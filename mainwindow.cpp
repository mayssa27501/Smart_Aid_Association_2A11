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
bool MainWindow::controlsaisie(){

    if ( ui->le_num->text().isEmpty() ||
         ui->le_num->text().toInt() == 0 )
    { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                 QObject::tr("numero invalide.\n"
                                                                             "Click cancel to exit."), QMessageBox::Cancel);
        return 0;}
    if (
            !(ui->le_espece->text().contains(QRegExp("^[A-Z a-z]+$"))) ) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                         QObject::tr("espece invalide.\n"
                                                                                     "Click cancel to exit."), QMessageBox::Cancel);
                return 0;
    }
         if(   !(ui->le_diag->text().contains(QRegExp("^[A-Za-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("diagnostic invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
           if ( !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))))
           {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("nom invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
           if ( !(ui->le_race->text().contains(QRegExp("^[A-Za-z]+$"))))
           {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("race invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
           if ( !(ui->le_sexe->text().contains(QRegExp("^[A-Za-z]+$")))) {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("sexe invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }

         if (!(ui->le_setri->text().contains(QRegExp("^[A-Za-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("sterilisation invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
         if (!(ui->le_vaccn->text().contains(QRegExp("^[A-Za-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("vaccin invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
         if (!(ui->le_trait->text().contains(QRegExp("^[A-Za-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("traitement invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }

         if (ui->le_poids->text().isEmpty() ||
         ui->le_poids->text().toDouble() == 0 ){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("poid invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }

         if (ui->le_temp->text().isEmpty() ||
         ui->le_temp->text().toDouble() == 0 ){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("temperature invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }

           if ( ui->cin_emp->text().isEmpty() ||
            ui->cin_emp->text().toInt() == 0 ) {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("employee invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
        return 1;
}

void MainWindow::on_pb_ajouter_clicked()
{
    if (controlsaisie()){
    int num_doss=ui->le_num->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag->text();
    QString nom_animal=ui->le_nom->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poid=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe->text();
    double temperature=ui->le_temp->text().toDouble();
    QString sterilisation=ui->le_setri->text();

    QString etat_vaccin=ui->le_vaccn->text();
    QString traitement=ui->le_trait->text();

    int id_employe=ui->cin_emp->text().toInt();

    Dossier_medical DM(num_doss,espece,maladie,nom_animal,race,date_naiss,poid,sexe, temperature,sterilisation,etat_vaccin,traitement,id_employe);

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
    else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("veuiller remplir tous les champs correctement.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
}
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

    if (controlsaisie()){
    int num_doss=ui->le_num->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag->text();
    QString nom_animal=ui->le_nom->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poid=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe->text();
    double temperature=ui->le_temp->text().toDouble();
    QString sterilisation=ui->le_setri->text();
    QString etat_vaccin=ui->le_vaccn->text();
    QString traitement=ui->le_trait->text();
    int id_employe=ui->cin_emp->text().toInt();

   Dossier_medical DM(num_doss,espece,maladie,nom_animal,race,date_naiss,poid,sexe, temperature,sterilisation,etat_vaccin,traitement,id_employe);


         bool test=DM.modifier(num_doss,espece,maladie,nom_animal,race,date_naiss,poid,sexe, temperature,sterilisation,etat_vaccin,traitement,id_employe);
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
         } else {

             QMessageBox::critical(nullptr, QObject::tr("not ok"),

                         QObject::tr("veuiller remplir tous les champs correctement.\n"

                                     "Click cancel to exit."), QMessageBox::Cancel);

         }
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

void MainWindow::on_cherche_li_textChanged(const QString &arg1)
{
    Dossier_medical DM;



   int num_doss= ui->cherche_li->text().toInt();

   QString nom = ui->cherche_li->text();

   QString maladie = ui->cherche_li->text();

   DM.recherche(ui->tabafficher,num_doss,nom,maladie);

   if (ui->cherche_li->text().isEmpty())

   {

       ui->tabafficher->setModel(DM.afficher());

   }
}

void MainWindow::on_tabafficher_clicked(const QModelIndex &index)
{
    ui->le_num->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),0)).toString());
    ui->le_nom->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),1)).toString());

    QString date_string_on_db = ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),2)).toString();
    QDate Date = QDate::fromString(date_string_on_db,"yyyy-MM-ddT00:00:00");
    qDebug(date_string_on_db.toLatin1());
    ui->de_date->setDate(Date);
    //....
 ui->le_espece->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),3)).toString());
 ui->le_race->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),4)).toString());
 ui->le_sexe->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),5)).toString());
 ui->le_poids->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),6)).toString());

  ui->le_diag->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),7)).toString());
    ui->le_temp->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),8)).toString());
    ui->le_setri->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),9)).toString());
     ui->le_vaccn->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),10)).toString());
     ui->le_trait->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),11)).toString());
      ui->cin_emp->setText(ui->tabafficher->model()->data(ui->tabafficher->model()->index(index.row(),12)).toString());

    // a coninuer


}
