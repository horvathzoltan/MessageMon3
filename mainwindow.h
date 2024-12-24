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
private:
    Ui::MainWindow *ui;

    static QPlainTextEdit* _plainTextEdit;
};
#endif // MAINWINDOW_H
