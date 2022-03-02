#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H
#include <QString>
#include <QDate>
#include <QSqlQuery>

#include <QtDebug>

#include<QSqlQueryModel>

#include <QtSql/QSqlQueryModel>
#include <QMainWindow>

class Dossier_medical
{
public:
    Dossier_medical();
    Dossier_medical(int,QString,QString,QString,QString,QDate,double,QString,double,QString,QString,QString);
    int getnum_doss();
    QString getespece();
     QString getmaladie();
     QString getnom_animal();
     QString getrace();
    QDate getdate_naiss();
    double getpoids();
     QString getsexe();
      double gettemperature();
     QString getsterilisation();

     QString getetat_vaccin();
     QString gettraitement();

     void setnum_doss(int);
    void setespece(QString);
     void setmaladie(QString);
     void setnom_animal(QString);
     void setrace(QString);
    void setdate_naiss(QDate);
   void setpoids(double);
     void setsexe(QString);
      void settemperature(double);
     void setsterilisation(QString);

    void setetat_vaccin(QString);
     void settraitement(QString);
 bool ajouter();
 QSqlQueryModel* afficher();
 bool supprimer(int);
  bool modifier(int,QString,QString,QString,QString,QDate,double,QString,double,QString,QString,QString);
  QSqlQueryModel * triernum();
  QSqlQueryModel * trierdate();
  QSqlQueryModel * triernom();
private:
    int num_doss;
    QString espece, maladie, nom_animal, race;
    QDate date_naiss;
    double poids;
    QString sexe;
    double  temperature;

   QString sterilisation,etat_vaccin, traitement;





};

#endif // DOSSIER_MEDICAL_H
