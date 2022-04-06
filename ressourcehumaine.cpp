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
    ID_EMP=0;
    NOM="";
    PRENOM="";
    METIER="";
    DATE_NAISSANCE=QDate::currentDate();
    TEL=0;
    SALAIRE=0;
    VILLE="";
    ID_DIRIGEANT=0;


}
RESSOURCE_HUMAINE::RESSOURCE_HUMAINE(int ID_EMP,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE,QString VILLE,int ID_DIRIGEANT)
{this->ID_EMP=ID_EMP;this->NOM=NOM;this->PRENOM=PRENOM;this->METIER=METIER;this->DATE_NAISSANCE=DATE_NAISSANCE;this->TEL=TEL;this->SALAIRE=SALAIRE;this->VILLE=VILLE;this->ID_DIRIGEANT=ID_DIRIGEANT;}
int RESSOURCE_HUMAINE::getID_EMP(){return ID_EMP;}
QString RESSOURCE_HUMAINE::getNOM(){return NOM;}
QString RESSOURCE_HUMAINE::getPRENOM(){return PRENOM;}
QString  RESSOURCE_HUMAINE::getMETIER(){return METIER;}
QDate RESSOURCE_HUMAINE::getDATE_NAISSANCE(){return DATE_NAISSANCE;}
int RESSOURCE_HUMAINE::getTEL(){return TEL;}
float RESSOURCE_HUMAINE::getSALAIRE(){return SALAIRE;}
QString  RESSOURCE_HUMAINE::getVILLE(){return VILLE;}
int RESSOURCE_HUMAINE::getID_DIRIGEANT(){return ID_DIRIGEANT;}


void RESSOURCE_HUMAINE::setID_EMP(int ID_EMP){this->ID_EMP=ID_EMP;}
void RESSOURCE_HUMAINE::setNOM(QString NOM){this->NOM=NOM;}
void RESSOURCE_HUMAINE::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void RESSOURCE_HUMAINE::setMETIER(QString METIER){this->METIER=METIER;}
void RESSOURCE_HUMAINE::setDATE_NAISSANCE(QDate DATE_NAISSANCE){this->DATE_NAISSANCE=DATE_NAISSANCE;}
void RESSOURCE_HUMAINE::setTEL(int TEL){this->TEL=TEL;}
void RESSOURCE_HUMAINE::setSALAIRE(float SALAIRE){this->SALAIRE=SALAIRE;}
void RESSOURCE_HUMAINE::setVILLE(QString VILLE){this->VILLE=VILLE;}
void RESSOURCE_HUMAINE::setID_DIRIGEANT(int ID_DIRIGEANT){this->ID_DIRIGEANT=ID_DIRIGEANT;}




bool RESSOURCE_HUMAINE::ajouter()
{
    QSqlQuery query;
    QString ID_EMP_string=QString::number(ID_EMP);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);
    QString ID_DIRIGEANT_string=QString::number(ID_DIRIGEANT);


         query.prepare("INSERT INTO RESSOURCE_HUMAINE (ID_EMP, NOM, PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,VILLE,ID_DIRIGEANT) "
                       "VALUES (:ID_EMP,:NOM,:PRENOM,:METIER ,:DATE_NAISSANCE,:TEL,:SALAIRE,:VILLE,:ID_DIRIGEANT)");
         query.bindValue(":ID_EMP",ID_EMP_string);
         query.bindValue(":NOM",NOM);
         query.bindValue(":PRENOM",PRENOM);
         query.bindValue(":METIER",METIER);
         query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
         query.bindValue(":TEL",TEL_string);
         query.bindValue(":SALAIRE",SALAIRE_string);
         query.bindValue(":VILLE",VILLE);
         query.bindValue(":ID_DIRIGEANT",ID_DIRIGEANT_string);

         return query.exec();

}

QSqlQueryModel* RESSOURCE_HUMAINE::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM RESSOURCE_HUMAINE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_DIRIGEANT"));

    return model;

}



