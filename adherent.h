#ifndef ADHERENT_H
#define ADHERENT_H
#include <QString>
#include<QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QMainWindow>
#include<QSqlQuery>

class ADHERENT
{

public:
   ADHERENT();
    ADHERENT(int,QString,QString,float,int,QString);
    int getID_ADHERENT();
    QString getNOM_ADHERENT();
     QString getPRENOM_ADHERENT();


    float getCOTISATION();
    int getNUM_OPERATION();
    QString getEMAIL();


     void setID_ADHERENT(int);
    void setNOM_ADHERENT(QString);
    void setPRENOM_ADHERENT(QString);

    void setCOTISATION(float);
    void setNUM_OPERATION(int);
    void setEMAIL(QString);

    bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int,QString,QString,float,int,QString);



private:
    int ID_ADHERENT ,NUM_OPERATION;
    QString NOM_ADHERENT, PRENOM_ADHERENT,EMAIL ;
    double COTISATION;


};




#endif // ADHERENT_H
