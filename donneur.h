#ifndef DONNEUR_H
#define DONNEUR_H

#include <QString>
#include<QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMainWindow>
#include<QSqlQuery>


class DONNEUR
{
public:
    DONNEUR();
    DONNEUR(int,QString,QString,QString,QString);
    int getID_DONNEUR();
    QString getNOM();
     QString getPRENOM();
     QString getMETIER();
    QString getSEXE();



     void setID_DONNEUR(int);
    void setNOM(QString);
    void setPRENOM(QString);
     void setMETIER(QString);
    void setSEXE(QString);
     bool Ajouter();
     QSqlQueryModel* afficher();


private:
    int ID_DONNEUR;
    QString NOM, PRENOM, METIER, SEXE;



};



#endif // DONNEUR_H
