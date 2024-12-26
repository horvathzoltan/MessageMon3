#ifndef SYSINFOHELPER_H
#define SYSINFOHELPER_H

#include <QString>

class SysInfoHelper
{
private:
    struct Data{
    private:
        QString _target;
        QString _buildNumber;
        QString _user;
        QString _hostName;
    public:
        Data(){};
        Data(const QString& t,
             const QString& b,
             const QString& u,
             const QString& h);

        bool hasBuildNumber();
        QString Get_SysInfo();
    };

    static Data _data;
    static bool _isInited;
public:
    static void Init(const QString& t, const QString& b);
    static QString Get_SysInfo();
};

#endif // SYSINFOHELPER_H
