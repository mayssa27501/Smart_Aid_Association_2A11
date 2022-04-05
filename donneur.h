#ifndef DONNEUR_H
#define DONNEUR_H
#include <QTableView>
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
     QString getemail();
   QString getTYPE();
int getNUM_OPERATION();


     void setID_DONNEUR(int);
    void setNOM(QString);
    void setPRENOM(QString);
    void setemail(QString);
     void setTYPE(QString);

    void setNUM_OPERATION(int);
     bool ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel * triernom();
       QSqlQueryModel * trierprenom();
       QSqlQueryModel * trierid();
     bool supprimer(int);
     bool modifier(int,QString,QString,QString,QString,int);
     //recherche
QSqlQueryModel * recherche(QString id_donneur);
QSqlQueryModel * rechercheN(QString nom);
QSqlQueryModel * rechercheP(QString prenom);
private:
    int ID_DONNEUR ,NUM_OPERATION;
    QString NOM, PRENOM,TYPE ,email ;




};



#endif // DONNEUR_H
//DONNEUR D1(aeaze);
