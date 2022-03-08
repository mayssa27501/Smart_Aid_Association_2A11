#include "connection.h"
//test
Connection::Connection()
{

}

bool Connection::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("testbd");
db.setUserName("ferchichi");//inserer nom de l'utilisateur
db.setPassword("ferchichi");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

