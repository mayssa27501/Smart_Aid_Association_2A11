#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ressourcehumaine.h"
#include <QDate>
#include <QMessageBox>
#include <QMainWindow>
RESSOURCE_HUMAINE RH;
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

void MainWindow::on_Ajouter_clicked()
{
        int CIN=ui->cin->text().toInt();
        QString NOM=ui->nom->text();
        QString PRENOM=ui->prenom->text();
        QString METIER=ui->metier->text();
        QDate DATE_NAISSANCE=ui->dateli->date();
        int TEL=ui->numero->text().toInt();
        double SALAIRE=ui->salaire->text().toDouble();


       RESSOURCE_HUMAINE RH(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE);
       bool test=RH.ajouter();
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
                 ui->affiche_tab->setModel (RH.afficher());


}






void MainWindow::on_Supp_btn_clicked()
{
    int id =ui->cin->text().toInt();
        bool test=RH.supprimer(id);

        if(test)
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("échec suprresion.\n"
                                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->affiche_tab->setModel(RH.afficher());
}

void MainWindow::on_mod_btn_clicked()
{
        int CIN=ui->cin->text().toInt();
        QString NOM=ui->nom->text();
        QString PRENOM=ui->prenom->text();
        QString METIER=ui->metier->text();
        QDate DATE_NAISSANCE=ui->dateli->date();
        int TEL=ui->numero->text().toInt();
        double SALAIRE=ui->salaire->text().toDouble();

        RESSOURCE_HUMAINE RH(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE);

         bool test=RH.modifier(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE);
         if(test)
       {ui->affiche_tab->setModel(RH.afficher());
       QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                         QObject::tr("invite modifiée.\n"
                                     "Click ok to exit."), QMessageBox::Ok);

       }
         else
             QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                         QObject::tr("echec d'ajout !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}
