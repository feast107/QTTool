#include "../Include/Directory.h"
#include "../Include/Path.h"
QtTool::Directory::Directory(const QDir &dir)
{
    this->dir = dir;
}

QtTool::Directory::Directory(const QString &path)
{
    dir = QDir(path);
}

QtTool::Directory::Directory(const QtTool::Directory &other)
{
    dir = other.dir;
}

bool QtTool::Directory::Create()const
{
    if(Exist()){
        return true;
    }else{
        return dir.mkpath(FullName());
    }
}

bool QtTool::Directory::Exist()const
{
    return dir.exists();
}

bool QtTool::Directory::Delete()
{
    return dir.removeRecursively();
}

bool QtTool::Directory::operator ==(const QtTool::Directory &dir)const
{
    return this->FullName()==dir.FullName();
}

QString QtTool::Directory::Name()const
{
    return dir.dirName();
}

QString QtTool::Directory::FullName()const
{
    return dir.absolutePath();
}

QtTool::Directory QtTool::Directory::ParentDirectory()const
{
    QDir par = QDir(dir);
    if(par.cdUp()){
        return Directory(par.absolutePath());
    }else{
        return Directory("/");
    }
}

QList<QtTool::Directory> QtTool::Directory::GetDirectories()const
{
    QList<Directory> ret;
    for(auto d : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        ret.append(Directory(Path::Combine(FullName(),d)));
    }
    return ret;
}

QList<QtTool::File> QtTool::Directory::GetFiles()const
{
    QList<File> ret;
    for(auto f : dir.entryList(QDir::Files)){
        ret.append(File(Path::Combine(FullName(),f)));
    }
    return ret;
}

QList<QtTool::File> QtTool::Directory::GetAllFiles()const
{
    QList<File> ret;
    for(auto f:GetFiles()){
        ret.append(f);
    }
    for(auto d:GetDirectories()){
        for(auto f:d.GetAllFiles()){
            ret.append(f);
        }
    }
    return ret;
}

bool QtTool::Directory::Exist(const QString & path)
{
    return QDir(path).exists();
}

QtTool::Directory QtTool::Directory::Create(const QString &path)
{
    Directory dir(path);
    if(!dir.Exist()){
        dir.Create();
    }
    return dir;
}

bool QtTool::Directory::Delete(const QString &path)
{
    Directory d(path);
    if(d.Exist()){
        return d.Delete();
    }else{
        return true;
    }

}

QList<QtTool::File> QtTool::Directory::GetAllFiles(const QString & dir)
{
    return Directory(dir).GetAllFiles();
}
