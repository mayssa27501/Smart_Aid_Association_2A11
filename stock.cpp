#include "stock.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QDate>
#include<QVector>
Stock::Stock()
{
    ref=0;espece=0;race=" ";nom=" ";categorie=0;quantite=0;delai=QDate::currentDate();

}
Stock::Stock (int ref ,int espece ,QString race ,QString nom,int categorie,int quantite,QDate delai)
{this->ref=ref;this->espece=espece;this->race=race;this->nom=nom;this->categorie=categorie;this->quantite=quantite;this->delai=delai;}
int Stock::getref(){return ref;}
int Stock::getespece(){return espece;}
QString Stock::getrace(){return race ;}
QString Stock::getnom(){return nom ;}
int Stock::getcategorie(){return categorie ;}
int Stock::getquantite(){return quantite;}
QDate Stock::getdelai(){return delai;}
void Stock::setref(int ref){this->ref=ref;}
void Stock::setespece(int espece){this->espece=espece;}
void Stock::setrace(QString race){this->race=race;}
void Stock::setnom(QString nom){this->nom=nom;}
void Stock::setcategorie(int categorie){this->categorie=categorie;}
void Stock::setquantite(int quantite){this->quantite=quantite;}
void Stock::setdelai(QDate delai){this->delai=delai;}
bool Stock::ajouter()
{
    QSqlQuery query;
    QString ref_string=QString::number(ref);
         query.prepare("INSERT INTO STOCK (ref, espece, race,nom,categorie,quantite,delai) "
                       "VALUES (:ref, :espece, :race,:nom ,:categorie,:quantite,:delai)");
         query.bindValue(":ref", ref_string);
         QString esp;
         if(espece==0)
            { esp="chien";}
         else if(espece==1)
          { esp="chat";}

         query.bindValue(":espece", esp);
         query.bindValue(":race", race);
          query.bindValue(":nom",nom);
          QString cat;
          if(categorie==0)
             { cat="nourriture";}
          else if(categorie==1)
           { cat="medicament";}
          else
          { cat="equipement";}
           query.bindValue(":categorie", cat);
            query.bindValue(":quantite",quantite);
            query.bindValue(":delai",delai);
         return query.exec();

}
bool Stock::supprimer(int ref)
{
    QSqlQuery query;

         query.prepare("Delete from Stock where ref=:ref");
         query.bindValue(":ref", ref);

         return query.exec();
}
QSqlQueryModel* Stock::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

          model->setQuery("SELECT * FROM Stock");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("reference"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("espece"));
           model->setHeaderData(2, Qt::Horizontal,QObject::tr("race"));
            model->setHeaderData(3, Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("delai"));
            model->setHeaderData(6, Qt::Horizontal,QObject::tr("categorie"));
            model->setHeaderData(4, Qt::Horizontal,QObject::tr("quantite"));
    return model ;
}
bool Stock::modifierStock(int ref,int espece,QString race,QString nom,int categorie,int quantite,QDate delai)

{



    QSqlQuery query;

    query.prepare("update STOCK set ref=:ref,espece=:espece,race=:race,nom=:nom,categorie=:categorie ,quantite=:quantite,delai=:delai where ref=:ref");

    query.bindValue(":ref",ref);
    query.bindValue(":espece",espece);

    query.bindValue(":race",race);

    query.bindValue(":nom",nom);

    query.bindValue(":categorie",categorie);

     query.bindValue(":quantite",quantite);
     query.bindValue(":delai",delai);





    return query.exec();



}
QSqlQueryModel * Stock::triernom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from STOCK ORDER BY NOM");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("espece"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("race "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));


    return model;
}
QSqlQueryModel * Stock::triercategorie()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from STOCK ORDER BY CATEGORIE");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("espece"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("race "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));


    return model;
}
QSqlQueryModel * Stock::trierrace()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from STOCK ORDER BY RACE");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("espece"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("race "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));


    return model;
}
void Stock::recherche(QTableView * table ,int ref,int espece, QString nom )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString ref_string=QString::number(ref);
    QString espece_string=QString::number(espece);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from Stock where ref like '%"+ref_string+"%' or NOM like '%"+nom+"%' or espece like '%"+espece_string+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}