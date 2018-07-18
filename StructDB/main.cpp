#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;   //Erstellen der GUI
    w.show();       //GUI Laden/öffnen

    return a.exec();
}
