#include "mainwindow.h"
#include "ui_mainwindow.h"

QPlainTextEdit* MainWindow::_plainTextEdit = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _plainTextEdit = ui->plainTextEdit;
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
