#ifndef E_H
#define E_H
#include <QString>
#include <QProcess>
#include <initializer_list>
using namespace std;
namespace QtTool
{
    class CMD
    {
        private:
            QProcess p;
            QStringList result;
        public:
            explicit CMD();
            explicit CMD(const QString & workDir);
            ~CMD();
            CMD* Enter(const QString & cmd);
            CMD* Enter(const QString & cmd,const QString & arg);
            CMD* Enter(const QString & cmd, const QStringList & args);
            CMD* Enter(initializer_list<QString> cmds);
            CMD* Enter(initializer_list<QString> cmds,
                       initializer_list<QStringList> args);
            QStringList Result()const;
            static QString E(QProcess* processer, const QString & cmd);
            static QString E(QProcess* processer, const QString & cmd,const QString & arg);
            static QString E(QProcess* processer, const QString & cmd, const QStringList & args);
            static QStringList L(const QString & Eresult);
    };
};


#endif // E_H
