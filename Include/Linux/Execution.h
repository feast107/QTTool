#ifndef EXECUTION_H
#define EXECUTION_H
#include "../File.h"
#include <QString>
namespace QtTool
{
    class Execution
    {
        private:
            bool got = false;
            QMyFile execution;
            QList<QMyFile> dependencies;
        public:
            QMyFile GetExecution()const;
            bool IsExecutable();
            QList<QMyFile> GetDependencies();
            Execution(const QString & executionPath);
            QStringList Collect(QString dir);
            QString Export();
            static QList<Execution> GetExecutables(QString dir);
    };
}
#endif // EXECUTION_H
