#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>                       //Für c++ vectoren Notwendig
#include "cred.h"                       //Klasse für Verbindung zur Datenbank
#include "cp2kdata.h"                   //Datenstrucktur Klasse für File Parser

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    cred connection;                    //Globale Variable für MainWindow um Verbindungen aufzubauen


private slots:                          //Slots die vom MainWindow angesprochen werden können

    void on_setLog_clicked();           //öffnen des log-File Browsers
    void on_setXYZ_clicked();           //öffnen des xyz-File Browsers
    void on_setInput_clicked();         //öffnen des inp-file Browsers
    void on_updateTable_clicked();      //Resfresh Button
    void on_uploadButton_clicked();     //Upload Button
    void on_checkButton_clicked();      //Check button

private:
    Ui::MainWindow *ui;                 //ui
    cp2kData data;                      //Datenstrucktur File Parser
    void setDBdata();                   //Füllen der Datenbank
};

#endif // MAINWINDOW_H













