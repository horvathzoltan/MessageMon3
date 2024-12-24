#include "processrequest.h"
#include <QDebug>
#include <logger.h>

bool ProcessRequest::Process(const QString &request, const QChar& sep)
{
    bool retVal = false;
    bool valid = !request.isEmpty();

    if(valid){    //master:started
        int ix = request.indexOf(sep);
        if(ix>0){
            QString cmd = request.left(ix);
            QString value = request.mid(ix+1);

            if(cmd=="master"){
                retVal = MasterCmd(value);
            } else if(cmd=="pow"){
                retVal = PowCmd(value);
            } else if(cmd=="addlog"){
                retVal = AddLog(value);
            }
        } else{
            if(request=="getlist"){
                retVal = GetListRequest();
            }
        }

    }
    return retVal;
}


bool ProcessRequest::MasterCmd(const QString &value)
{
    qDebug()<<"MasterCmd:"<<value;
    return true;
}

bool ProcessRequest::PowCmd(const QString &value)
{
    qDebug()<<"PowCmd:"<<value;
    return true;
}

bool ProcessRequest::GetListRequest()
{
    qDebug()<<"GetListRequest";
    return true;
}

bool ProcessRequest::AddLog(const QString &value)
{
    Logger::Info(value);
    return true;
}

