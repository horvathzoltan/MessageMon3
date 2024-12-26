#include "mainwindow.h"
#include <QApplication>
#include <logger.h>
#include "helpers/stringify.h"

#include "server.h"
#include "processrequest.h"
#include "helpers/filenamehelper.h"
#include "helpers/sysinfohelper.h"

int main(int argc, char *argv[])
{
#if defined (STRINGIFY_H) && defined (STRING) && defined (TARGI)
    QString target = STRING(TARGI);
#else
    auto target=QStringLiteral("ApplicationNameString");
#endif

    QCoreApplication::setApplicationName(target);
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("horvathzoltan");
    QCoreApplication::setOrganizationDomain("https://github.com/horvathzoltan");

    QApplication a(argc, argv);

    Logger::SetFunction(&MainWindow::Log);
    FileNameHelper::Init();
    SysInfoHelper::Init(target, "");

    MainWindow w;
    w.show();

    //
    QString sysInfo = SysInfoHelper::Get_SysInfo();
    Logger::Info("started:"+sysInfo);
    //
    QString folder = FileNameHelper::GetHomeFolder();//GetWorkingFolder();
    QString fileName = FileNameHelper::GetLogFileName();
    QString logFilePath = folder+"/"+fileName+".log";
    Logger::Info("logFilePath:"+logFilePath);

    ProcessRequest r;
    Server mServer;
    mServer.SetmRequestProcessor(&ProcessRequest::Process, r);

    QString title = target+' '+mServer.ToString_HostPort();
    w.setWindowTitle(title);

    return a.exec();
}
