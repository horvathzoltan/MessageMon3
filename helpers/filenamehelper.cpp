#include "filenamehelper.h"
#include "qcoreapplication.h"

#include <QDateTime>
#include <QDir>

//#include <stdio.h>
//#include <string.h>

bool FileNameHelper::_inited;
QString FileNameHelper::_projectPath;
bool FileNameHelper::_isTest;

bool FileNameHelper::Init(const char *file)
{
    _inited = false;

#if defined (STRING) && defined (TARGI) && defined (SOURCE_PATH)
    Q_UNUSED(file)
    _projectPath = STRING(SOURCE_PATH);
#else
    bool valid = file != nullptr;
    if(valid){
        QString path(file);
        if(path.endsWith(QStringLiteral("/helpers/filenamehelper.h"))){
            auto ap = QFileInfo(path).absoluteDir();
            ap.cdUp();
            _projectPath = ap.absolutePath();
            _inited = true;
        }
    }
#endif
    return _inited;
}

QString FileNameHelper::GetTestFolderPath()
{
    auto pp = QDir(_projectPath).filePath("testdata");
    return pp;
}

QString FileNameHelper::GetWorkingFolder()
{
    QString workingFolder = _isTest?FileNameHelper::GetTestFolderPath():qApp->applicationDirPath();
    return workingFolder;
}

QString FileNameHelper::GetLogFileName()
{
    QDateTime now = QDateTime::currentDateTime();
    QString format("yyyyMMdd-hhmmss");

    QString timestamp = now.toString(format);
    return timestamp;
}

QString FileNameHelper::GetHomeFolder()
{
    QString home = QDir::homePath();

    return home;
}

QString FileNameHelper::GetLogFolder(const QString& projectName)
{
    auto home = GetHomeFolder();
    QString logFolder = QDir(home).filePath("logs");
    if(!projectName.isEmpty()){
       logFolder = QDir(logFolder).filePath(projectName);
    }

    return logFolder;
}
