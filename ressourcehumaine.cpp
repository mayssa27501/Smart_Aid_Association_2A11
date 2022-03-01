#include "ressourcehumaine.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>


RESSOURCE_HUMAINE::RESSOURCE_HUMAINE()
{
    CIN=0;
    NOM="";
    PRENOM="";
    METIER="";
    DATE_NAISSANCE=QDate::currentDate();
    TEL=0;
    SALAIRE=0;


}
RESSOURCE_HUMAINE::RESSOURCE_HUMAINE(int CIN,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE)
{this->CIN=CIN;this->NOM=NOM;this->PRENOM=PRENOM;this->METIER=METIER;this->DATE_NAISSANCE=DATE_NAISSANCE;this->TEL=TEL;this->SALAIRE=SALAIRE;}
int RESSOURCE_HUMAINE::getCIN(){return CIN;}
QString RESSOURCE_HUMAINE::getNOM(){return NOM;}
QString RESSOURCE_HUMAINE::getPRENOM(){return PRENOM;}
QString  RESSOURCE_HUMAINE::getMETIER(){return METIER;}
QDate RESSOURCE_HUMAINE::getDATE_NAISSANCE(){return DATE_NAISSANCE;}
int RESSOURCE_HUMAINE::getTEL(){return TEL;}
float RESSOURCE_HUMAINE::getSALAIRE(){return SALAIRE;}

void RESSOURCE_HUMAINE::setCIN(int CIN){this->CIN=CIN;}
void RESSOURCE_HUMAINE::setNOM(QString NOM){this->NOM=NOM;}
void RESSOURCE_HUMAINE::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void RESSOURCE_HUMAINE::setMETIER(QString METIER){this->METIER=METIER;}
void RESSOURCE_HUMAINE::setDATE_NAISSANCE(QDate DATE_NAISSANCE){this->DATE_NAISSANCE=DATE_NAISSANCE;}
void RESSOURCE_HUMAINE::setTEL(int TEL){this->TEL=TEL;}
void RESSOURCE_HUMAINE::setSALAIRE(float SALAIRE){this->SALAIRE=SALAIRE;}

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


    return model;

}


bool RESSOURCE_HUMAINE::ajouter()
{
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);


         query.prepare("INSERT INTO RESSOURCE_HUMAINE (CIN, NOM, PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE) "
                       "VALUES (:CIN,:NOM,:PRENOM,:METIER ,:DATE_NAISSANCE,:TEL,:SALAIRE)");
         query.bindValue(":CIN",CIN_string);
         query.bindValue(":NOM",NOM);
         query.bindValue(":PRENOM",PRENOM);
         query.bindValue(":METIER",METIER);
         query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
         query.bindValue(":TEL",TEL_string);
         query.bindValue(":SALAIRE",SALAIRE_string);
         return query.exec();

}


bool RESSOURCE_HUMAINE::supprimer(int CIN){
      QSqlQuery query;
      QString res=QString::number(CIN);
    query.prepare("Delete from RESSOURCE_HUMAINE where CIN=:CIN");
    query.bindValue(":CIN", res);

    return  query.exec();



}
bool RESSOURCE_HUMAINE::modifier(int CIN,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE){
    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);
       query.prepare(" UPDATE RESSOURCE_HUMAINE set CIN=:CIN ,NOM=:NOM,PRENOM=:PRENOM ,METIER=:METIER, DATE_NAISSANCE=:DATE_NAISSANCE, TEL=:TEL, SALAIRE=:SALAIRE where CIN=:CIN");
       query.bindValue(":CIN",CIN_string);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":METIER",METIER);
       query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
       query.bindValue(":TEL",TEL_string);
       query.bindValue(":SALAIRE",SALAIRE_string);
       return query.exec();
}
