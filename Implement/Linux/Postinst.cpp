#include "Postinst.h"
#include "../QPath.h"
#include "../QMyFile.h"
#include "Execution.h"
#include "../QtTool.hpp"
using namespace QtTool;
#define POSTINST "postinst"
#define DEBIAN "DEBIAN"
#define BINHEAD "#!/bin/sh"
Postinst::Postinst()
{

}

QString Postinst::Create(QString PackageDir)
{
    QString path = QPath::Combine({PackageDir,DEBIAN,POSTINST});
    QMyFile f(path);
    if(f.Exist()){
        f.Delete();
    }
    f.Create();
    QString content = BINHEAD + '\n';
    for(auto f :QDirectory::GetAllFiles(PackageDir)){
        if((f.IsExecutable()&&f.Extension()=="")||f.Extension()=="desktop"){
            content += "chown root "+f.FullName().replace(0,PackageDir.length()+1,"") +'\n';
            content += "chmod -R a+s "+f.FullName().replace(0,PackageDir.length()+1,"") +'\n';
        }
    }
    f.WriteText(content);
    CMD("chmod -R 775 " +path);
    return path;
}
