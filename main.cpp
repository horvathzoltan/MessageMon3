#include "mainwindow.h"
#include <QApplication>
#include <logger.h>
#include "server.h"
#include "processrequest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::SetFunction(&MainWindow::SetMessage);

    MainWindow w;        
    w.show();  

    ProcessRequest r;
    Server mServer;
    mServer.SetmRequestProcessor(&ProcessRequest::Process, r);

    return a.exec();
}
