#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include <QMessageBox>
#include <QMainWindow>
#include "donneur.h"


ADHERENT A;
DONNEUR D;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_adherent->setModel(A.afficher());
     ui->tab_donneur->setModel(D.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{

        int ID_ADHERENT=ui->le_id->text().toInt();
          QString NOM_ADHERENT=ui->le_nom->text();
          QString PRENOM_ADHERENT=ui->le_prenom->text();
          QString METIER_ADHERENT=ui->le_metier->text();
           QString SEXE=ui->le_sexe->text();
           double COTISATION=ui->le_cotisation->text().toDouble();



          ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,METIER_ADHERENT,SEXE ,COTISATION);


          bool test=A.ajouter();
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
                     ui->tab_adherent->setModel(A.afficher());
}

void MainWindow::on_pb_supprimer_clicked()
{
    {
        int ID_ADHERENT =ui->le_id->text().toInt();
            bool test=A.supprimer(ID_ADHERENT);

            if(test)
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("supression effectué .\n"
                                        "Click Ok to exit."), QMessageBox::Ok);
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("échec suprresion.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
            ui->tab_adherent->setModel(A.afficher());
    }

}



void MainWindow::on_le_afficher_clicked()
{
    int ID_ADHERENT=ui->le_id->text().toInt();
      QString NOM_ADHERENT=ui->le_nom->text();
      QString PRENOM_ADHERENT=ui->le_prenom->text();
      QString METIER_ADHERENT=ui->le_metier->text();
       QString SEXE=ui->le_sexe->text();
       double COTISATION=ui->le_cotisation->text().toDouble();



      ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,METIER_ADHERENT,SEXE ,COTISATION);



                 ui->tab_adherent->setModel(A.afficher());
}

void MainWindow::on_le_modif_clicked()
{
    int ID_ADHERENT=ui->le_id->text().toInt();
            QString NOM_ADHERENT=ui->le_nom->text();
            QString PRENOM_ADHERENT=ui->le_prenom->text();
            QString METIER_ADHERENT=ui->le_metier->text();
             QString SEXE=ui->le_sexe->text();

            float COTISATION=ui->le_cotisation->text().toFloat();

               ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT, METIER_ADHERENT, SEXE, COTISATION);


             bool test=A.modifier(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT, METIER_ADHERENT, SEXE, COTISATION);
             if(test)
           {ui->tab_adherent->setModel(A.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);

           }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}
/*donneuuuuuuuuuuuuuur*/
/*ajouter*/

void MainWindow::on_pushButton_6_clicked() /*ajouter*/
{
    int ID_DONNEUR=ui->le_id_d->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
      QString METIER=ui->le_metier_d->text();
       QString SEXE=ui->le_sexe_d->text();




      DONNEUR D(ID_DONNEUR,NOM,PRENOM,METIER,SEXE );


      bool test=D.Ajouter();
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
 ui->tab_donneur->setModel(D.afficher());
}

/*affich*/

void MainWindow::on_pushButton_clicked()
{
    int ID_DONNEUR=ui->le_id->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
      QString METIER=ui->le_metier_d->text();
       QString SEXE=ui->le_sexe_d->text();




      DONNEUR A(ID_DONNEUR,NOM,PRENOM,METIER,SEXE );



                 ui->tab_donneur->setModel(D.afficher());
}
