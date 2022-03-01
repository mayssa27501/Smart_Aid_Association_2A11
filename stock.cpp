#include "stock.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
Stock::Stock()
{
    ref=0;espece=" ";race=" ";nom=" ";categorie=" ";

}
Stock::Stock (int ref ,QString espece ,QString race ,QString nom,QString categorie )
{this->ref=ref;this->espece=espece;this->race=race;this->nom=nom;this->categorie=categorie;}
int Stock::getref(){return ref;}
QString Stock::getespece(){return espece;}
QString Stock::getrace(){return race ;}
QString Stock::getnom(){return nom ;}
QString Stock::getcategorie(){return categorie ;}
void Stock::setref(int ref){this->ref=ref;}
void Stock::setespece(QString espece){this->espece=espece;}
void Stock::setrace(QString race){this->race=race;}
void Stock::setnom(QString nom){this->nom=nom;}
void Stock::setcategorie(QString categorie){this->categorie=categorie;}
bool Stock::ajouter()
{
    QSqlQuery query;
    QString ref_string=QString::number(ref);
         query.prepare("INSERT INTO STOCK (ref, espece, race,nom,categorie) "
                       "VALUES (:ref, :espece, :nom ,:race ,:categorie)");
         query.bindValue(":ref", ref_string);
         query.bindValue(":espece", espece);
         query.bindValue(":race", race);
          query.bindValue(":nom",nom);
           query.bindValue(":categorie", categorie);
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
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("Reference"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("Espece"));
           model->setHeaderData(1, Qt::Horizontal,QObject::tr("Race"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal,QObject::tr("Categorie"));
    return model ;
}
bool Stock::modifierStock(int ref,QString espece,QString race,QString nom,QString categorie)

{



    QSqlQuery query;

    query.prepare("update STOCK set ref=:ref,espece=:espece,race=:race,nom=:nom,categorie=:categorie where ref=:ref");

    query.bindValue(":ref",ref);
    query.bindValue(":espece",espece);

    query.bindValue(":race",race);

    query.bindValue(":nom",nom);

    query.bindValue(":categorie",categorie);





    return query.exec();



}
