#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include <QMessageBox>
#include <QMainWindow>
#include "donneur.h"
#include <QtWidgets/QRadioButton>
#include <QtSql/QSqlQueryModel>


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

bool MainWindow::controlSaisie(){

    if (
            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_metier->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            ui->id_tresorie_adherent->text().isEmpty() ||
            ui->id_tresorie_adherent->text().toInt() == 0 ||
            ui->le_id->text().isEmpty() ||
            ui->le_id->text().toInt() == 0 ||
            !(ui->le_sexe->text().contains(QRegExp("^[A-Za-z]+$"))) )
        return 0;
    else
        return 1;
}
bool MainWindow::controlSaisie2(){

    if (
            !(ui->le_nom_d->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom_d->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_metier_d->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            ui->id_tresorie_donneur->text().isEmpty() ||
            ui->id_tresorie_donneur->text().toInt() == 0 ||
            ui->le_id_d->text().isEmpty() ||// si vide
            ui->le_id_d->text().toInt() == 0 || //si contient 7arff (7arfa kif yosraa  sahbtyyy )
            !(ui->le_sexe_d->text().contains(QRegExp("^[A-Za-z]+$"))) )
        return 0;
    else
        return 1;
}

void MainWindow::on_pb_ajouter_clicked()
{
if (controlSaisie()){
        int ID_ADHERENT=ui->le_id->text().toInt();
          QString NOM_ADHERENT=ui->le_nom->text();
          QString PRENOM_ADHERENT=ui->le_prenom->text();
          QString METIER_ADHERENT=ui->le_metier->text();
           QString SEXE=ui->le_sexe->text();
           double COTISATION=ui->le_cotisation->text().toDouble();
           int ID_TRESORIE = ui->id_tresorie_adherent->text().toInt();



          ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,METIER_ADHERENT,SEXE ,COTISATION,ID_TRESORIE);


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
                      } else {
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("veuiller remplir tous les champs correctement.\n"
                            "Click cancel to exit."), QMessageBox::Cancel);
}
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
  int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();


      ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,METIER_ADHERENT,SEXE ,COTISATION ,ID_TRESORIE);



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
int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();
               ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT, METIER_ADHERENT, SEXE, COTISATION ,ID_TRESORIE);


             bool test=A.modifier(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT, METIER_ADHERENT, SEXE, COTISATION ,ID_TRESORIE);
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


void MainWindow::on_pb_ajouter_d_clicked()
{
    if(controlSaisie2()){
    int ID_DONNEUR=ui->le_id_d->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
      QString METIER=ui->le_metier_d->text();
       QString SEXE=ui->le_sexe_d->text();
    int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();



      DONNEUR D(ID_DONNEUR,NOM,PRENOM,METIER,SEXE, ID_TRESORIE );


      bool test=D.ajouter();
              QMessageBox msgBox;
                 if(test)
                 {
                     msgBox.setText("ajout avec succes");

                 msgBox.exec();
                 clear();
                 }
                 else
                 {
                     msgBox.setText("echec");
                 msgBox.exec();
                 }
 ui->tab_donneur->setModel(D.afficher());}
 // mtaaa cntrl de saisiirrr
    else {
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                 QObject::tr("veuiller remplir tous les champs correctement.\n"
                             "Click cancel to exit."), QMessageBox::Cancel);
 }
}
// pour clear

void MainWindow::clear(){
    ui->le_id_d->clear();
     ui->le_nom_d->clear();
    ui->le_prenom_d->clear();
    ui->le_metier_d->clear();
    ui->le_sexe_d->clear();
    ui->id_tresorie_donneur->clear();
}





//affich donneur

void MainWindow::on_pushButton_clicked()
{
    int ID_DONNEUR=ui->le_id->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
      QString METIER=ui->le_metier_d->text();
       QString SEXE=ui->le_sexe_d->text();
int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();



      DONNEUR A(ID_DONNEUR,NOM,PRENOM,METIER,SEXE,ID_TRESORIE );



                 ui->tab_donneur->setModel(D.afficher());
}
//trieprenom



void MainWindow::on_t_nom_clicked()
{
    ui->tab_donneur->setModel(D.trierprenom());
}
//triepreid

void MainWindow::on_t_id_clicked()
{
   ui->tab_donneur->setModel(D.trierid());
}
void MainWindow::on_t_prenom_clicked()
{
     ui->tab_donneur->setModel(D.trierprenom());
}
//SUPP donneur
void MainWindow::on_pb_suppr_d_clicked()

    {
    //yjiblna donneur ily aandu id ily tnfskhooh
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from DONNEUR WHERE ID_DONNEUR="+ui->le_id_d->text());
//si id vide oou bien 0 ou bien
    if(ui->le_id_d->text().isEmpty() || model->rowCount() == 0)
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("donner un id valide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    else

        {
            int ID_DONNEUR =ui->le_id_d->text().toInt();
                bool test=D.supprimer(ID_DONNEUR);

                if(test)
                    QMessageBox::information(nullptr, QObject::tr("ok"),
                                QObject::tr("supression effectué .\n"
                                            "Click Ok to exit."), QMessageBox::Ok);

                else
                    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                QObject::tr("échec suprresion.\n"
                                            "Click cancel to exit."), QMessageBox::Cancel);
                ui->tab_donneur->setModel(D.afficher());
                clear();
        }


    }

void MainWindow::on_le_mod_d_clicked()
{
    if (controlSaisie2()){
    int ID_DONNEUR=ui->le_id_d->text().toInt();
            QString NOM=ui->le_nom_d->text();
            QString PRENOM=ui->le_prenom_d->text();
            QString METIER=ui->le_metier_d->text();
             QString SEXE=ui->le_sexe_d->text();
 int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();


               DONNEUR D(ID_DONNEUR,NOM,PRENOM, METIER, SEXE,ID_TRESORIE );


             bool test=D.modifier(ID_DONNEUR,NOM,PRENOM, METIER, SEXE,ID_TRESORIE);
             if(test)
           {
                 ui->tab_donneur->setModel(D.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);
           clear();

           }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}
    else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("veuiller remplir tous les champs correctement.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_le_afficher_d_clicked()
{
    int ID_DONNEUR=ui->le_id_d->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
      QString METIER=ui->le_metier_d->text();
       QString SEXE=ui->le_sexe_d->text();
  int ID_TRESORIE=ui->id_tresorie_donneur->text().toInt();



      DONNEUR D(ID_DONNEUR,NOM,PRENOM,METIER,SEXE,ID_TRESORIE );



                 ui->tab_donneur->setModel(D.afficher());
}




