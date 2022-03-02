#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dossier_medical.h"
#include "mainwindow.h"
#include <qradiobutton.h>
#include <QMainWindow>
#include <QtQml/qqml.h>
#include <QMessageBox>

Dossier_medical DM;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int num_doss=ui->le_num->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag->text();
    QString nom_animal=ui->le_nom->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poids=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe->text();
    double temperature=ui->le_temp->text().toDouble();
    QString sterilisation=ui->le_setri->text();

    QString etat_vaccin=ui->le_vaccn->text();
    QString traitement=ui->le_trait->text();


    Dossier_medical DM(num_doss,espece,maladie,nom_animal,race,date_naiss,poids,sexe, temperature,sterilisation,etat_vaccin,traitement);

    bool test=DM.ajouter();
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
    ui->tabafficher->setModel (DM.afficher());
}


void MainWindow::on_pb_supp_clicked()
{
    int num_doss=ui->le_supp->text().toInt();
            bool test=DM.supprimer(num_doss);

            if(test)
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("supression effectué .\n"
                                        "Click Ok to exit."), QMessageBox::Ok);
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("échec suprresion.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
            ui->tabafficher->setModel(DM.afficher());}

void MainWindow::on_pb_afficher_clicked()
{
    ui->tabafficher->setModel (DM.afficher());

}

void MainWindow::on_pb_modif_clicked()
{
    int num_doss=ui->le_num->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag->text();
    QString nom_animal=ui->le_nom->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poids=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe->text();
    double temperature=ui->le_temp->text().toDouble();
    QString sterilisation=ui->le_setri->text();

    QString etat_vaccin=ui->le_vaccn->text();
    QString traitement=ui->le_trait->text();

   Dossier_medical DM(num_doss,espece,maladie,nom_animal,race,date_naiss,poids,sexe, temperature,sterilisation,etat_vaccin,traitement);


         bool test=DM.modifier(num_doss,espece,maladie,nom_animal,race,date_naiss,poids,sexe, temperature,sterilisation,etat_vaccin,traitement);
         if(test)
       {ui->tabafficher->setModel(DM.afficher());
       QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                         QObject::tr("invite modifiée.\n"
                                     "Click ok to exit."), QMessageBox::Ok);

       }
         else
             QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                         QObject::tr("echec d'ajout !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_trinum_clicked()
{
    ui->tabafficher->setModel(DM.triernum());
}

void MainWindow::on_tridate_clicked()
{
    ui->tabafficher->setModel(DM.trierdate());
}

void MainWindow::on_tabnom_clicked()
{
    ui->tabafficher->setModel(DM.triernom());
}
