#include "../../Include/Linux/Desktop.h"
#include "../../Include/File.h"
#include "../../Include/Path.h"
#include "../../Include/CMD.h"
#define ENTRY "[Desktop Entry]"
using namespace QtTool;

QString Desktop::X_Deepin_CreateBy_Head = "X-Deepin-CreatedBy";
QString Desktop::X_Deepin_CreateBy_Default = "com.deepin.dde.daemon.Launcher";

QString Desktop::X_Deepin_AppID_Head= "X-Deepin-AppID";
QString Desktop::X_Deepin_AppID_Default = "ZBH.zbform.Asura";

QString Desktop::Type_Head = "Type";
QString Desktop::Type_Default = "Application";

QString Desktop::Version_Head = "Version";
QString Desktop::Version_Default = "1.0.0";

QString Desktop::Exec_Head = "Exec";

QString Desktop::Icon_Head = "Icon";

QString Desktop::Name_Head = "Name";

QString Desktop::NameZH_Head = "Name[zh_CN]";

QString Desktop::StartupWMClass_Head = "StartupWMClass" ;

QString Desktop::Comment_Head = "Comment";
QString Desktop::Comment_Default = "Create By Orochi";

QString Desktop::Categories_Head = "Categories";
QString Desktop::Categories_Default = "Development";

QString Desktop::Terminal_Head = "Terminal";
QString Desktop::Terminal_Default = "false";

QString Desktop::MimeType_Head = "MimeType";

QString Desktop::GenericName_Head = "GenericName";
QString Desktop::GenericName_Default = Desktop::X_Deepin_AppID_Default;


QString Desktop::X_scheme_handler="x-scheme-handler/";

void Desktop::Set(QString attr, QString value)
{
    content += (attr+'='+value+'\n');
}

QString Desktop::Create(QString Path)
{
    File f(Path);
    if(!f.Exist()){
        f.Create();
    }else{
        return Path;
    }
    SetContent();
    f.WriteText(content);
    return Path;
}

QString Desktop::Create(QString Dir, QString pro,QString version)
{
    QString Path = Path::Combine({Dir,"usr","share","applications",pro+".desktop"});
    File f(Path);
    if(!f.Exist()){
        f.Create();
    }else{
        return Path;
    }
    Version = version;
    MimeType = NameZH = GenericName = Name = pro;
    Icon = "/usr/share/icons/";
    SetContent();
    f.WriteText(content);
    CMD("chmod -R 777 " +Path);
    return Path;
}

void Desktop::SetContent()
{
    content = "[Desktop Entry]\n";

#ifdef DEEPINS
    if( X_Deepin_CreateBy != ""){
        Set(X_Deepin_CreateBy_Head,X_Deepin_CreateBy);
    }else{
        Set(X_Deepin_CreateBy_Head,X_Deepin_CreateBy_Default);
    }

    if( X_Deepin_AppID != ""){
        Set(X_Deepin_AppID_Head,X_Deepin_AppID);
    }else{
        Set(X_Deepin_AppID_Head,X_Deepin_AppID_Default);
    }
#endif
    if( Type != ""){
        Set(Type_Head,Type);
    }else{
        Set(Type_Head,Type_Default);
    }

    if( Version != ""){
        Set(Version_Head,Version);
    }else{
        Set(Version_Head,Version_Default);
    }

    if( Name != ""){
        Set(Name_Head,Name);
        Set(StartupWMClass_Head,Name);
    }
    if( Exec != ""){
        Set(Exec_Head,Exec);
    }
    if( Icon != ""){
        Set(Icon_Head,Icon);
    }
    if( StartupWMClass != ""){
        Set(StartupWMClass_Head,StartupWMClass);
    }

    if( Comment != ""){
        Set(Comment_Head,Comment);
    }else{
        Set(Comment_Head,Comment_Default);
    }

    if( Terminal != ""){
        Set(Terminal_Head,Terminal);
    }else{
        Set(Terminal_Head,Terminal_Default);
    }

    if( GenericName != ""){
        Set( GenericName_Head , GenericName );
    }else{
        Set( GenericName_Head , GenericName_Default );
    }

    if( MimeType != ""){
        Set( MimeType_Head , X_scheme_handler + MimeType );
    }
    if(NameZH != "" ){
        Set( NameZH_Head , NameZH );
    }else{
        Set( NameZH_Head , Name);
    }
}

Desktop::Desktop()
{

}

void Desktop::Clear()
{
    content = "";
}
