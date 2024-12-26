#ifndef MYSERVER_H
#define MYSERVER_H

#include "processrequest.h"

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

struct ClientSettings{
protected:
    QString _host;
    int _port;

public:
    ClientSettings(){};
    ClientSettings(const QString& h,int port);

    QString host(){return _host;}
    int port(){return _port;}
    QString ToString_HostPort();
};

typedef bool (*RequestProcessor)(const QString&,const QChar& sep);
typedef bool (ProcessRequest::*mRequestProcessor)(const QString&,const QChar& sep);

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void SetRequestProcessor(RequestProcessor r){_requestProcessor = r;}
    void SetmRequestProcessor(mRequestProcessor r, ProcessRequest& pr){_mrequestProcessor = r; _pr = pr;}
    QString ToString_HostPort(){return _settings.ToString_HostPort();}
signals:

public slots:
    void newConnection();

private:
    QTcpServer *_server;

    ClientSettings _settings;

    bool _verbose = true;
    RequestProcessor _requestProcessor;
    mRequestProcessor _mrequestProcessor;
    ProcessRequest _pr;
    static QString GetIpAddress();
};

#endif // MYSERVER_H
