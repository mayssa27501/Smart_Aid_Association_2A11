#include "contrat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include<QPrintDialog>
#include<QPrinter>



Contrat::Contrat()
{
id_contrat=0; nom=""; prenom=""; email=""; date_contrat=QDate::currentDate();; cin_employe=0; num_dossier=0;
}

Contrat::Contrat(int id_contrat,QString nom,QString prenom,QString email,QDate date_contrat,int cin_employe,int num_dossier)
{this->id_contrat=id_contrat;this->nom=nom;this->prenom=prenom;this->email=email;this->date_contrat=date_contrat;this->cin_employe=cin_employe;this->num_dossier=num_dossier;}

int Contrat::getid_contrat(){return id_contrat;}
QString Contrat::getnom(){return nom;}
QString Contrat::getprenom(){return prenom;}
QString Contrat::getemail(){return email;}
QDate Contrat::getdate_contrat(){return date_contrat;}
int Contrat::getcin_employe(){return cin_employe;}
int Contrat::getnum_dossier(){return num_dossier;}

void Contrat::setid_contrat(int id_contrat){this->id_contrat=id_contrat;}
void Contrat::setnom(QString nom){this->nom=nom;}
void Contrat::setprenom(QString prenom){this->prenom=prenom;}
void Contrat::setemail(QString email){this->email=email;}
void Contrat::setdate_contrat(QDate date_contrat){this->date_contrat=date_contrat;}
void Contrat::setcin_employe(int cin_employe){this->cin_employe=cin_employe;}
void Contrat::setnum_dossier(int num_dossier){this->num_dossier=num_dossier;}

bool Contrat::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id_contrat);
    QString cin_employe_string=QString::number(cin_employe);
    QString num_dossier_string=QString::number(num_dossier);
          query.prepare("INSERT INTO CONTRAT (ID_CONTRAT,NOM,PRENOM,EMAIL,DATE_CONTRAT,CIN_EMPLOYE,NUM_DOSSIER) "
                        "VALUES (:ID_CONTRAT, :NOM, :PRENOM, :EMAIL, :DATE_CONTRAT, :CIN_EMPLOYE, :NUM_DOSSIER)");
          query.bindValue(":ID_CONTRAT",id_string);
          query.bindValue(":NOM", nom);
          query.bindValue(":PRENOM", prenom);
          query.bindValue(":EMAIL", email);
          query.bindValue(":DATE_CONTRAT", date_contrat);
          query.bindValue(":CIN_EMPLOYE", cin_employe_string);
          query.bindValue(":NUM_DOSSIER", num_dossier_string);


    return query.exec();
}

QSqlQueryModel * Contrat::afficher()
{ QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from CONTRAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CONTRAT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE_CONTRAT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("CIN_EMPLOYE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM_DOSSIER"));

    return  model;

}

bool Contrat::supprimer(int id_contrat){

      QSqlQuery query;

      QString res=QString::number(id_contrat);

    query.prepare("Delete from CONTRAT where ID_CONTRAT=:ID_CONTRAT");

    query.bindValue(":ID_CONTRAT", res);



    return  query.exec();
}

bool Contrat::modifier(int id_contrat,QString nom,QString prenom,QString email,QDate date_contrat,int cin_employe,int num_dossier){
    QSqlQuery query;
    QString id_contrat_string=QString::number(id_contrat);
    QString cin_employe_string=QString::number(cin_employe);
    QString num_dossier_string=QString::number(num_dossier);
       query.prepare(" UPDATE CONTRAT set ID_CONTRAT=:ID_CONTRAT ,NOM=:NOM,PRENOM=:PRENOM ,EMAIL=:EMAIL, DATE_CONTRAT=:DATE_CONTRAT,CIN_EMPLOYE=:CIN_EMPLOYE,NUM_DOSSIER=:NUM_DOSSIER where ID_CONTRAT=:ID_CONTRAT");
       query.bindValue(":ID_CONTRAT",id_contrat_string);
       query.bindValue(":NOM",nom);
       query.bindValue(":PRENOM",prenom);
       query.bindValue(":EMAIL",email);
       query.bindValue(":DATE_CONTRAT",date_contrat);
       query.bindValue(":CIN_EMPLOYE",cin_employe_string);
       query.bindValue(":NUM_DOSSIER",num_dossier_string);
       return query.exec();
}

QSqlQueryModel * Contrat::trierid()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT ORDER BY ID_CONTRAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CONTRAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_CONTRAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN_EMPLOYE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM_DOSSIER"));


    return model;
}

QSqlQueryModel * Contrat::triernom()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT ORDER BY NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CONTRAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_CONTRAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN_EMPLOYE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM_DOSSIER"));


    return model;
}

QSqlQueryModel * Contrat::trierdate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRAT ORDER BY DATE_CONTRAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CONTRAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_CONTRAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN_EMPLOYE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM_DOSSIER"));


    return model;
}

void Contrat::recherche(QTableView * table ,int id_contrat,QString nom, QString prenom )
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString id_contrat_string=QString::number(id_contrat);


    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from CONTRAT where ID_CONTRAT like '%"+id_contrat_string+"%' or NOM like '%"+nom+"%' or PRENOM like '%"+prenom+"%' ;");


    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

}

void  Contrat::telechargerPDF()
{


                     QPdfWriter pdf("C:/Atelier_Connexion/export_pdf.pdf");

                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::red);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"CONTRAT");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",14));
                         painter.drawRect(100,100,7300,2600);
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial",11));
                         painter.drawText(200,3300,"id_contrat");
                         painter.drawText(1300,3300,"nom");
                         painter.drawText(2200,3300,"prenom");
                         painter.drawText(3200,3300,"email");
                         painter.drawText(5300,3300,"date_contrat");
                         painter.drawText(7000,3300,"cin_employe");
                         painter.drawText(8100,3300,"num_dossier");

                         QSqlQuery query;
                         query.prepare("select * from CONTRAT");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2200,i,query.value(2).toString());
                             painter.drawText(3200,i,query.value(3).toString());
                             painter.drawText(5300,i,query.value(4).toString());
                             painter.drawText(7700,i,query.value(5).toString());
                             painter.drawText(8700,i,query.value(6).toString());

                            i = i + 500;
                         }

}