bool RESSOURCE_HUMAINE::supprimer(int ID_EMP){
      QSqlQuery query;
      QString res=QString::number(ID_EMP);
    query.prepare("Delete from RESSOURCE_HUMAINE where ID_EMP=:ID_EMP");
    query.bindValue(":ID_EMP", res);

    return  query.exec();



}
bool RESSOURCE_HUMAINE::modifier(int ID_EMP,QString NOM,QString PRENOM,QString METIER,QDate DATE_NAISSANCE,int TEL,float SALAIRE,QString VILLE,int ID_DIRIGEANT){
    QSqlQuery query;
    QString ID_EMP_string=QString::number(ID_EMP);
    QString TEL_string=QString::number(TEL);
    QString SALAIRE_string=QString::number(SALAIRE);
    QString ID_DIRIGEANT_string=QString::number(ID_DIRIGEANT);
       query.prepare(" UPDATE RESSOURCE_HUMAINE set ID_EMP=:ID_EMP ,NOM=:NOM,PRENOM=:PRENOM ,METIER=:METIER, DATE_NAISSANCE=:DATE_NAISSANCE, TEL=:TEL, SALAIRE=:SALAIRE,VILLE=:VILLE,ID_DIRIGEANT=:ID_DIRIGEANT where ID_EMP=:ID_EMP");
       query.bindValue(":ID_EMP",ID_EMP_string);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":METIER",METIER);
       query.bindValue(":DATE_NAISSANCE",DATE_NAISSANCE);
       query.bindValue(":TEL",TEL_string);
       query.bindValue(":SALAIRE",SALAIRE_string);
       query.bindValue(":VILLE",VILLE);
       query.bindValue(":ID_DIRIGEANT",ID_DIRIGEANT_string);
       return query.exec();
}


QSqlQueryModel * RESSOURCE_HUMAINE::triercin()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY ID_EMP");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_DIRIGEANT"));

    return model;
}
QSqlQueryModel * RESSOURCE_HUMAINE::trierdate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY DATE_NAISSANCE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_DIRIGEANT"));

    return model;
}

QSqlQueryModel * RESSOURCE_HUMAINE::triersalaire()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_HUMAINE ORDER BY SALAIRE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("METIER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID_DIRIGEANT"));

    return model;
}

void RESSOURCE_HUMAINE::recherche(QTableView * table ,int cin,QString nom, QString metier )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString cin_string=QString::number(cin);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from RESSOURCE_HUMAINE where ID_EMP like '%"+cin_string+"%' or NOM like '%"+nom+"%' or METIER like '%"+metier+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}

void  RESSOURCE_HUMAINE::telechargerPDF(){

                     QPdfWriter pdf("C:\\Users\\dalys\\OneDrive\\Bureau\\Atelier_Connexion\\import.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::blue);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"GESTION RH");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",11));
                         painter.drawText(300,3300,"CIN");
                         painter.drawText(1300,3300,"NOM");
                         painter.drawText(2200,3300,"PRENOM");
                         painter.drawText(3200,3300,"METIER");
                         painter.drawText(4300,3300,"DATE NAISSANCE");
                         painter.drawText(6300,3300,"TEL");
                         painter.drawText(7300,3300,"SALAIR");
                         painter.drawText(8300,3300,"CIN DIRIGEANT");


                         QSqlQuery query;
                        // query.prepare("select * from RESSOURCE_HUMAINE where ID_EMP='"+val+"'");
                         query.prepare("select * from RESSOURCE_HUMAINE");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2200,i,query.value(2).toString());
                             painter.drawText(3200,i,query.value(3).toString());
                             painter.drawText(4300,i,query.value(4).toString());
                             painter.drawText(6300,i,query.value(5).toString());
                             painter.drawText(7300,i,query.value(6).toString());
                             painter.drawText(8300,i,query.value(7).toString());



                            i = i + 500;
                         }}

bool RESSOURCE_HUMAINE::modifier_emploi(QString mtrcl, QDateTime dateS, QDateTime dateE)
{
    QSqlQuery query;
    QString date_stringS = dateS.toString("d MMM yyyy h:m");
    QString date_stringE = dateE.toString("d MMM yyyy h:m");
    QString date_string = "From "+date_stringS +" To "+ date_stringE;

    query.prepare("UPDATE RESSOURCE_HUMAINE set reservation=:reserv where ID_EMP=:mtrcl");
    query.bindValue(":mtrcl", mtrcl);
    query.bindValue(":reserv", date_string);

    return query.exec();
}


