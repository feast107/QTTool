#include "../../Include/Linux/Control.h"
#include "../../Include/File.h"
#include "../../Include/Path.h"
using namespace QtTool;
#define CONTROL "control"

#define PACKAGE "Package"
#define VERSION "Version"
#define SECTION "Section"
#define PRIORITY "Priority"
#define DEPENDS "Depends"
#define ARCHITECTURE "Architecture"
#define MAINTAINER "Maintainer"
#define DESCRIPTION "Description"
#define ESSENTIAL "Essential"
#define SOURCE "Source"
#define MULTIARCH "Multi-Arch"
#define DEBIAN "DEBIAN"
Control::Control()
{

}

inline void Append(QString* src,QString key,QString value){
    *src += key + ": " + value + '\n';
}

QString Control::Create(QString PackageDir)
{
    QString content = "";
    File f(Path::Combine({PackageDir,DEBIAN,CONTROL}));
    if(f.Exist()){
        f.Delete();
    }
    f.Create();
    if(Package!=""){
        Append(&content,PACKAGE,Package);
    }
    if(Source!=""){
        Append(&content,SOURCE,Source);
    }
    if(Version!=""){
        Append(&content,VERSION,Version);
    }
    if(Section!=""){
        Append(&content,SECTION,Section);
    }
    if(Priority!=""){
        Append(&content,PRIORITY,Priority);
    }
    if(Depends!=""){
        Append(&content,DEPENDS,Depends);
    }
    if(Maintainer!=""){
         Append(&content,MAINTAINER,Maintainer);
    }
    if(Architecture!=""){
        Append(&content,ARCHITECTURE,Architecture);
    }
    if(Multi_Arch!=""){
        Append(&content,MULTIARCH,Multi_Arch);
    }
    if(Description!=""){
        Append(&content,DESCRIPTION,Description);
    }
    Append(&content,ESSENTIAL,Essential?"yes":"no");
    f.WriteText(content);
    return f.FullName();
}
