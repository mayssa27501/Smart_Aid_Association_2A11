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
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z][-._+])[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)([0-9a-zA-Z][.])[a-zA-Z]{2,6}$");
    ui->le_id->setValidator(new QIntValidator(0,99999999,this));
    ui->le_cin->setValidator(new QIntValidator(10000000,99999999,this));
    ui->le_numd->setValidator(new QIntValidator(0,99999999,this));
    ui->tableView->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::controlSaisie(){
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
    if (
            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            ui->le_id->text().isEmpty() ||
            ui->le_id->text().toInt() == 0 ||
            ui->le_cin->text().isEmpty() ||
            ui->le_cin->text().toInt() == 0 ||
            ui->le_numd->text().isEmpty() ||
            ui->le_numd->text().toInt() == 0 ||
            !(mailREX.exactMatch(ui->le_email->text()))
            )
        return 0;
    else
        return 1;
}

void MainWindow::on_pb_ajouter_clicked()
{
    if (controlSaisie()){
    int id_contrat=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    QDate date_contrat=ui->date_lee->date();
    int cin_employe=ui->le_cin->text().toInt();
    int num_dossier=ui->le_numd->text().toInt();
Contrat C(id_contrat,nom,prenom,email,date_contrat,cin_employe,num_dossier);
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
    else {
        QMessageBox msgBox;
        msgBox.setText("echec veuillez remplir les champs correctement");
        msgBox.exec();
    }
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
    if (controlSaisie()){
    int id_contrat=ui->le_id->text().toInt();

     QString nom=ui->le_nom->text();

     QString prenom=ui->le_prenom->text();

     QString email=ui->le_email->text();

     QDate date_contrat=ui->date_lee->date();

     int cin_employe=ui->le_cin->text().toInt();

     int num_dossier=ui->le_numd->text().toInt();




     Contrat C(id_contrat,nom,prenom,email,date_contrat,cin_employe,num_dossier);



      bool test=C.modifier(id_contrat,nom,prenom,email,date_contrat,cin_employe,num_dossier);

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
    else {
        QMessageBox msgBox;
        msgBox.setText("echec veuillez remplir les champs correctement");
        msgBox.exec();
    }
}
