#ifndef QPATH_H
#define QPATH_H
#include <QString>
#include <initializer_list>

namespace QtTool
{
    class Path
    {
        public:
            static QString Combine(const char* p1,const char* p2);
            static QString Combine(const QString & p1,const QString & p2);
            static QString Combine(std::initializer_list<const char*> paths);
            static QString Combine(std::initializer_list<QString> paths);
            static QString ParentDirectory(const QString & path);
            static QString CurrentDirectory();
            static QString ExecutionPath();
    };
}
#endif // QPATH_H
