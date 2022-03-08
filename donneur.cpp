#include "donneur.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include <QtWidgets/QRadioButton>
DONNEUR::DONNEUR()
{
     ID_DONNEUR=0;
    NOM="";
    PRENOM="" ;
    METIER="" ;
   SEXE="";
   ID_TRESORIE=0;



}
DONNEUR::DONNEUR(int ID_DONNEUR,QString NOM,QString PRENOM,QString METIER,QString SEXE, int ID_TRESORIE)
{this->ID_DONNEUR=ID_DONNEUR;this->NOM=NOM;this-> PRENOM= PRENOM;this->METIER=METIER;this-> SEXE= SEXE;this->ID_TRESORIE=ID_TRESORIE;}
int DONNEUR::getID_DONNEUR(){return ID_DONNEUR;}
QString DONNEUR:: getNOM(){return NOM;}
QString DONNEUR:: getPRENOM(){return PRENOM;}
QString  DONNEUR::getMETIER(){return METIER;}
QString DONNEUR:: getSEXE(){return SEXE;}
int DONNEUR::getID_TRESORIE(){return ID_TRESORIE;}

void DONNEUR::setID_DONNEUR(int ID_DONNEUR){this->ID_DONNEUR=ID_DONNEUR;}
void DONNEUR::setNOM(QString NOM){this->NOM=NOM;}
void DONNEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void DONNEUR::setMETIER(QString  METIER){this-> METIER= METIER;}
void DONNEUR::setSEXE(QString SEXE){this->SEXE=SEXE;}
void DONNEUR::setID_TRESORIE(int ID_TRESORIE){this->ID_TRESORIE=ID_TRESORIE;}
bool DONNEUR::ajouter()//zedthaa
{


    QSqlQuery query;
    QString ID_DONNEUR_string= QString::number(ID_DONNEUR);
    QString ID_TRESORIE_string= QString::number(ID_TRESORIE);
    query.prepare("INSERT INTO DONNEUR (ID_DONNEUR,NOM,PRENOM,METIER,SEXE,ID_TRESORIE) "
                  "VALUES (:ID_DONNEUR, :NOM, :PRENOM,:METIER,:SEXE,:ID_TRESORIE)");
     //affecter le valeur dans bd
    query.bindValue(":ID_DONNEUR",ID_DONNEUR_string);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":METIER", METIER);
    query.bindValue(":SEXE",SEXE);
     query.bindValue(":ID_TRESORIE",ID_TRESORIE_string);

    return query.exec();


}
bool DONNEUR::supprimer(int ID_DONNEUR)
{

    QSqlQuery query;
    QString res=QString::number(ID_DONNEUR);
    query.prepare("DELETE FROM DONNEUR WHERE ID_DONNEUR= :ID_DONNEUR");
    query.bindValue(0,ID_DONNEUR);

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
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_TRESORIE"));


    return  model;

}
//trieee nom
QSqlQueryModel * DONNEUR::triernom()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DONNEUR ORDER BY NOM");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_DONNEUR"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("METIER"));
     model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
        model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID_TRESORIE"));



     return model;
 }
//trieee PREnom
QSqlQueryModel * DONNEUR::trierprenom()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DONNEUR ORDER BY PRENOM");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_DONNEUR"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("METIER"));
     model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
   model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID_TRESORIE"));


     return model;
 }
//trieee ID_DONNEUR
QSqlQueryModel * DONNEUR::trierid()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from DONNEUR ORDER BY ID_DONNEUR");
     model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_DONNEUR"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("METIER"));
     model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("ID_TRESORIE"));


     return model;
 }
bool DONNEUR::modifier(int ID_DONNEUR,QString NOM,QString PRENOM,QString METIER,QString SEXE,int ID_TRESORIE){
    QSqlQuery query;
    QString  ID_ADHERENT_string=QString::number( ID_DONNEUR);


       query.prepare(" UPDATE DONNEUR set ID_DONNEUR=:ID_DONNEUR ,NOM=:NOM,PRENOM=:PRENOM ,METIER=:METIER,  SEXE=:SEXE ,ID_TRESORIE=:ID_TRESORIE where ID_DONNEUR=:ID_DONNEUR");
       query.bindValue(":ID_DONNEUR",ID_ADHERENT_string);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":METIER",METIER);
        query.bindValue(":SEXE",SEXE);
        query.bindValue(":ID_TRESORIE",ID_TRESORIE);
       return query.exec();
}
