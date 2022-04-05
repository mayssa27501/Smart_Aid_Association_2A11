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
    ADHERENT(int,QString,QString,QString,float,int);
    int getID_ADHERENT();
    QString getNOM_ADHERENT();
     QString getPRENOM_ADHERENT();
QString getemail();

    float getCOTISATION();
    int getNUM_OPERATION();


     void setID_ADHERENT(int);
    void setNOM_ADHERENT(QString);
    void setPRENOM_ADHERENT(QString);
 void setemail(QString);
    void setCOTISATION(float);
    void setNUM_OPERATION(int);

    bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int,QString,QString,QString,float,int);



private:
    int ID_ADHERENT ,NUM_OPERATION;
    QString NOM_ADHERENT, PRENOM_ADHERENT , EMAIL ;
    double COTISATION;


};




#endif // ADHERENT_H
