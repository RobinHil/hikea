#include "mainwindow.h"

#include <QApplication>

#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QTranslator translator;
    QString locale = QLocale::system().name();
    if (translator.load(":/i18n/s2_01_" + locale))
    {
        qDebug()<<"Traduction ..";
        a.installTranslator(&translator);
    }
    */
    MainWindow w;
    w.show();
    return a.exec();
}

