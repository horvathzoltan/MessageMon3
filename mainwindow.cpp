#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyleFactory>

QPlainTextEdit* MainWindow::_plainTextEdit = nullptr;

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetMessage(const QString &msg)
{
    if(!_plainTextEdit) return;

    _plainTextEdit->appendPlainText(msg);
}

void MainWindow::Log(const QString& str0)
{
    QString str(str0);
    str.replace('<', "&lt;").replace('>', "&gt;");

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
