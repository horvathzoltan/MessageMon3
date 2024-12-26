#include "sysinfohelper.h"

//started biovitality as zoli@hercules
//started biovitality as zoli@pif

SysInfoHelper::Data SysInfoHelper::_data;
bool SysInfoHelper::_isInited=false;

void SysInfoHelper::Init(const QString &t, const QString &b)
{
    _isInited = false;
    _data = Data(t, b,
                 qgetenv("USER"),
                 QSysInfo::machineHostName());
    _isInited = true;
}

SysInfoHelper::Data::Data(const QString& t,
                          const QString& b,
                          const QString& u,
                          const QString& h){
    _target = t;
    _buildNumber = b;
    _user = u;
    _hostName = h;
}

bool SysInfoHelper::Data::hasBuildNumber(){
    if(_buildNumber.isEmpty()) return false;
    if(_buildNumber=="-1") return false;
    return true;
}

QString SysInfoHelper::Data::Get_SysInfo(){
    QString msg = _target;
    if(_data.hasBuildNumber())
    {
        msg+="("+_buildNumber+")";
    }

    if(!_user.isEmpty()){
        msg += +" as "+_user;
    }

    if(!_hostName.isEmpty())
    {
        msg+="@"+_hostName;
    }

    return msg;
}

QString SysInfoHelper::Get_SysInfo()
{
    if(!_isInited) return {};
    return _data.Get_SysInfo();
}
