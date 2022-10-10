#include "../Include/CMD.h"
#include <QDebug>
#include <QTextCodec>
QtTool::CMD::CMD():p(0)
{

}

QtTool::CMD::CMD(const QString &workDir):p(0)
{
    p.setWorkingDirectory(workDir);
}

QtTool::CMD::~CMD()
{
    p.close();
}

inline QString WaitForResult(QProcess *processer){
    processer->waitForFinished();
    QByteArray res = processer->readAllStandardOutput();
    QTextCodec* pTextCodec = QTextCodec::codecForName("System");
    QString ret = pTextCodec->toUnicode(res).replace('\t',"").replace('\r',"");
    for(auto s:ret.split('\n')){
        if(s!=""){
            qDebug()<<s;
        }
    }
    return ret;
}

QString QtTool::CMD::E(QProcess *processer, const QString & cmd){
    processer->start(cmd);
    processer->waitForStarted();
    return  WaitForResult(processer);
}

QString QtTool::CMD::E(QProcess *processer, const QString &cmd, const QString &arg)
{
    processer->start(cmd,QStringList(arg));
    processer->waitForStarted();
    return  WaitForResult(processer);
}

QString QtTool::CMD::E(QProcess *processer, const QString & cmd, const QStringList & args){
    processer->start(cmd,args);
    processer->waitForStarted();
    return  WaitForResult(processer);
}

QtTool::CMD* QtTool::CMD::Enter(const QString & cmd){
    result.append(QtTool::CMD::E(&p,cmd));
    return this;
}

QtTool::CMD *QtTool::CMD::Enter(const QString &cmd, const QString &arg)
{
    QString ret = QtTool::CMD::E(&p,cmd);
    result.append(ret);
    return this;
}

QtTool::CMD* QtTool::CMD::Enter(const QString & cmd, const QStringList & args){
    QString ret = QtTool::CMD::E(&p,cmd,args);
    result.append(ret);
    return this;
}


QtTool::CMD* QtTool::CMD::Enter(std::initializer_list<QString> cmds){
    QString ret = "";
    auto cmd = cmds.begin();
    while(cmd!=cmds.end()){
        ret += E(&p,*cmd);
        cmd++;
    }
    result.append(ret);
    return this;
}


QtTool::CMD* QtTool::CMD::Enter(std::initializer_list<QString> cmds, std::initializer_list<QStringList> args){
    QString ret = "";
    auto cmd = cmds.begin();
    auto arg = args.begin();
    while(cmd!=cmds.end()){
        ret += E(&p,*cmd,*arg);
        cmd++;
        arg++;
    }
    p.close();
    result.append(ret);
    return this;
}

QStringList QtTool::CMD::Result() const
{
    return result;
}


QStringList QtTool::CMD::L(const QString &cmdresult)
{
    return cmdresult.split('\n');
}
