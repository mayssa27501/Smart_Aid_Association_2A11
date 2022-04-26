#include "dossier_medical.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QObject>
#include <QTableView>
Dossier_medical::Dossier_medical()
{
     num_doss=0;
    espece="";
    maladie="" ;
    nom_animal="";
    race="";
     date_naiss =QDate::currentDate();
     poid=0;
     sexe="";
     temperature=0;
     sterilisation="";

    etat_vaccin="";
    traitement="";
id_employe=0;

}
Dossier_medical::Dossier_medical(int num_doss,QString espece,QString maladie,QString nom_animal,QString race,QDate date_naiss,double poid,QString sexe,double temperature,QString sterilisation,QString etat_vaccin,QString traitement,int id_employe)
{this->num_doss=num_doss;this->espece=espece;this->maladie=maladie;this->nom_animal=nom_animal;this->race=race;this->date_naiss=date_naiss;this->poid=poid;this->sexe=sexe;this->temperature=temperature;this->sterilisation=sterilisation;this->etat_vaccin=etat_vaccin;this->traitement=traitement;this->id_employe=id_employe;}
int Dossier_medical::getnum_doss(){return num_doss;}
QString Dossier_medical:: getespece(){return espece;}
QString  Dossier_medical::getmaladie(){return maladie;}
QString Dossier_medical:: getnom_animal(){return nom_animal;}
QString Dossier_medical::getrace(){return race;}
QDate Dossier_medical:: getdate_naiss(){return date_naiss;}
double Dossier_medical::getpoid(){return poid;}
QString Dossier_medical::getsexe(){return sexe;}
double Dossier_medical::gettemperature(){return temperature;}
QString Dossier_medical::getsterilisation(){return sterilisation;}

QString Dossier_medical::getetat_vaccin(){return  etat_vaccin;}
QString Dossier_medical::gettraitement(){return traitement;}
int Dossier_medical::getid_employe(){return id_employe;}

void Dossier_medical::setnum_doss(int num_doss){this->num_doss=num_doss;}
void Dossier_medical::setespece(QString espece){this->espece=espece;}
void Dossier_medical::setmaladie(QString maladie){this->maladie=maladie;}
void Dossier_medical::setnom_animal(QString nom_animal){this->nom_animal=nom_animal;}
void Dossier_medical::setrace(QString race){this->race=race;}
void Dossier_medical::setdate_naiss(QDate date_naiss){this->date_naiss=date_naiss;}
void Dossier_medical::setpoid(double poid){this->poid=poid;}
void Dossier_medical::setsexe(QString sexe){this->sexe=sexe;}
void Dossier_medical::settemperature(double temperature){this->temperature=temperature;}
void Dossier_medical::setsterilisation(QString sterilisation){this->sterilisation=sterilisation;}

void Dossier_medical::setetat_vaccin(QString etat_vaccin){this->etat_vaccin=etat_vaccin;}
void Dossier_medical::settraitement(QString traitement){this->traitement=traitement;}
void Dossier_medical::setid_employe(int id_employe){this->id_employe=id_employe;}

