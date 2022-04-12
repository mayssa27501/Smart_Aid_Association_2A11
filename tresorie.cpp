#include "tresorie.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>

tresorie::tresorie()
{
    num_op=0;
    type="";
    descriptive="";
    montant=0;
    date_ajout=QDate::currentDate();


}
tresorie::tresorie(int num_op,QString type,QString descriptive,float montant,QDate date_ajout)
{this->num_op=num_op;this->type=type;this->descriptive=descriptive;this->montant=montant;this->date_ajout=date_ajout;}
int tresorie::getnum_op(){return num_op;}
QString tresorie::gettype(){return type;}
QString tresorie::getdescriptive(){return descriptive;}
float  tresorie::getmontant(){return montant;}
QDate tresorie::getdate_ajout(){return date_ajout;}

void tresorie::setnum_op(int num_op){this->num_op=num_op;}
void tresorie::settype(QString type){this->type=type;}
void tresorie::setdescriptive(QString descriptive){this->descriptive=descriptive;}
void tresorie::setmontant(float montant){this->montant=montant;}
void tresorie::setdate_ajout(QDate date_ajout){this->date_ajout=date_ajout;}

bool tresorie::ajouter()
{
    QSqlQuery query;
    QString num_op_string=QString::number(num_op);
    QString montant_string=QString::number(montant);


         query.prepare("INSERT INTO TRESORIE (NUM_OP, TYPE, DESCRIPTIVE,MONTANT,DATE_AJOUT) "
                       "VALUES (:NUM_OP,:TYPE,:DESCRIPTIVE,:MONTANT ,:DATE_AJOUT)");
         query.bindValue(":NUM_OP",num_op_string);
         query.bindValue(":TYPE",type);
         query.bindValue(":DESCRIPTIVE",descriptive);
         query.bindValue(":MONTANT",montant_string);
         query.bindValue(":DATE_AJOUT",date_ajout);
         return query.exec();

}


QSqlQueryModel* tresorie::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM TRESORIE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_OP"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTIVE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_AJOUT"));


    return model;

}


bool tresorie::supprimer(int num_op){

      QSqlQuery query;

      QString res=QString::number(num_op);

    query.prepare("Delete from TRESORIE where NUM_OP=:NUM_OP");

    query.bindValue(":NUM_OP", res);



    return  query.exec();
}


bool tresorie::modifier(int num_op,QString type,QString descriptive,float montant,QDate date_ajout){
    QSqlQuery query;
    QString num_op_string=QString::number(num_op);
    QString montant_string=QString::number(montant);
       query.prepare(" UPDATE TRESORIE set NUM_OP=:NUM_OP ,TYPE=:TYPE,DESCRIPTIVE=:DESCRIPTIVE ,MONTANT=:MONTANT, DATE_AJOUT=:DATE_AJOUT where NUM_OP=:NUM_OP");
       query.bindValue(":NUM_OP",num_op_string);
       query.bindValue(":TYPE",type);
       query.bindValue(":DESCRIPTIVE",descriptive);
       query.bindValue(":MONTANT",montant_string);
       query.bindValue(":DATE_AJOUT",date_ajout);
       return query.exec();
}

QSqlQueryModel * tresorie::trierdate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRESORIE ORDER BY DATE_AJOUT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_OP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTIVE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_AJOUT"));

    return model;
}

QSqlQueryModel * tresorie::triertype()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRESORIE ORDER BY TYPE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_OP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTIVE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_AJOUT"));

    return model;
}

QSqlQueryModel * tresorie::triermontant()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRESORIE ORDER BY MONTANT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_OP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTIVE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_AJOUT"));

    return model;
}

void tresorie::recherche(QTableView * table ,int num_op,QString type, QString descriptive )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString num_op_string=QString::number(num_op);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from TRESORIE where NUM_OP like '%"+num_op_string+"%' or TYPE like '%"+type+"%' or DESCRIPTIVE like '%"+descriptive+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}



