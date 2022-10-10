#ifndef QDIRECTORY_H
#define QDIRECTORY_H
#include <QString>
#include <QDir>
#include "File.h"
namespace QtTool
{
    class File;
    class Directory
    {
            friend class File;
        private:
            QDir dir;
            Directory(const QDir & dir);
        public:
            Directory(const QString & path);
            Directory(const Directory & other);
            bool Create()const;
            bool Exist()const;
            bool Delete();
            bool operator == (const Directory & dir)const;

            QString Name()const;
            QString FullName()const;
            Directory ParentDirectory()const;
            QList<Directory> GetDirectories()const;
            QList<File> GetFiles()const;
            QList<File> GetAllFiles()const;

            static bool Exist(const QString & path);
            static Directory Create(const QString & path);
            static bool Delete(const QString & path);
            static QList<File> GetAllFiles(const QString & dir);
    };
}
#endif // QDIRECTORY_H
