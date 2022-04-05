#include "donneur.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include <QtWidgets/QRadioButton>
#include<QDate>
DONNEUR::DONNEUR()
{
     ID_DONNEUR=0;
    NOM="";
    PRENOM="" ;
    email="";
  TYPE="" ;

   NUM_OPERATION=0;



}
DONNEUR::DONNEUR(int ID_DONNEUR,QString NOM,QString PRENOM,QString email,QString TYPE, int NUM_OPERATION)
{this->ID_DONNEUR=ID_DONNEUR;this->NOM=NOM;this-> PRENOM= PRENOM;this->email=email;this-> TYPE= TYPE;this->NUM_OPERATION=NUM_OPERATION;}
int DONNEUR::getID_DONNEUR(){return ID_DONNEUR;}
QString DONNEUR:: getNOM(){return NOM;}
QString DONNEUR:: getPRENOM(){return PRENOM;}
QString DONNEUR::getemail(){return email;}
QString DONNEUR:: getTYPE(){return TYPE;}
int DONNEUR::getNUM_OPERATION(){return NUM_OPERATION;}

void DONNEUR::setID_DONNEUR(int ID_DONNEUR){this->ID_DONNEUR=ID_DONNEUR;}
void DONNEUR::setNOM(QString NOM){this->NOM=NOM;}
void DONNEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void DONNEUR::setemail(QString email){this->email=email;}
void DONNEUR::setTYPE(QString type){this->TYPE=type;}

void DONNEUR::setNUM_OPERATION(int NUM_OPERATION){this->NUM_OPERATION=NUM_OPERATION;}
bool DONNEUR::ajouter()//zedthaa
{


    QSqlQuery query;
    QString ID_DONNEUR_string= QString::number(ID_DONNEUR);
    QString NUM_OPERATION_string= QString::number(NUM_OPERATION);
    query.prepare("INSERT INTO DONNEUR (ID_DONNEUR,NOM,PRENOM,EMAIL,TYPE,NUM_OP) "
                  "VALUES (:ID_DONNEUR, :NOM, :PRENOM,:EMAIL, :TYPE,:NUM_OP)");
     //affecter le valeur dans bd
    query.bindValue(":ID_DONNEUR",ID_DONNEUR_string);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
     query.bindValue(":EMAIL", email);
    query.bindValue(":TYPE",TYPE);
     query.bindValue(":NUM_OP",NUM_OPERATION_string);

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

    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE "));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_OPERATION"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));



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
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("TYPE"));

        model->setHeaderData(5,Qt::Horizontal, QObject::tr("NUM_OPERATION"));



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
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("TYPE"));

   model->setHeaderData(5,Qt::Horizontal, QObject::tr("NUM_OPERATION"));


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
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
     model->setHeaderData(4,Qt::Horizontal, QObject::tr("TYPE"));

    model->setHeaderData(5,Qt::Horizontal, QObject::tr("NUM_OPERATION"));


     return model;
 }
bool DONNEUR::modifier(int ID_DONNEUR,QString NOM,QString PRENOM,QString EMAIL,QString TYPE,int NUM_OPERATION){
    QSqlQuery query;
    QString  ID_ADHERENT_string=QString::number( ID_DONNEUR);


       query.prepare(" UPDATE DONNEUR set ID_DONNEUR=:ID_DONNEUR ,NOM=:NOM,PRENOM=:PRENOM ,EMAIL=:EMAIL ,TYPE=:TYPE ,NUM_OP=:NUM_OP where ID_DONNEUR=:ID_DONNEUR");
       query.bindValue(":ID_DONNEUR",ID_ADHERENT_string);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":EMAIL",email);
       query.bindValue(":TYPE",TYPE);

        query.bindValue(":NUM_OP",NUM_OPERATION);
       return query.exec();
}
//recherche//
QSqlQueryModel * DONNEUR::recherche(QString CHERCH)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM DONNEUR WHERE ID_DONNEUR LIKE '%"+CHERCH+"%' OR NOM LIKE '%"+CHERCH+"%' OR PRENOM LIKE '%"+CHERCH+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DONNEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_OP"));

    return model;
}
//recherche par nom
/*QSqlQueryModel * DONNEUR::rechercheN(QString NOM)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM DONNEUR WHERE NOM LIKE '%"+NOM+"%'");
    model->query().bindValue(":idc",ID_DONNEUR);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DONNEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_OP"));

    return model;
}*/
//RECHERCHE PAR PRENOM
/*QSqlQueryModel * DONNEUR::rechercheP(QString PRENOM)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM DONNEUR WHERE PRENOM LIKE '%"+PRENOM+"%'");
    model->query().bindValue(":idc",ID_DONNEUR);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DONNEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_OP"));

    return model;
}*/
