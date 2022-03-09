#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_sas");
db.setUserName("yousra");//inserer nom de l'utilisateur
db.setPassword("yousra");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
