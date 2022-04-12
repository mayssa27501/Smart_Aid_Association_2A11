#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tresorie.h"
#include <QDate>
#include <QMessageBox>
#include <QMainWindow>
tresorie tr;
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

void MainWindow::on_ajouter_li_clicked()
{
    int num_op=ui->num_li->text().toInt();
          QString type=ui->type_li->text();
          QString descriptive=ui->descrip_li->text();
          double montant=ui->mon_li->text().toDouble();
          QDate date_ajout=ui->dateli->date();


         tresorie tr(num_op,type,descriptive,montant,date_ajout);
         bool test=tr.ajouter();
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

           ui->affiche_tab->setModel (tr.afficher());
}

void MainWindow::on_supp_btn_clicked()
{
    tresorie tr;

    int id =ui->num_li->text().toInt();
           bool test=tr.supprimer(id);

           if(test)
               QMessageBox::information(nullptr, QObject::tr("ok"),
                           QObject::tr("supression effectué .\n"
                                       "Click Ok to exit."), QMessageBox::Ok);
           else
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("échec suprresion.\n"
                                       "Click cancel to exit."), QMessageBox::Cancel);
           ui->affiche_tab->setModel(tr.afficher());
}

void MainWindow::on_modif_btn_clicked()
{
    int num_op=ui->num_li->text().toInt();
          QString type=ui->type_li->text();
          QString descriptive=ui->descrip_li->text();
          double montant=ui->mon_li->text().toDouble();
          QDate date_ajout=ui->dateli->date();



          tresorie tr(num_op,type,descriptive,montant,date_ajout);



             bool test=tr.modifier(num_op,type,descriptive,montant,date_ajout);

             if(test)

           {ui->affiche_tab->setModel(tr.afficher());

           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                             QObject::tr("invite modifiée.\n"

                                         "Click ok to exit."), QMessageBox::Ok);



           }

             else

                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                             QObject::tr("echec d'ajout !.\n"

                                         "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tri_type_clicked()
{
   tresorie tr;
   ui->affiche_tab->setModel(tr.triertype());
}

void MainWindow::on_tri_date_clicked()
{
    tresorie tr;
    ui->affiche_tab->setModel(tr.trierdate());

}

void MainWindow::on_tri_montant_clicked()
{
    tresorie tr;
    ui->affiche_tab->setModel(tr.triermontant());
}

void MainWindow::on_cherche_li_textChanged(const QString &arg1)
{
    tresorie tr;



    int num_op= ui->cherche_li->text().toInt();

    QString type = ui->cherche_li->text();

    QString descriptive = ui->cherche_li->text();

    tr.recherche(ui->affiche_tab,num_op,type,descriptive);

    if (ui->cherche_li->text().isEmpty())

    {

        ui->affiche_tab->setModel(tr.afficher());

    }
}
