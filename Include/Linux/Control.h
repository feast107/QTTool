#ifndef CONTROL_H
#define CONTROL_H
#include <QString>
#include <QSysInfo>
class Control
{
    public:
        /**
         * @brief 平台架构
         */
        QString Architecture = QSysInfo::currentCpuArchitecture().toLower();
        /**
         * @brief 程序名称
         */
        QString Package;
        /**
         * @brief 源代码名称
         */
        QString Source;
        /**
         * @brief 程序版本
         */
        QString Version = "1.0.0";
        /**
         * @brief 软件类别
         */
        QString Section = "utils";
        /**
         * @brief 重要程度
         */
        QString Priority;
        /**
         * @brief 程序依赖的库文件
         */
        QString Depends;
        /**
         * @brief Multi_Arch
         */
        QString Multi_Arch = "foreign";
        /**
         * @brief Maintainer
         */
        QString Maintainer = "ZBH@zbform.cn";
        /**
         * @brief 程序说明
         */
        QString Description = "Description";
        /**
         * @brief 是否可以卸载 yes/no
         */
        bool Essential = true;

        Control();
        QString Create(QString PackageDir);
};

#endif // CONTROL_H
