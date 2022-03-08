#include "ressourcehumaine.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QString>
#include<mainwindow.h>
#include<QObject>
#include<QLabel>
#include<QVector>
#include<qiterator.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


RESSOURCE_HUMAINE::RESSOURCE_HUMAINE()
{
    CIN=0;
    NOM="";
    PRENOM="";
    METIER="";
    DATE_NAISSANCE=QDate::currentDate();
    TEL=0;
    SALAIRE=0;
    ID_TRESORIE=0;
    ID_STOCK=0;
    CIN_DIRIGEANT=0;



}
RESSOURCE_HUMAINE::RESSOURCE_HUMAINE(int CIN,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE,int ID_TRESORIE,int ID_STOCK,int CIN_DIRIGEANT)
{this->CIN=CIN;this->NOM=NOM;this->PRENOM=PRENOM;this->METIER=METIER;this->DATE_NAISSANCE=DATE_NAISSANCE;this->TEL=TEL;this->SALAIRE=SALAIRE;this->ID_TRESORIE=ID_TRESORIE;this->ID_STOCK=ID_STOCK;this->CIN_DIRIGEANT=CIN_DIRIGEANT;}
int RESSOURCE_HUMAINE::getCIN(){return CIN;}
QString RESSOURCE_HUMAINE::getNOM(){return NOM;}
QString RESSOURCE_HUMAINE::getPRENOM(){return PRENOM;}
QString  RESSOURCE_HUMAINE::getMETIER(){return METIER;}
QDate RESSOURCE_HUMAINE::getDATE_NAISSANCE(){return DATE_NAISSANCE;}
int RESSOURCE_HUMAINE::getTEL(){return TEL;}
float RESSOURCE_HUMAINE::getSALAIRE(){return SALAIRE;}
int RESSOURCE_HUMAINE::getID_TRESORIE(){return ID_TRESORIE;}
int RESSOURCE_HUMAINE::getID_STOCK(){return ID_STOCK;}
int RESSOURCE_HUMAINE::getCIN_DIRIGEANT(){return CIN_DIRIGEANT;}


void RESSOURCE_HUMAINE::setCIN(int CIN){this->CIN=CIN;}
void RESSOURCE_HUMAINE::setNOM(QString NOM){this->NOM=NOM;}
void RESSOURCE_HUMAINE::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void RESSOURCE_HUMAINE::setMETIER(QString METIER){this->METIER=METIER;}
void RESSOURCE_HUMAINE::setDATE_NAISSANCE(QDate DATE_NAISSANCE){this->DATE_NAISSANCE=DATE_NAISSANCE;}
void RESSOURCE_HUMAINE::setTEL(int TEL){this->TEL=TEL;}
void RESSOURCE_HUMAINE::setSALAIRE(float SALAIRE){this->SALAIRE=SALAIRE;}
void RESSOURCE_HUMAINE::setID_TRESORIE(int ID_TRESORIE){this->ID_TRESORIE=ID_TRESORIE;}
void RESSOURCE_HUMAINE::setID_STOCK(int ID_STOCK){this->ID_STOCK=ID_STOCK;}
void RESSOURCE_HUMAINE::setCIN_DIRIGEANT(int CIN_DIRIGEANT){this->CIN_DIRIGEANT=CIN_DIRIGEANT;}



bool RESSOURCE_HUMAINE::ajouter()
{
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);
    QString TRESORIE_string=QString::number(ID_TRESORIE);
    QString STOCK_string=QString::number(ID_STOCK);
    QString CIN_DIRIGEANT_string=QString::number(CIN_DIRIGEANT);


         query.prepare("INSERT INTO RESSOURCE_HUMAINE (CIN, NOM, PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,ID_TRESORIE,ID_STOCK,CIN_DIRIGEANT) "
                       "VALUES (:CIN,:NOM,:PRENOM,:METIER ,:DATE_NAISSANCE,:TEL,:SALAIRE,:ID_TRESORIE,:ID_STOCK,:CIN_DIRIGEANT)");
         query.bindValue(":CIN",CIN_string);
         query.bindValue(":NOM",NOM);
         query.bindValue(":PRENOM",PRENOM);
         query.bindValue(":METIER",METIER);
         query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
         query.bindValue(":TEL",TEL_string);
         query.bindValue(":SALAIRE",SALAIRE_string);
         query.bindValue(":ID_TRESORIE",TRESORIE_string);
         query.bindValue(":ID_STOCK",STOCK_string);
         query.bindValue(":CIN_DIRIGEANT",CIN_DIRIGEANT_string);

         return query.exec();

}

QSqlQueryModel* RESSOURCE_HUMAINE::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM RESSOURCE_HUMAINE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_TRESORIE"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_STOCK"));
          model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN_DIRIGEANT"));


    return model;

}

bool RESSOURCE_HUMAINE::supprimer(int CIN){
      QSqlQuery query;
      QString res=QString::number(CIN);
    query.prepare("Delete from RESSOURCE_HUMAINE where CIN=:CIN");
    query.bindValue(":CIN", res);

    return  query.exec();



}
bool RESSOURCE_HUMAINE::modifier(int CIN,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE,int ID_TRESORIE,int ID_STOCK,int CIN_DIRIGEANT){
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);
    QString TRESORIE_string=QString::number(ID_TRESORIE);
    QString STOCK_string=QString::number(ID_STOCK);
    QString CIN_DIRIGEANT_string=QString::number(CIN_DIRIGEANT);
       query.prepare(" UPDATE RESSOURCE_HUMAINE set CIN=:CIN ,NOM=:NOM,PRENOM=:PRENOM ,METIER=:METIER, DATE_NAISSANCE=:DATE_NAISSANCE, TEL=:TEL, SALAIRE=:SALAIRE,ID_TRESORIE=:ID_TRESORIE,ID_STOCK=:ID_STOCK,CIN_DIRIGEANT=:CIN_DIRIGEANT where CIN=:CIN");
       query.bindValue(":CIN",CIN_string);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":METIER",METIER);
       query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
       query.bindValue(":TEL",TEL_string);
       query.bindValue(":SALAIRE",SALAIRE_string);
       query.bindValue(":ID_TRESORIE",TRESORIE_string);
       query.bindValue(":ID_STOCK",STOCK_string);
       query.bindValue(":CIN_DIRIGEANT",CIN_DIRIGEANT_string);
       return query.exec();
}


QSqlQueryModel * RESSOURCE_HUMAINE::triercin()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_TRESORIE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_STOCK"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN_DIRIGEANT"));

    return model;
}
QSqlQueryModel * RESSOURCE_HUMAINE::trierdate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY DATE_NAISSANCE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_TRESORIE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_STOCK"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN_DIRIGEANT"));

    return model;
}

QSqlQueryModel * RESSOURCE_HUMAINE::triersalaire()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY SALAIRE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_TRESORIE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_STOCK"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("CIN_DIRIGEANT"));

    return model;
}

void RESSOURCE_HUMAINE::recherche(QTableView * table ,int cin,QString nom, QString metier )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString cin_string=QString::number(cin);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from RESSOURCE_HUMAINE where CIN like '%"+cin_string+"%' or NOM like '%"+nom+"%' or METIER like '%"+metier+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}

