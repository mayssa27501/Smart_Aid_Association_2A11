#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include <QMessageBox>
#include <QMainWindow>


Contrat C;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id_contrat=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    int date_contrat=ui->le_date->text().toInt();
    int num_dossier=ui->le_numd->text().toInt();
Contrat C(id_contrat,nom,prenom,email,date_contrat,num_dossier);
bool test=C.ajouter();
        QMessageBox msgBox;
           if(test)
           {
               msgBox.setText("ajout avec succes");
           msgBox.exec();
           }
           else
           {
               msgBox.setText("echec");
           msgBox.exec();
           }
    ui->tableView->setModel(C.afficher());
}


void MainWindow::on_pb_supp_clicked()
{
    int id =ui->le_id->text().toInt();
        bool test=C.supprimer(id);

        if(test)
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("échec suprresion.\n"
                                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(C.afficher());
}


void MainWindow::on_pb_modifier_clicked()
{
    int id_contrat=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    int date_contrat=ui->le_date->text().toInt();
    int num_dossier=ui->le_numd->text().toInt();

       Contrat C(id_contrat,nom,prenom,email,date_contrat,num_dossier);


     bool test=C.modifier(id_contrat,nom,prenom,email,date_contrat,num_dossier);
     if(test)
   {ui->tableView->setModel(C.afficher());
   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                     QObject::tr("invite modifiée.\n"
                                 "Click ok to exit."), QMessageBox::Ok);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                     QObject::tr("echec d'ajout !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
