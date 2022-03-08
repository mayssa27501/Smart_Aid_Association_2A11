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

    DONNEUR(int,QString,QString,QString,QString, int);
    int getID_DONNEUR();
    QString getNOM();
     QString getPRENOM();
     QString getMETIER();
    QString getSEXE();
int getID_TRESORIE();


     void setID_DONNEUR(int);
    void setNOM(QString);
    void setPRENOM(QString);
     void setMETIER(QString);
    void setSEXE(QString);
    void setID_TRESORIE(int);
     bool ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel * triernom();
       QSqlQueryModel * trierprenom();
       QSqlQueryModel * trierid();
     bool supprimer(int);
     bool modifier(int,QString,QString,QString,QString,int);


private:
    int ID_DONNEUR ,ID_TRESORIE;
    QString NOM, PRENOM, METIER, SEXE;



};



#endif // DONNEUR_H
//DONNEUR D1(aeaze);
