#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct ProjModel{
    public:
        QString projectName;
        QString site;
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    static void SetMessage(const QString& msg);
    static void Log(const QString &str0);
    static QString GetLogColor(const QString &str);
    static QString GetLogLevel(const QString& str);
    static QString ColorizeLog2(const QString &str, const QString &c);

    bool isDarkMode();    
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool _isDarkMode;
    //static QString _projectame;
    //static QString _projectFolder;
    //static QString _fileName;
    static QString _filePath;
    static QString _site;

    static QPlainTextEdit* _plainTextEdit;
    void SetDarkMode();
    static ProjModel GetProjectName(const QString &);
};
#endif // MAINWINDOW_H
