#ifndef CRED_H
#define CRED_H

#include <QMainWindow>

class cred
{
public:
    cred();

    bool openConnection(bool printSuccess);
    void closeConnection();
    std::vector<std::vector<std::string> > executeReturnQuery(QString Query);
    std::string executeQuery(QString Query);

    QString IP;
    int Port;
    QString DB;
    QString Table;
    QString UserName;
    QString Password;

    bool set_ip(std::string ip);
    bool set_port(int port);
    bool set_db(std::string db);
    bool set_table(std::string table);
    bool set_username(std::string username);
    bool set_password(std::string password);

    std::string get_ip();
    int get_port();
    std::string get_db();
    std::string get_table();
    std::string get_username();
    std::string get_password();


};

#endif // CRED_H
