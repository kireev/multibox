#include "config.h"

SimpleStruct Config::settingsProperties;

Config::Config()
{
    settings = new QSettings(QApplication::applicationDirPath()+"/multidrop.ini", QSettings::IniFormat);
    if (QFile(QApplication::applicationDirPath()+"/multidrop.ini").exists())
    {
        ReadConfig();
        return;
    }

    //Run for the first time



    //firstrun = settings->value("FirstRun").value<bool>();
    //settings->setValue("FirstRun",1);
    //qDebug() << settingsProperties.firstrun;
    //ReadConfig();
}

void Config::ReadConfig()
{
    qDebug() << "ReadConf";
    settingsProperties.firstrun=settings->value("FirstRun").value<bool>();
    qDebug() << settingsProperties.firstrun;
}
