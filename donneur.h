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

    DONNEUR(int,QString,QString,QString, int,QString);
    int getID_DONNEUR();
    QString getNOM();
     QString getPRENOM();
   QString getTYPE();
int getNUM_OPERATION();
QString getEMAIL();


     void setID_DONNEUR(int);
    void setNOM(QString);
    void setPRENOM(QString);
     void setTYPE(QString);
     void setEMAIL(QString);

    void setNUM_OPERATION(int);
     bool ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel * triernom();
       QSqlQueryModel * trierprenom();
       QSqlQueryModel * trierid();
     bool supprimer(int);
     bool modifier(int,QString,QString,QString,int,QString);
     //recherche
QSqlQueryModel * recherche(QString id_donneur);
QSqlQueryModel * rechercheN(QString nom);
QSqlQueryModel * rechercheP(QString prenom);
QSqlQueryModel* getAlertes();

private:
    int ID_DONNEUR ,NUM_OPERATION;
    QString NOM, PRENOM,TYPE,EMAIL ;




};



#endif // DONNEUR_H
//DONNEUR D1(aeaze);
