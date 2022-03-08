#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ressourcehumaine.h"
#include <QDate>
#include <QMessageBox>
#include <QMainWindow>
#include "QSqlQuery"
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTextStream>
#include <QIntValidator>
RESSOURCE_HUMAINE RH;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cin->setValidator(new QIntValidator(0,99999999,this));
    ui->numero->setValidator(new QIntValidator(0,99999999,this));
    ui->cin_Dirgeant->setValidator(new QIntValidator(0,99999999,this));
    ui->id_tresorie->setValidator(new QIntValidator(0,99999999,this));
    ui->id_stock->setValidator(new QIntValidator(0,99999999,this));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ajouter_clicked()
{if (controlSaisie()){

        int CIN=ui->cin->text().toInt();
        QString NOM=ui->nom->text();
        QString PRENOM=ui->prenom->text();
        QString METIER=ui->metier->text();
        QDate DATE_NAISSANCE=ui->dateli->date();
        int TEL=ui->numero->text().toInt();
        double SALAIRE=ui->salaire->text().toDouble();
        int ID_TRESORIE=ui->id_tresorie->text().toInt();
        int ID_STOCK=ui->id_stock->text().toUInt();
        int CIN_DIRIGEANT=ui->cin_Dirgeant->text().toUInt();



       RESSOURCE_HUMAINE RH(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,ID_TRESORIE,ID_STOCK,CIN_DIRIGEANT);
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

    } else {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),

                    QObject::tr("veuiller remplir tous les champs correctement.\n"

                                "Click cancel to exit."), QMessageBox::Cancel);

    }
}






void MainWindow::on_Supp_btn_clicked()
{
    int id =ui->cin_2->text().toInt();
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
{if (controlSaisie()){
        int CIN=ui->cin->text().toInt();
        QString NOM=ui->nom->text();
        QString PRENOM=ui->prenom->text();
        QString METIER=ui->metier->text();
        QDate DATE_NAISSANCE=ui->dateli->date();
        int TEL=ui->numero->text().toInt();
        double SALAIRE=ui->salaire->text().toDouble();
        int ID_TRESORIE=ui->id_tresorie->text().toInt();
        int ID_STOCK=ui->id_stock->text().toUInt();
        int CIN_DIRIGEANT=ui->cin_Dirgeant->text().toUInt();

        RESSOURCE_HUMAINE RH(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,ID_TRESORIE,ID_STOCK,CIN_DIRIGEANT);

         bool test=RH.modifier(CIN,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,ID_TRESORIE,ID_STOCK,CIN_DIRIGEANT);
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
    } else {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),

                    QObject::tr("veuiller remplir tous les champs correctement.\n"

                                "Click cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_tri_cin_clicked()
{
    ui->affiche_tab->setModel(RH.triercin());

}

void MainWindow::on_tri_date_clicked()
{
    ui->affiche_tab->setModel(RH.trierdate());

}

void MainWindow::on_tri_salaire_clicked()
{
    ui->affiche_tab->setModel(RH.triersalaire());

}


void MainWindow::on_Afficher_li_clicked()
{
    ui->affiche_tab->setModel(RH.afficher());

}

void MainWindow::on_cherche_li_textChanged(const QString &arg1)
{
    RESSOURCE_HUMAINE RH;

int cin= ui->cherche_li->text().toInt();
QString nom = ui->cherche_li->text();
QString metier = ui->cherche_li->text();
RH.recherche(ui->affiche_tab,cin,nom,metier);
if (ui->cherche_li->text().isEmpty())
{
    ui->affiche_tab->setModel(RH.afficher());
}
}



void MainWindow::on_connecter_clicked()
{
    QStackedWidget stackedWidget;
        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));
        QString username=ui->lineEdit_username->text();
                QString password = ui->lineEdit_password->text();
                if(username == "daly" && password == "daly")
                { QMessageBox::information(this, "Login", "Username and password is correct");
               //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));
                ui->stackedWidget->setCurrentIndex(1);
                }
                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                    else if(username == "anas" && password == "anas")
                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(2);
                }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "yosra" && password == "yosra")
                        { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(3);
                }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "arslen" && password == "arslen")
                            { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(4);
                }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "abrar" && password == "abrar")
                                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(5);
                }
                else if(username == "maysa" && password == "maysa")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                      ui->stackedWidget->setCurrentIndex(6);
                      }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                            else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

}
bool MainWindow::controlSaisie(){



    if (

            !(ui->nom->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )

            !(ui->prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            !(ui->metier->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->cin->text().isEmpty() ||

            ui->cin->text().toInt() == 0 ||

            ui->numero->text().isEmpty() ||

            ui->numero->text().toInt() == 0 ||

            ui->salaire->text().isEmpty() ||

            ui->salaire->text().toDouble() == 0)

        return 0;

    else

        return 1;

}
