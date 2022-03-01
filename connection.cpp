#include "connection.h"
//test
Connection::Connection()
{

}

bool Connection::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Gestion_contrat");
db.setUserName("arslen");//inserer nom de l'utilisateur
db.setPassword("arslen");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

