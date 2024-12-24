#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <functional>


class Logger
{
private:
    static std::function<void(const QString& str)> _func;
public:
    static void SetFunction(std::function<void(const QString& str)> f){ _func = f;};

    static void Info(const QString& msg);

};

#endif // LOGGER_H
