#include "donneur.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>
DONNEUR::DONNEUR()
{
     ID_DONNEUR=0;
    NOM="";
    PRENOM="" ;
    METIER="" ;
   SEXE="";



}
DONNEUR::DONNEUR(int ID_DONNEUR,QString NOM,QString  PRENOM,QString METIER,QString SEXE)
{this->ID_DONNEUR=ID_DONNEUR;this->NOM=NOM;this-> PRENOM= PRENOM;this->METIER=METIER;this-> SEXE= SEXE;}
int DONNEUR::getID_DONNEUR(){return ID_DONNEUR;}
QString DONNEUR:: getNOM(){return NOM;}
QString DONNEUR:: getPRENOM(){return PRENOM;}
QString  DONNEUR::getMETIER(){return METIER;}
QString DONNEUR:: getSEXE(){return SEXE;}


void DONNEUR::setID_DONNEUR(int ID_DONNEUR){this->ID_DONNEUR=ID_DONNEUR;}
void DONNEUR::setNOM(QString NOM){this->NOM=NOM;}
void DONNEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void DONNEUR::setMETIER(QString  METIER){this-> METIER= METIER;}
void DONNEUR::setSEXE(QString SEXE){this->SEXE=SEXE;}

bool DONNEUR::Ajouter()//zedthaa
{


QSqlQuery query;
QString ID_DONNEUR_string= QString::number(ID_DONNEUR);

query.prepare("INSERT INTO DONNEUR (ID_DONNEUR,NOM,PRENOM,METIER,SEXE) "
              "VALUES (:ID_DONNEUR, :NOM, :PRENOM,:METIER,:SEXE");
 //affecter le valeur dans bd
query.bindValue(":ID_DONNEUR",ID_DONNEUR_string);
query.bindValue(":NOM", NOM);
query.bindValue(":PRENOM", PRENOM);
query.bindValue(":METIER", METIER);
query.bindValue(":SEXE",SEXE);

return query.exec();


}
QSqlQueryModel * DONNEUR::afficher()
{ QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from DONNEUR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_DONNEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("METIER "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));


    return  model;

}
