#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QRegularExpression>
#include <QStyleFactory>

#include <helpers/filehelper.h>
#include <helpers/filenamehelper.h>

QPlainTextEdit* MainWindow::_plainTextEdit = nullptr;
//QString MainWindow::_projectame = "";
//QString MainWindow::_projectFolder = "";
//QString MainWindow::_fileName = "";
QString MainWindow::_filePath = "";
QString MainWindow::_site = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _plainTextEdit = ui->plainTextEdit;
    //_isDarkMode = isDarkMode();

    //if(_isDarkMode){
        SetDarkMode();
    //}
}

void MainWindow::Maximize()
{
    this->setWindowState(Qt::WindowMaximized); //Maximizes the window
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetMessage(const QString &msg)
{
    if(!_plainTextEdit) return;

    _plainTextEdit->appendHtml(msg);
}

void MainWindow::Log(const QString& str0)
{
    QDateTime now = QDateTime::currentDateTime();
    QString format("yyyy.MM.dd. hh:mm.ss");
    QString timestamp = now.toString(format);

    QString logLevel = GetLogLevel(str0);

    QString str(str0);
    str.replace('<', "&lt;").replace('>', "&gt;");

    if(_filePath.isEmpty()){
        if(str0.startsWith("started")){
            ProjModel proj = GetProjectName(str0);
            if(proj.projectName != QCoreApplication::applicationName())
            {
                _site = proj.site;
                QString projectFolder = FileNameHelper::GetLogFolder(proj.projectName);
                QString fileName = FileNameHelper::GetLogFileName();

                bool isPath = FileHelper::MakePath(projectFolder);
                if(isPath){
                    _filePath = projectFolder+'/'+fileName;
                }
            }
        }
    }

    if(!_filePath.isEmpty()){
        FileHelper::Save(timestamp+';'+_site+';'+logLevel+';'+str0+'\n',
                         _filePath,
                         nullptr,
                         FileHelper::SaveModes::Append);
    }

    QString logColor = GetLogColor(str);
    int ix = str.indexOf(':');
    QString keyword = (ix>-1)?str.left(ix):"";
    QStringList strs = str.split("\n", Qt::SkipEmptyParts);

    for(auto&a:strs){
        if(a.isEmpty()) continue;
        if(!a.startsWith(keyword)){
            a=keyword+": "+a;
        }
        QString msg = ColorizeLog2(a, logColor);

        SetMessage(msg);
    }
}

QString MainWindow::ColorizeLog2(const QString& str, const QString& c){
    if(c.isEmpty()) return str;
    return QStringLiteral("<p style='color: ")+c+"'>"+str+"</p>";
}


// QString MainWindow::ColorizeLog(const QString& str){
//     if(str.startsWith("ERROR:")) return ColorizeLog2(str, "red");
//     if(str.startsWith("WARNING:")) return ColorizeLog2(str, "orange");
//     if(str.startsWith("DEBUG:")) return ColorizeLog2(str, "yellow");
//     if(str.startsWith("TRACE:")) return ColorizeLog2(str, "green");
//     return str;
// }

QString MainWindow::GetLogColor(const QString& str){
    if(str.startsWith("ERROR:")) return "red";
    if(str.startsWith("WARNING:")) return "orange";
    if(str.startsWith("DEBUG:")) return "yellow";
    if(str.startsWith("TRACE:")) return "green";
    return "";
}

QString MainWindow::GetLogLevel(const QString& str){
    if(str.startsWith("ERROR:")) return "error";
    if(str.startsWith("WARNING:")) return "warning";
    if(str.startsWith("DEBUG:")) return "debug";
    if(str.startsWith("TRACE:")) return "trace";
    return "info";
}

bool MainWindow::isDarkMode()
{
    const QPalette defaultPalette;
    const auto text = defaultPalette.color(QPalette::WindowText);
    const auto window = defaultPalette.color(QPalette::Window);
    bool isDark = text.lightness() > window.lightness();
    return isDark;
}



void MainWindow::SetDarkMode()
{
    // set style
    qApp->setStyle(QStyleFactory::create("Fusion"));
    // increase font size for better reading
    QFont defaultFont = QApplication::font();
    defaultFont.setPointSize(defaultFont.pointSize()+2);
    qApp->setFont(defaultFont);
    // modify palette to dark
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window,QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Base,QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
    darkPalette.setColor(QPalette::ToolTipText,Qt::white);
    darkPalette.setColor(QPalette::Text,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
    darkPalette.setColor(QPalette::Button,QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText,Qt::red);
    darkPalette.setColor(QPalette::Link,QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));

    qApp->setPalette(darkPalette);
}

MainWindow::ProjModel MainWindow::GetProjectName(const QString &str)
{
    QRegularExpression r(R"((start[\w]*)\s*([\w]+)+(?:\(([\d\.]*)\))?\s*as\s*([\w@]*))");

    QRegularExpressionMatch m = r.match(str);

    ProjModel p;

    int lastCapturedIx = m.lastCapturedIndex();
    if(lastCapturedIx>=2){
        p.projectName= m.captured(2);
    }
    if(lastCapturedIx>=4){
        p.site= m.captured(4);
    }
    return p;
}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
}


