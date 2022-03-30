#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("data_db");
db.setUserName("daly");//inserer nom de l'utilisateur
db.setPassword("daly");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;




    return  test;
}

