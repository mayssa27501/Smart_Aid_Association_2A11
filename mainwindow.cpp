#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stock.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QIntValidator>

Stock S;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_reference->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_stock->setModel(S.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int ref=ui->le_reference->text().toInt();
    QString espece=ui->le_espece->text();
    QString race=ui->le_race->text();
    QString nom=ui->le_nom->text();
    QString categorie=ui->le_categorie->text();

    Stock S(ref ,espece ,race,nom,categorie);
    bool test=S.ajouter();
            QMessageBox msgBox;
               if(test)
               {
                   msgBox.setText("ajout avec succes");
                    ui->tab_stock->setModel(S.afficher());
               msgBox.exec();
               }
               else
               {
                   msgBox.setText("echec");
               msgBox.exec();
               }

}

void MainWindow::on_pb_supprimer_clicked()
{
    Stock S1; S1.setref(ui->le_supprimer->text().toInt());
    bool test=S1.supprimer(S1.getref());
    QMessageBox msgBox;
       if(test)
       {
           msgBox.setText("Suppression avec succes");
           ui->tab_stock->setModel(S.afficher());
       msgBox.exec();
       }
       else
       {
           msgBox.setText("echec de suppression");
       msgBox.exec();
       }

}

void MainWindow::on_pb_modifier_clicked()
{
    int ref=ui->le_reference->text().toInt();
    QString espece=ui->le_espece->text();
            QString race=ui->le_race->text();
            QString nom=ui->le_nom->text();
            QString categorie=ui->le_categorie->text();




         ui->le_espece->setMaxLength(20);
         ui->le_race->setMaxLength(20);
            ui->le_nom->setMaxLength(5); // max longueur
             ui->le_categorie->setMaxLength(20);
                    ui->le_reference->setMaxLength(7);


            Stock S2(ref,espece,race,nom,categorie);

            bool test=S2.modifierStock(S2.getref(),S2.getespece(),S2.getrace(),S2.getnom(),S2.getcategorie());

            QMessageBox msgBox;
            if(test)
            {
                msgBox.setText("Modification avec succes");
                ui->tab_stock->setModel(S.afficher());
            msgBox.exec();
            }
            else
            {
                msgBox.setText("echec de modification");
            msgBox.exec();
            }
}
