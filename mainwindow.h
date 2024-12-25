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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    static void SetMessage(const QString& msg);
    static void Log(const QString &str0);
    static QString GetLogColor(const QString &str);
    static QString ColorizeLog2(const QString &str, const QString &c);

    bool isDarkMode();
private:
    Ui::MainWindow *ui;
    bool _isDarkMode;
    static QPlainTextEdit* _plainTextEdit;
    void SetDarkMode();
};
#endif // MAINWINDOW_H