bool Dossier_medical::ajouter()
{
    QSqlQuery query;
    QString numD_string=QString::number(num_doss);
    QString num_poid_string=QString::number(poid);
    QString num_temp_string=QString::number(temperature);
     QString id_employe_string=QString::number(id_employe);
         query.prepare("INSERT INTO DOSSIER_MEDICAL (NUM_DOSS,ESPECE,MALADIE,NOM_ANIMAL,RACE,DATE_NAISS,POID,SEXE, TEMPERATURE,STERILISATION,ETAT_VACCIN,TRAITEMENT,ID_EMPLOYE) "
                       "VALUES (:NUM_DOSS,:ESPECE,:MALADIE,:NOM_ANIMAL,:RACE,:DATE_NAISS,:POID,:SEXE,:TEMPERATURE,:STERILISATION, :ETAT_VACCIN,:TRAITEMENT,:ID_EMPLOYE)");
         query.bindValue(":NUM_DOSS", numD_string);
         query.bindValue(":ESPECE", espece);
         query.bindValue(":MALADIE", maladie);
         query.bindValue(":NOM_ANIMAL",nom_animal);
         query.bindValue(":RACE", race);
         query.bindValue(":DATE_NAISS", date_naiss);
         query.bindValue(":POID", num_poid_string);
         query.bindValue(":SEXE", sexe);
           query.bindValue(":TEMPERATURE", num_temp_string);
         query.bindValue(":STERILISATION", sterilisation);

         query.bindValue(":ETAT_VACCIN", etat_vaccin);
         query.bindValue(":TRAITEMENT", traitement);
          query.bindValue(":ID_EMPLOYE", id_employe_string);

         return query.exec();

}
bool Dossier_medical::supprimer(int num_doss)
{
    QSqlQuery query;
     QString numD_string=QString::number(num_doss);
         query.prepare("Delete from DOSSIER_MEDICAL where NUM_DOSS=:NUM_DOSS ");
         query.bindValue(":NUM_DOSS", numD_string);
         return query.exec();
}

 QSqlQueryModel * Dossier_medical::afficher()
{ QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from DOSSIER_MEDICAL");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_DOSS"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM_ANIMAL "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_NAISS"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("ESPECE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("RACE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("POID "));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("MALADIE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("TEMPERATURE"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("STERILISATION "));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("ETAT_VACCIN"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("TRAITEMENT"));
    model->setHeaderData(12,Qt::Horizontal, QObject::tr("ID_EMPLOYE"));

    return  model;

}
 bool Dossier_medical::modifier(int num_doss,QString espece,QString maladie,QString nom_animal,QString race,QDate date_naiss,double poid,QString sexe,double temperature,QString sterilisation,QString etat_vaccin,QString traitement,int id_employe){
     QSqlQuery query;
     QString numD_string=QString::number(num_doss);
     QString num_poid_string=QString::number(poid);
     QString num_temp_string=QString::number(temperature);
     QString id_employe_string=QString::number(id_employe);
        query.prepare(" UPDATE DOSSIER_MEDICAL set espece=:ESPECE, maladie=:MALADIE ,nom_animal=:NOM_ANIMAL, race=:RACE, date_naiss=:DATE_NAISS,poid=:POID,sexe=:SEXE,temperature=:TEMPERATURE,sterilisation=:STERILISATION,etat_vaccin=:ETAT_VACCIN,traitement=:TRAITEMENT,id_employe=:ID_EMPLOYE where num_doss=:NUM_DOSS");
        query.bindValue(":NUM_DOSS", numD_string);
        query.bindValue(":ESPECE", espece);
        query.bindValue(":MALADIE", maladie);
        query.bindValue(":NOM_ANIMAL",nom_animal);
        query.bindValue(":RACE", race);
        query.bindValue(":DATE_NAISS", date_naiss);
        query.bindValue(":POID", num_poid_string);
        query.bindValue(":SEXE", sexe);
          query.bindValue(":TEMPERATURE", num_temp_string);
        query.bindValue(":STERILISATION", sterilisation);

        query.bindValue(":ETAT_VACCIN", etat_vaccin);
        query.bindValue(":TRAITEMENT", traitement);
        query.bindValue(":ID_EMPLOYE", id_employe_string);
        return query.exec();
 }
 QSqlQueryModel * Dossier_medical::triernum()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DOSSIER_MEDICAL ORDER BY NUM_DOSS");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_DOSS"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("ESPECE"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("MALADIE"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("NOM_ANIMAL "));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("RACE"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISS"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("POID"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("TEMPERATURE"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("STERILISATION "));
     model->setHeaderData(10,Qt::Horizontal,QObject::tr("ETAT_VACCIN"));
     model->setHeaderData(11,Qt::Horizontal,QObject::tr("TRAITEMENT"));
     model->setHeaderData(12,Qt::Horizontal,QObject::tr("ID_EMPLOYE"));

     return model;
 }


 QSqlQueryModel * Dossier_medical::trierdate()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DOSSIER_MEDICAL ORDER BY DATE_NAISS");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_DOSS"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("ESPECE"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("MALADIE"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("NOM_ANIMAL "));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("RACE"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISS"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("POID"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("TEMPERATURE"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("STERILISATION "));
     model->setHeaderData(10,Qt::Horizontal,QObject::tr("ETAT_VACCIN"));
     model->setHeaderData(11,Qt::Horizontal,QObject::tr("TRAITEMENT"));

     model->setHeaderData(12,Qt::Horizontal,QObject::tr("ID_EMPLOYE"));

     return model;
 }
 QSqlQueryModel * Dossier_medical::triernom()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DOSSIER_MEDICAL ORDER BY NOM_ANIMAL");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_DOSS"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("ESPECE"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("MALADIE"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("NOM_ANIMAL "));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("RACE"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISS"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("POID"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("TEMPERATURE"));
     model->setHeaderData(9,Qt::Horizontal,QObject::tr("STERILISATION "));
     model->setHeaderData(10,Qt::Horizontal,QObject::tr("ETAT_VACCIN"));
     model->setHeaderData(11,Qt::Horizontal,QObject::tr("TRAITEMENT"));

     model->setHeaderData(12,Qt::Horizontal,QObject::tr("ID_EMPLOYE"));

     return model;
 }

 void Dossier_medical::recherche(QTableView * table ,int num_doss,QString nom, QString maladie )
 {
     QSqlQueryModel *model= new QSqlQueryModel();
     QString num_string=QString::number(num_doss);


     QSqlQuery *query=new QSqlQuery;
     query->prepare("select * from DOSSIER_MEDICAL where NUM_DOSS like '%"+num_string+"%' or NOM_ANIMAL like '%"+nom+"%' or MALADIE like '%"+maladie+"%' ;");


     query->exec();
     model->setQuery(*query);
     table->setModel(model);
     table->show();

 }

 int Dossier_medical::dossierExist(int id)
 {
     QString idS = QString::number(id);
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DOSSIER_MEDICAL wHERE NUM_DOSS = "+idS);


     return model->rowCount();
 }


 bool Dossier_medical::modifier_ardui(QString mtrcl,QString data_ar)
 {
     QSqlQuery query;
     query.prepare("UPDATE DOSSIER_MEDICAL set TYPE_MVT=:data_ar where NUM_DOSS=:mtrcl");
     query.bindValue(":mtrcl", mtrcl);
     query.bindValue(":data_ar", data_ar);

     return query.exec();
 }
