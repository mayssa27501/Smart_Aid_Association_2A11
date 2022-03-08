#include "adherent.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>

ADHERENT::ADHERENT()
{
     ID_ADHERENT=0;
    NOM_ADHERENT="";
    PRENOM_ADHERENT="" ;
    METIER_ADHERENT="" ;
   SEXE="";
    COTISATION=0;
    ID_TRESORIE=0;


}

ADHERENT::ADHERENT(int ID_ADHERENT,QString NOM_ADHERENT,QString  PRENOM_ADHERENT,QString METIER_ADHERENT,QString SEXE, float COTISATION,int ID_TRESORIE)
{this->ID_ADHERENT=ID_ADHERENT;
    this->NOM_ADHERENT=NOM_ADHERENT;
    this-> PRENOM_ADHERENT= PRENOM_ADHERENT;
    this->METIER_ADHERENT=METIER_ADHERENT;
    this-> SEXE= SEXE;
    this->COTISATION=COTISATION;
    this->ID_TRESORIE=ID_TRESORIE;}



int ADHERENT::getID_ADHERENT(){return ID_ADHERENT;}
QString ADHERENT:: getNOM_ADHERENT(){return NOM_ADHERENT;}
QString ADHERENT:: getPRENOM_ADHERENT(){return PRENOM_ADHERENT;}
QString  ADHERENT::getMETIER_ADHERENT(){return METIER_ADHERENT;}
QString  ADHERENT::getSEXE(){return SEXE;}
float ADHERENT::getCOTISATION(){return COTISATION;}
int ADHERENT::getID_TRESORIE(){return ID_TRESORIE;}

void ADHERENT::setID_ADHERENT(int ID_ADHERENT){this->ID_ADHERENT=ID_ADHERENT;}
void ADHERENT::setNOM_ADHERENT(QString NOM_ADHERENT){this->NOM_ADHERENT=NOM_ADHERENT;}
void ADHERENT::setPRENOM_ADHERENT(QString PRENOM_ADHERENT){this->PRENOM_ADHERENT=PRENOM_ADHERENT;}
void ADHERENT::setMETIER_ADHERENT(QString  METIER_ADHERENT){this-> METIER_ADHERENT= METIER_ADHERENT;}
void ADHERENT::setSEXE(QString SEXE){this->SEXE=SEXE;}
void ADHERENT::setCOTISATION(float  COTISATION){this-> COTISATION= COTISATION;}

void ADHERENT::setID_TRESORIE(int ID_TRESORIE){this->ID_TRESORIE=ID_TRESORIE;}

bool ADHERENT::ajouter()//zedthaa
{


QSqlQuery query;//declarer requete
//convertie int  en chain de caractere
QString ID_ADHERENT_string= QString::number(ID_ADHERENT);
QString COTISATION_string=QString::number(COTISATION);
//n7thro l reqet
query.prepare("INSERT INTO ADHERENT (ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,METIER_ADHERENT,SEXE,COTISATION,ID_TRESORIE) "
              "VALUES (:ID_ADHERENT, :NOM_ADHERENT, :PRENOM_ADHERENT,:METIER_ADHERENT,:SEXE,:COTISATION,:ID_TRESORIE)");
 //affecter le valeur dans bd
query.bindValue(":ID_ADHERENT",ID_ADHERENT_string);
query.bindValue(":NOM_ADHERENT", NOM_ADHERENT);
query.bindValue(":PRENOM_ADHERENT", PRENOM_ADHERENT);
query.bindValue(":METIER_ADHERENT", METIER_ADHERENT);
query.bindValue(":SEXE",SEXE);
query.bindValue(":COTISATION",COTISATION_string);
query.bindValue(":ID_TRESORIE",ID_TRESORIE);
return query.exec();


}

QSqlQueryModel * ADHERENT::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from ADHERENT");
    //nrak7oo behom lheader
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_ADHERENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_ADHERENT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_ADHERENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("METIER_ADHERENT "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("COTISATION"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_TRESORIE"));

    return  model;

}
bool ADHERENT::supprimer(int ID_ADHERENT)
{

    QSqlQuery query;
    query.prepare("DELETE FROM ADHERENT WHERE ID_ADHERENT= :ID_ADHERENT");
    query.bindValue(":ID_ADHERENT",ID_ADHERENT);

    return query.exec();

}
bool ADHERENT::modifier(int ID_ADHERENT,QString NOM_ADHERENT,QString PRENOM_ADHERENT,QString METIER_ADHERENT,QString SEXE,float COTISATION, int ID_TRESORIE){
    QSqlQuery query;
    QString  ID_ADHERENT_string=QString::number( ID_ADHERENT);
    QString  COTISATION_string=QString::number( COTISATION);
     QString  ID_TRESORIE_string=QString::number( ID_TRESORIE);

       query.prepare(" UPDATE ADHERENT set ID_ADHERENT=:ID_ADHERENT ,NOM_ADHERENT=:NOM_ADHERENT,PRENOM_ADHERENT=:PRENOM_ADHERENT ,METIER_ADHERENT=:METIER_ADHERENT, COTISATION=:COTISATION, SEXE=:SEXE , ID_TRESORIE=:ID_TRESORIE where ID_ADHERENT=:ID_ADHERENT");

       query.bindValue(":ID_ADHERENT",ID_ADHERENT_string);
       query.bindValue(":NOM_ADHERENT",NOM_ADHERENT);
       query.bindValue(":PRENOM_ADHERENT",PRENOM_ADHERENT);
       query.bindValue(":METIER_ADHERENT",METIER_ADHERENT);
 query.bindValue(":COTISATION",COTISATION_string);
        query.bindValue(":SEXE",SEXE);
           query.bindValue(":ID_TRESORIE",ID_TRESORIE_string);
       return query.exec();
}
