#include <QApplication>
#include "mainwindow.h"
#include "startwindow.h"
#include <QDebug>
#include "keypresseater.h"

#include "config.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
     QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));


    QApplication a(argc, argv);

    KeyPressEater *keyPressEater = new KeyPressEater();
    a.installEventFilter(keyPressEater);


    startWindow st(0, keyPressEater);
    st.show();

//    MainWindow w;
//    w.show();

   //Config* cfg = new Config();
   //qDebug() << Config::shit;
   //qDebug() << cfg->shit;
// zzz
    // I like it
  // qDebug() << Config::firstrun;
  // qDebug() << Config::firstrun;
    //fuck::e=5;
    //Config::x_pos=5;
   // qDebug() << Config::x_pos;
//    Config conf;

 //   qDebug() <<"YEAH " << Config::settingsProperties.firstrun;



    return a.exec();
}
