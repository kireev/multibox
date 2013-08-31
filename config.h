#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QApplication>

struct SimpleStruct
{
    bool firstrun;
    int x_pos;
    int y_pos;
    int x_width;
    int y_width;


};

class Config
{

public:
    static SimpleStruct settingsProperties;
    QSettings* settings;

    Config();
    void ReadConfig();



};

#endif // CONFIG_H
