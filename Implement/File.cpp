#include "../Include/File.h"
#include <QFile>
QtTool::File::File(const QString &path)
{
    f = QFileInfo(path);
}

QtTool::File::File(const QtTool::File &other)
{
    f = other.f;
}

bool QtTool::File::Exist()const
{
    return f.exists() && f.isFile();
}

bool QtTool::File::Create()const
{
    if(!Exist()){
        if(!Directory().Exist()){
            Directory().Create();
        }
        QFile file(f.filePath());
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            file.close();
            return true;
        }else{
            return false;
        }
    }else{
        return true;
    }
}

bool QtTool::File::Delete()const
{
    return f.dir().remove(Name());
}

bool QtTool::File::CopyTo(const QString & dst)
{
    return QFile::copy(FullName(), dst);
}

bool QtTool::File::MoveTo(const QString & dst)
{
    return QFile::rename(FullName(),dst);
}

bool QtTool::File::operator ==(const QtTool::File &file)const
{
    return this->FullName()==file.FullName();
}

QString QtTool::File::Name()const
{
    return f.fileName();
}

QString QtTool::File::StandardName()const
{
    return f.completeBaseName();
}

QString QtTool::File::NameWithoutExtension()const
{
    int last =  Extension().length();
    if(last == 0){
        return Name();
    }else{
        return Name().mid(0,Name().length() - (++last));
    }
}

QString QtTool::File::FullName()const
{
    return f.filePath();
}

QString QtTool::File::Extension()const
{
    return f.completeSuffix();
}

bool QtTool::File::IsExecutable()const
{
    return Exist() && f.isExecutable();
}

bool QtTool::File::IsHidden()const
{
    return Exist() && f.isHidden();
}

QString QtTool::File::DirectoryName()const
{
    return Directory().Name();
}

QtTool::Directory QtTool::File::Directory()const
{
    return QtTool::Directory(f.dir());
}

qint64 QtTool::File::Length()
{
    return f.size();
}

bool QtTool::File::WriteText(const QString & text)
{
    if(!Exist()){
        return false;
    }
    return WriteBytes(text.toUtf8());
}

bool QtTool::File::AppendText(const QString &text)
{
    if(!Exist()){
        return false;
    }
    return AppendBytes(text.toUtf8());
}

bool QtTool::File::WriteBytes(const QByteArray & bytes)
{
    if(!Exist()){
        return false;
    }
    QFile file(FullName());
    if(file.open(QIODevice::WriteOnly)){
        file.write(bytes);
        file.close();
        return true;
    }else{
        return false;
    }
}

bool QtTool::File::AppendBytes(const QByteArray &bytes)
{
    if(!Exist()){
        return false;
    }
    QFile file(FullName());
    if(file.open(QIODevice::Append)){
        file.write(bytes);
        file.close();
        return true;
    }else{
        return false;
    }
}

QByteArray QtTool::File::ReadAllBytes()
{
    QByteArray ret;
    if(Exist()){
        QFile file(FullName());
        file.open(QIODevice::ReadOnly);
        ret = file.readAll();
    }
    return ret;
}

QString QtTool::File::ReadText()
{
    return QString(ReadAllBytes());
}

bool QtTool::File::Exist(const QString &path)
{
    return File(path).Exist();
}

QtTool::File QtTool::File::Create(const QString &path)
{
    File ret(path);
    if(!ret.Exist()){
        ret.Create();
    }
    return ret;
}

bool QtTool::File::Delete(const QString &path)
{
    return File(path).Delete();
}

bool QtTool::File::MoveTo(const QString & src, const QString & dst)
{
    return QFile::rename(src,dst);;
}

bool QtTool::File::CopyTo(const QString & src, const QString & dst)
{
    return File(src).CopyTo(dst);
}
