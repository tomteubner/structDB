#include <QMainWindow>
#include <QMessageBox>
#include "/usr/local/mysql/include/mysql.h"
#include "cred.h"
#include <vector>

cred::cred()
{
    /*
    cred::IP = "127.0.0.1";
    cred::Port = 3308;
    cred::DB = "DB";
    cred::Table = "Table";
    cred::UserName = "User";
    cred::Password = "";
    */
}

MYSQL mysql;
MYSQL * conn;

bool cred::set_ip(std::string ip){
    cred::IP = QString::fromStdString(ip);
    return true;
}
bool cred::set_port(int port){
    cred::Port = port;
    return true;
}
bool cred::set_db(std::string db){
    cred::DB = QString::fromStdString(db);
    return true;
}
bool cred::set_table(std::string table){
    cred::Table = QString::fromStdString(table);
    return true;
}
bool cred::set_username(std::string username){
    cred::UserName = QString::fromStdString(username);
    return true;
}
bool cred::set_password(std::string password){
    cred::Password = QString::fromStdString(password);
    return true;
}


std::string cred::get_ip(){
    return cred::IP.toStdString();
}
int cred::get_port(){
    return cred::Port;
}
std::string cred::get_db(){
    return cred::DB.toStdString();
}
std::string cred::get_table(){
    return cred::Table.toStdString();
}
std::string cred::get_username(){
    return cred::UserName.toStdString();
}
std::string cred::get_password(){
    return cred::Password.toStdString();
}

bool cred::openConnection(bool printSuccess)
{
    mysql_init( &mysql );
    // Timeout für Verbindungen setzen
    unsigned int conn_timeout=1;
    mysql_options(&mysql,MYSQL_OPT_CONNECT_TIMEOUT, &conn_timeout);
    //Cred Daten an Connection übergeben
    conn = mysql_real_connect
    (
        &mysql,
        cred::IP.toStdString().c_str(),          //IP
        cred::UserName.toStdString().c_str(),    //user
        cred::Password.toStdString().c_str(),    //passwd
        cred::DB.toStdString().c_str(),          //db
        cred::Port,                              //port
        0,
        0
    );
      // Wenn Connection Fehlschlägt, dann Error Box mit Error Message
      if( !conn )
      {
          QString error = mysql_error(&mysql);
          QMessageBox Msgbox;
          Msgbox.setText(error);
          Msgbox.exec();
          return false;
      }
      else
      {
          if (printSuccess == 1)
          {
                QMessageBox Msgbox;
                Msgbox.setText("Successfully connected to database");
                Msgbox.exec();
          }
          return true;
      }
}

void cred::closeConnection()
{
   mysql_close(conn);
}

std::vector<std::vector<std::string> > cred::executeReturnQuery(QString Query)
{
    //Wenn Query Fehlschlägt
    if (mysql_query(conn, Query.toStdString().c_str()))
    {
        typedef std::vector<std::string> Dim1;
        typedef std::vector<Dim1> Matrix2D;
        Matrix2D result(1,Dim1(1));

        result[0][0] = "error";
        return result;
    }
    else
    {
        //Variablen für Connector
        MYSQL_RES * resultset;
        MYSQL_ROW row;
        MYSQL_FIELD * fields;
        //Rückgabe von connection speichern
        resultset = mysql_store_result( conn );
        fields = mysql_fetch_fields(resultset);
        //Anzahl von Collums und Rows Speichern
        int numRows = mysql_num_rows( resultset ) ;
        int numFields = mysql_num_fields( resultset );
        //Erstellen des Rückgabe Vector: 2D, <Anzahl Collums><Anzahl Rows + 1>
        //<Anzahl Collums><0> ist Name von Collum
        typedef std::vector<std::string> Dim1;
        typedef std::vector<Dim1> Matrix2D;
        Matrix2D result(numFields,Dim1(numRows+1));
        //Rückgabe der connection durchgehen und Collum Namen im Rückgabe Vector speichern
        for (int i = 0; i < numFields; i++)
        {
            std::string str(fields[i].name);
            result[i][0] = str;
        }

        int i = 0;
        //Solange es Rows in der Rückgabe von Connection gibt,
        while( (row = mysql_fetch_row( resultset )) )
        {
            //Einträge der einzelnen Row Collum im Rückgabe Vector speichern
            for (int ii = 0; ii < numFields; ii++)
            {
                if (row[ii] == NULL)
                {
                    result[ii][i+1] = "NULL";
                }
                else
                {
                    std::string str(row[ii]);
                    result[ii][i+1] = str;
                }
            }
            i++;
        }
        //Rückgabe Vector übergeben
        return result;
    }
}

std::string cred::executeQuery(QString Query)
{
    //Wenn Query Fehlschlägt
    if (mysql_query(conn, Query.toStdString().c_str()))
    {
        return "fail";
    }
    else
    {
        return "success";
    }

}
