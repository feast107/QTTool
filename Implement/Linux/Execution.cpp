#include "Execution.h"
#include <QProcess>
#include "../QtTool.hpp"
#include "../QPath.h"
#define LOCATE_DYNAMIC_DEPENDENCE "ldd "
using namespace QtTool;
static QtTool::QMyFile* Analyze(QString cmd){
    int status = 0 ;
    QString path;
    bool over = false;
    for(QChar c : cmd){
        if(over) break;
        switch(status){
            case 0:
            {
                if(c=='>') status=1;
            }break;
            case 1:
            {
                if(c=='(' ) { over = true;break;}
                if(c!=' ' ){ status=2;path+=c; }

            }break;
            case 2:
            {
                if(c!=' '&& c != '(' ) path+=c;
                else over = true;
            }break;
        }
    }
    if(path.trimmed()!=""){
        QtTool::QMyFile* f = new QtTool::QMyFile(path);
        return f;
    }else{
        return NULL;
    }
}

QMyFile Execution::GetExecution()const
{
    return execution;
}

bool QtTool::Execution::IsExecutable()
{
    return execution.IsExecutable();
}

QList<QtTool::QMyFile> QtTool::Execution::GetDependencies()
{
    if(IsExecutable() && !got)
    {
        QProcess p(0);
        QMyFile* f = NULL;
        for(QString s : CMD(&p,LOCATE_DYNAMIC_DEPENDENCE+execution.FullName()).split('\n'))
        {
            f = Analyze(s);
            if(f!=NULL){
                dependencies.append(*f);
                f = NULL;
            }
        }
        got = true;
    }
    return dependencies;
}

QtTool::Execution::Execution(const QString & executionPath):
    execution(executionPath){}

QString QtTool::Execution::Export()
{
    QString ret = "";
    for(auto f :GetDependencies()){
        if(f.Name().trimmed()!=""){
            if(ret == ""){
                ret += f.Name();
            }else if(ret[ret.length()-1]!=','){
                ret +=","+f.Name();
            }else{
                ret += f.Name();
            }
        }
    }
    return ret;
}
static QList<QMyFile> GetExes(QDirectory dir){
    QList<QMyFile>ret;
    for(auto f:dir.GetFiles()){
        if(f.IsExecutable()){
            ret.append(f);
        }
    }
    for(auto d :dir.GetDirectories()){
        for(auto f:GetExes(d)){
            ret.append(f);
        }
    }
    return ret;
}

QList<QtTool::Execution> QtTool::Execution::GetExecutables(QString dir)
{
    QList<Execution> ret;
    QDirectory dire(dir);
    for(auto d:dire.GetDirectories()){
        for(auto f:GetExes(d)){
            ret.append(Execution(f.FullName()));
        }
    }
    return ret;
}

QStringList QtTool::Execution::Collect(QString dir)
{
    QDirectory d(dir);
    QStringList ret;
    if(!d.Exist()){
        d.Create();
    }
    for(auto f : GetDependencies()){
        QString path = QPath::Combine(dir,f.Name());
        if(f.CopyTo(path)){
            ret.append(path);
        }
    }
    return ret;
}
