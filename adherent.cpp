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

    COTISATION=0;
    NUM_OPERATION=0;
    EMAIL="";


}

ADHERENT::ADHERENT(int ID_ADHERENT,QString NOM_ADHERENT,QString  PRENOM_ADHERENT, float COTISATION,int NUM_OPERATION,QString EMAIL)
{this->ID_ADHERENT=ID_ADHERENT;
    this->NOM_ADHERENT=NOM_ADHERENT;
    this-> PRENOM_ADHERENT= PRENOM_ADHERENT;

    this->COTISATION=COTISATION;
    this->NUM_OPERATION=NUM_OPERATION;
this->EMAIL=EMAIL;}



int ADHERENT::getID_ADHERENT(){return ID_ADHERENT;}
QString ADHERENT:: getNOM_ADHERENT(){return NOM_ADHERENT;}
QString ADHERENT:: getPRENOM_ADHERENT(){return PRENOM_ADHERENT;}

float ADHERENT::getCOTISATION(){return COTISATION;}
int ADHERENT::getNUM_OPERATION(){return NUM_OPERATION;}
QString ADHERENT:: getEMAIL(){return EMAIL;}

void ADHERENT::setID_ADHERENT(int ID_ADHERENT){this->ID_ADHERENT=ID_ADHERENT;}
void ADHERENT::setNOM_ADHERENT(QString NOM_ADHERENT){this->NOM_ADHERENT=NOM_ADHERENT;}
void ADHERENT::setPRENOM_ADHERENT(QString PRENOM_ADHERENT){this->PRENOM_ADHERENT=PRENOM_ADHERENT;}

void ADHERENT::setCOTISATION(float  COTISATION){this-> COTISATION= COTISATION;}

void ADHERENT::setNUM_OPERATION(int NUM_OPERATION){this->NUM_OPERATION=NUM_OPERATION;}
void ADHERENT::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}

bool ADHERENT::ajouter()//zedthaa
{


QSqlQuery query;//declarer requete
//convertie int  en chain de caractere
  QString NUM_OP_string= QString::number(NUM_OPERATION);
QString ID_ADHERENT_string= QString::number(ID_ADHERENT);
QString COTISATION_string=QString::number(COTISATION);
//n7thro l reqet
query.prepare("INSERT INTO ADHERENT (ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,COTISATION,NUM_OP,EMAIL) "
              "VALUES (:ID_ADHERENT, :NOM_ADHERENT, :PRENOM_ADHERENT,:COTISATION,:NUM_OP,:EMAIL)");
 //affecter le valeur dans bd
//execution
query.bindValue(":ID_ADHERENT",ID_ADHERENT_string);
query.bindValue(":NOM_ADHERENT", NOM_ADHERENT);
query.bindValue(":PRENOM_ADHERENT", PRENOM_ADHERENT);
query.bindValue(":COTISATION", COTISATION_string);
query.bindValue(":NUM_OP",NUM_OP_string);
query.bindValue(":EMAIL",EMAIL);

return query.exec();


}

QSqlQueryModel *ADHERENT::afficher()
{ QSqlQueryModel * model=new QSqlQueryModel();


    model->setQuery("select * from ADHERENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_ADHERENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("COTISATION "));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_OP"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));



    return  model;

}

bool ADHERENT::supprimer(int ID_ADHERENT)
{

    QSqlQuery query;
    query.prepare("DELETE FROM ADHERENT WHERE ID_ADHERENT= :ID_ADHERENT");
    query.bindValue(":ID_ADHERENT",ID_ADHERENT);

    return query.exec();

}
bool ADHERENT::modifier(int ID_ADHERENT,QString NOM_ADHERENT,QString PRENOM_ADHERENT,float COTISATION, int NUM_OPERATION,QString EMAIL){
    QSqlQuery query;
    QString  ID_ADHERENT_string=QString::number( ID_ADHERENT);
    QString  COTISATION_string=QString::number( COTISATION);
     QString  NUM_OPERATION_string=QString::number( NUM_OPERATION);

       query.prepare(" UPDATE ADHERENT set NOM_ADHERENT=:NOM_ADHERENT,PRENOM_ADHERENT=:PRENOM_ADHERENT , COTISATION=:COTISATION, NUM_OP=:NUM_OP, EMAIL=:EMAIL where ID_ADHERENT=:ID_ADHERENT");

       query.bindValue(":ID_ADHERENT",ID_ADHERENT);
       query.bindValue(":NOM_ADHERENT",NOM_ADHERENT);
       query.bindValue(":PRENOM_ADHERENT",PRENOM_ADHERENT);

 query.bindValue(":COTISATION",COTISATION_string);

           query.bindValue(":NUM_OP",NUM_OPERATION_string);
           query.bindValue(":EMAIL",EMAIL);

       return query.exec();
}
