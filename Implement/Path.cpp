#include "../Include/Path.h"
#include <QDir>
#include <QCoreApplication>
QString QtTool::Path::Combine(const char *p1, const char *p2)
{
    return Combine(QString(p1),QString(p2));
}

QString QtTool::Path::Combine(const QString &p1, const QString &p2)
{
    return QDir::cleanPath(p1+QDir::separator()+p2);
}

QString QtTool::Path::Combine(std::initializer_list<const char *> paths)
{
    QString ret = "";
    for(const char* s : paths){
        if(ret == ""){
            ret = QDir::cleanPath(QString(s));
        }else{
            ret = Combine(ret,QString(s));
        }
    }
    return ret;
}

QString QtTool::Path::Combine(std::initializer_list<QString> paths)
{
    QString ret = "";
    for(QString s : paths){
        if(ret == ""){
            ret = QDir::cleanPath(s);
        }else{
            ret = Combine(ret,s);
        }
    }
    return ret;
}

QString QtTool::Path::ParentDirectory(const QString & path)
{
    QFileInfo f(path);
    if(f.exists()){
        if(f.isDir()){
            QDir dir(path);
            if(dir.cdUp()){
                return dir.absolutePath();
            }
        }if(f.isFile()){
            return f.dir().absolutePath();
        }
    }
    return "";
}

QString QtTool::Path::CurrentDirectory()
{
    return QCoreApplication::applicationDirPath();
}

QString QtTool::Path::ExecutionPath()
{
    return QCoreApplication::applicationFilePath();
}
