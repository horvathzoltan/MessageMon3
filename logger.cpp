#include "logger.h"
#include "qdebug.h"

std::function<void(const QString& str)> Logger::_func = nullptr;


void Logger::Info(const QString &msg)
{
    if(_func)
    {
        _func(msg);
    } else{
        qInfo()<<msg;
    }
}
