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
    ADHERENT(int,QString,QString,QString,QString,float);
    int getID_ADHERENT();
    QString getNOM_ADHERENT();
     QString getPRENOM_ADHERENT();
     QString getMETIER_ADHERENT();
     QString getSEXE();
    float getCOTISATION();


     void setID_ADHERENT(int);
    void setNOM_ADHERENT(QString);
    void setPRENOM_ADHERENT(QString);
     void setMETIER_ADHERENT(QString);
    void setSEXE(QString);
    void setCOTISATION(float);

    bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int,QString,QString,QString,QString,float);



private:
    int ID_ADHERENT;
    QString NOM_ADHERENT, PRENOM_ADHERENT, METIER_ADHERENT,SEXE;
    float COTISATION;


};




#endif // ADHERENT_H
