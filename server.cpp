#include "server.h"

#include <QElapsedTimer>
#include <logger.h>
#include <QNetworkInterface>

// git ieszt 23

Server::Server(QObject *parent) :
    QObject(parent)
{
    _server = new QTcpServer(this);

    QString ipAddress = GetIpAddress();
    _settings = ClientSettings(ipAddress, 8081);

    connect(_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!_server->listen(QHostAddress::Any, _settings.port()))
    {
        Logger::Info("Server could not start!");
    }
    else
    {
        QString msg = QStringLiteral("The server is running on ")
                      +_settings.ToString_HostPort();
        Logger::Info(msg);
    }
}

void Server::newConnection()
{
    QElapsedTimer t;
    t.start();
    qint64 t1=0, t2=0;//, t3=0;
    QString request;
    bool connected=false, receive_ok=false;//, send_ok=false;

    QTcpSocket *socket = _server->nextPendingConnection();
    connected = socket!=nullptr;

    if(connected)
    {
        receive_ok = socket->waitForReadyRead(1000);
        t1 = t.elapsed();
        if(receive_ok){
            QByteArray bytes_in = socket->readAll();
            //t2 = t.elapsed();
            socket->write("ok");
            socket->flush();
            //t2 = t.elapsed();
            //send_ok = socket->waitForBytesWritten(1000);
            t2 = t.elapsed();
            request = QString(bytes_in);
        }
        socket->close();
    }

    if(_verbose){
        QString a1(QStringLiteral("connect[ms]: ")+QString::number(t1)+' '+(connected?"ok":"failed"));
        QString a2(QStringLiteral("receive[ms]: ")+QString::number(t2)+' '+(receive_ok?"ok":"failed"));
        //QString a3(QStringLiteral("send[ms]: ")+QString::number(t3)+' '+(send_ok?"ok":"failed"));
        qDebug() <<a1<<a2;//<<a3;
    }

    //    if(_requestProcessor!=nullptr){
    //        _requestProcessor(request);
    //    }
    if(_mrequestProcessor != nullptr){
        (_pr.*_mrequestProcessor)(request, ':');
    }
}

QString Server::GetIpAddress()
{
    QString ipAddress;
    const QList<QHostAddress> ipAddressesList =
        QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}


ClientSettings::ClientSettings(const QString &h, int port)
{
    _host = h;
    _port = port;
}

QString ClientSettings::ToString_HostPort()
{
    return _host+":"+QString::number(_port);
}
