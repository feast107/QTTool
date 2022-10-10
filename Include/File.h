#ifndef QMYFILE_H
#define QMYFILE_H
#include <QString>
#include <QFileInfo>
#include "Directory.h"
namespace QtTool
{
    class Directory;
    class File
    {
            friend class Directory;
        private:
            QFileInfo f;
        public:
            File(const QString & path);
            File(const File & other);
            bool Exist()const;
            bool Create()const;
            bool Delete()const;
            bool CopyTo(const QString & dst);
            bool MoveTo(const QString & dst);
            bool operator ==(const File & file)const;

            QString Name()const;
            QString StandardName()const;
            QString NameWithoutExtension()const;
            QString FullName()const;
            QString Extension()const;
            bool IsExecutable()const;
            bool IsHidden()const;
            QString DirectoryName()const;
            QtTool::Directory Directory()const;
            qint64 Length();

            bool WriteText(const QString & text);
            bool AppendText(const QString & text);
            bool WriteBytes(const QByteArray & bytes);
            bool AppendBytes(const QByteArray & bytes);
            QByteArray ReadAllBytes();
            QString ReadText();

            static bool Exist(const QString & path);
            static File Create(const QString & path);
            static bool Delete(const QString & path);
            static bool MoveTo(const QString & src,const QString & dst);
            static bool CopyTo(const QString & src,const QString & dst);
    };
}
#endif // QMYFILE_H
