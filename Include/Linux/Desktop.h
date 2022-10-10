#ifndef DESKTOP_H
#define DESKTOP_H
#include <QString>
namespace  QtTool {
    class Desktop
    {
        private:
            void Set(QString attr,QString value);
            QString content = "";
            static QString X_Deepin_CreateBy_Head ;
            static QString X_Deepin_CreateBy_Default ;

            static QString X_Deepin_AppID_Head;
            static QString X_Deepin_AppID_Default ;

            static QString Type_Head;
            static QString Type_Default ;

            static QString Version_Head;
            static QString Version_Default ;

            static QString Exec_Head;

            static QString Icon_Head;

            static QString Name_Head;

            static QString NameZH_Head;

            static QString Comment_Head;
            static QString Comment_Default;

            static QString StartupWMClass_Head;

            static QString Categories_Head;
            static QString Categories_Default;

            static QString Terminal_Head ;
            static QString Terminal_Default;

            static QString MimeType_Head;

            static QString GenericName_Head;
            static QString GenericName_Default;
            static QString X_scheme_handler;
        public:
            /**
             * @brief 创建者
             */
            QString X_Deepin_CreateBy ;
            /**
             * @brief 应用标识ID
             */
            QString X_Deepin_AppID;
            /**
             * @brief Application , Link , Direcory
             */
            QString Type;
            /**
             * @brief 版本
             */
            QString Version;
            /**
             * @brief 可执行程序路径（重要）
             */
            QString Exec;
            /**
             * @brief 绝对路径or符合图标主题规范
             */
            QString Icon;
            /**
             * @brief 应用程序的特定名称
             */
            QString Name;
            /**
             * @brief 注解
             */
            QString Comment;
            /**
             * @brief 默认与Name相同
             */
            QString StartupWMClass ;
            /**
             * @brief Categories
             */
            QString Categories;
            /**
             * @brief 程序是否在终端窗口中运行(bool)
             */
            QString Terminal ;
            /**
             * @brief 此应用支持打开的类型(核心)
             */
            QString MimeType;
            /**
             * @brief 应用程序的通用名称
             */
            QString GenericName;
            /**
             * @brief 中文名
             */
            QString NameZH;
            QString Create(QString Path);
            QString Create(QString Dir,QString pro,QString version);
            void SetContent();
            Desktop();
            void Clear();
    };
}
#endif // DESKTOP_H
