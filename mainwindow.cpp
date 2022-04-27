#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ressourcehumaine.h"
#include <QDate>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQueryModel>
#include "QSqlQuery"
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTextStream>
#include <QIntValidator>
#include <QDesktopServices>
#include "QStringListModel"
#include <QFile>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QDateTime>
#include<QPrintDialog>
#include<QPrinter>
#include<QPrintDialog>
#include <QPdfWriter>
#include<QFileDialog>
#include "qrcodegen.hpp"
#include "chat.h"
#include <QTextStream>
#include <QSqlRecord>
#include <QDesktopServices>
#include <QtWidgets/QRadioButton>
#include <QtSql/QSqlQueryModel>
#include"QUrl"
#include "stmp.h"

RESSOURCE_HUMAINE RH;
ADHERENT AD;
DONNEUR D;
Contrat C;
Stock S;
tresorie tr,trr;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cin->setValidator(new QIntValidator(0,99999999,this));
    ui->numero->setValidator(new QIntValidator(0,99999999,this));
    ui->cin_Dirgeant->setValidator(new QIntValidator(0,99999999,this));

    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z][-._+])[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)([0-9a-zA-Z][.])[a-zA-Z]{2,6}$");
    ui->le_id->setValidator(new QIntValidator(0,99999999,this));
    ui->le_cin->setValidator(new QIntValidator(10000000,99999999,this));
    ui->le_numd->setValidator(new QIntValidator(0,99999999,this));
    ui->tableView->setModel(C.afficher());

    ui->affiche_tab->setModel(RH.afficher());
    ui->change->setModel(RH.afficher());
    ui->comboBox_2->setModel(RH.afficher());
    ui->comboBox->setModel(RH.afficher());
    ui->comboBox_5->setModel(DM.afficher());
    ui->combo_sup->setModel(C.afficher());
    ui->combo_modif->setModel(C.afficher());


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

        ui->dateEdit_emploi->setDisplayFormat("d MMM yyyy");
        ui->dateTimeEdit_emploiS->setDisplayFormat("d MMM yyyy h:m");
        ui->dateTimeEdit_emploiE->setDisplayFormat("d MMM yyyy h:m");
        ui->dateEdit_emploi->setDate(QDate::currentDate());
        ui->dateTimeEdit_emploiS->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_emploiE->setDateTime(QDateTime::currentDateTime().addDays(1));
        ui->calendarWidget->setDateRange(QDate::currentDate(), QDate::currentDate().addDays(14));
        ui->affiche_tab_2->setModel(trr.afficher());
        //ui->affiche_tab_2->setModel(tr)
        showtime();
        QTimer *timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
        timer->start();


        ui->le_reference->setValidator(new QIntValidator(0, 9999999, this));
         ui->le_quantite->setValidator(new QIntValidator(0, 999999, this));
       ui->tab_stock->setModel(S.afficher());

       ui->tab_adherent->setModel(AD.afficher());
        ui->tab_donneur->setModel(D.afficher());
        ui->tableView_alerte->setModel(D.getAlertes());
        QValidator *validator = new QIntValidator(1, 99999999, this); // pour les int
       QValidator *validatorDouble = new QDoubleValidator(0.0, 999,2, this);
        ui->le_id_d->setValidator(validator);
        ui->num_op_d->setValidator(validator);
        ui->le_id_a->setValidator(validator);
        ui->id_tresorie_a->setValidator(validator);
        ui->le_cotisation_a->setValidator(validatorDouble);
}

void MainWindow::showtime()
{
    QTime time=QTime::currentTime();

    QString time_next=time.toString("hh : mm : ss");
    ui->Digital_clock->setText(time_next);
    ui->Digital_clock_3->setText(time_next);
    ui->digital_clock->setText(time_next);
    ui->Digital_clock_2->setText(time_next);
    ui->Digital_clock_4->setText(time_next);
    ui->Digital_clock_5->setText(time_next);
    ui->Digital_clock_6->setText(time_next);
    ui->Digital_clock_7->setText(time_next);
    ui->Digital_clock_8->setText(time_next);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ajouter_clicked()
{if (controlSaisie()){

        int ID_EMP=ui->cin->text().toInt();
        QString NOM=ui->nom->text();
        QString PRENOM=ui->prenom->text();
        QString METIER=ui->metier->text();
        QDate DATE_NAISSANCE=ui->dateli->date();
        int TEL=ui->numero->text().toInt();
        double SALAIRE=ui->salaire->text().toDouble();
        QString VILLE=ui->comboBox_4->currentText();
        int ID_DIRIGEANT=ui->cin_Dirgeant->text().toUInt();




       RESSOURCE_HUMAINE RH(ID_EMP,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,VILLE,ID_DIRIGEANT);
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
                 ui->affiche_tab->setModel(RH.afficher());
                 ui->change->setModel(RH.afficher());
                 ui->comboBox_2->setModel(RH.afficher());
                 ui->comboBox->setModel(RH.afficher());


    } else {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),

                    QObject::tr("veuiller remplir tous les champs correctement.\n"

                                "Click cancel to exit."), QMessageBox::Cancel);

    }
}






void MainWindow::on_Supp_btn_clicked()
{
    int id =ui->comboBox_2->currentText().toInt();
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
        ui->change->setModel(RH.afficher());
        ui->comboBox_2->setModel(RH.afficher());
        ui->comboBox->setModel(RH.afficher());



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
    ui->change->setModel(RH.afficher());
    ui->comboBox_2->setModel(RH.afficher());
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
                    else if(username == "arslen" && password == "arslen")
                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(2);
                }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "mayssa" && password == "mayssa")
                        { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(3);
                }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "yosra" && password == "yosra")
                            { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(4);
                }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "anas" && password == "anas")
                                { QMessageBox::information(this, "Login", "Username and password is correct");
                   ui->stackedWidget->setCurrentIndex(5);
                }
                else if(username == "abrar" && password == "abrar")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                      ui->stackedWidget->setCurrentIndex(6);
                      }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                            else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    ui->dateTimeEdit_emploiS->setCalendarPopup(true);
        ui->dateTimeEdit_emploiE->setCalendarPopup(true);

        if( dateTimeEditS_hadfocus )
            ui->dateTimeEdit_emploiE->setDate(date);
        else if( dateTimeEditE_hadfocus )
            ui->dateTimeEdit_emploiS->setDate(date);

        QDateTime date_min = QDateTime::currentDateTime();
        QDateTime date_max = date_min.addDays(14);
        ui->dateTimeEdit_emploiS->setDateTimeRange(date_min, date_max);
        ui->dateTimeEdit_emploiE->setDateTimeRange(date_min, date_max);
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









void MainWindow::on_change_activated(const QString &arg1)
{
    int ID_EMP = ui->change->currentText().toInt();
     QString id_string= QString::number(ID_EMP);
            QSqlQuery query;
            query.prepare("select * from RESSOURCE_HUMAINE where ID_EMP='"+id_string+"'");

            if(query.exec()){

                while(query.next())
                {
               ui->cin->setText(query.value(0).toString());
               ui->nom->setText(query.value(1).toString());
                ui->prenom->setText(query.value(2).toString());
                ui->metier->setText(query.value(3).toString());
                ui->dateli->setDate(query.value(4).toDate());
                 ui->numero->setText(query.value(5).toString());
                 ui->salaire->setText(query.value(6).toString());
                 ui->comboBox_4->setCurrentText(query.value(7).toString());
                 ui->cin_Dirgeant->setText(query.value(8).toString());

}}
            else
                QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

}





void MainWindow::on_modifer_btn_clicked()
{
    int ID_EMP=ui->cin->text().toInt();
    QString NOM=ui->nom->text();
    QString PRENOM=ui->prenom->text();
    QString METIER=ui->metier->text();
    QDate DATE_NAISSANCE=ui->dateli->date();
    int TEL=ui->numero->text().toInt();
    double SALAIRE=ui->salaire->text().toDouble();
    QString VILLE=ui->comboBox_4->currentText();
    int ID_DIRIGEANT=ui->cin_Dirgeant->text().toUInt();


    RESSOURCE_HUMAINE RH(ID_EMP,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,VILLE,ID_DIRIGEANT);


         bool test=RH.modifier(ID_EMP,NOM,PRENOM,METIER,DATE_NAISSANCE,TEL,SALAIRE,VILLE,ID_DIRIGEANT);
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

void MainWindow::on_Afficher_li_clicked()
{
    ui->affiche_tab->setModel(RH.afficher());
    ui->change->setModel(RH.afficher());
    ui->comboBox_2->setModel(RH.afficher());
    ui->comboBox->setModel(RH.afficher());
    ui->comboBox_3->setModel(RH.afficher());
    ui->comboBox_5->setModel(DM.afficher());

}

void MainWindow::on_telechargerPDF_clicked()
{
    RH.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}


void MainWindow::on_tableView_emploi_clicked(const QModelIndex &index)
{
    QString mtrcl_emp = ui->affiche_tab->model()->index(index.row(), 0).data().toString();
    int ID_EMP = ui->comboBox_3->currentText().toInt();

             QString id_string= QString::number(ID_EMP);
                    QSqlQuery query;
                    query.prepare("select * from RESSOURCE_HUMAINE where ID_EMP='"+id_string+"'");

}



void MainWindow::on_pushButton_emploi_goto_clicked()
{
    QDate date = ui->dateEdit_emploi->date();
       ui->calendarWidget->setSelectedDate(date);
}

void MainWindow::on_dateTimeEdit_emploiS_dateTimeChanged(const QDateTime &dateTime)
{
    dateTimeEditS_hadfocus  = true;
    dateTimeEditE_hadfocus  = false;
}

void MainWindow::on_dateTimeEdit_emploiE_dateTimeChanged(const QDateTime &dateTime)
{
    dateTimeEditS_hadfocus  = false;
       dateTimeEditE_hadfocus  = true;
}

void MainWindow::on_pushButton_mdf_emploi_clicked()
{
    int mtrcl1 = ui->comboBox_3->currentText().toInt();
    QString mtrcl=QString::number(mtrcl1);
     QDateTime dateS = ui->dateTimeEdit_emploiS->dateTime();
     QDateTime dateE = ui->dateTimeEdit_emploiE->dateTime();
     qDebug() << RH.modifier_emploi(mtrcl, dateS, dateE);
     ui->affiche_tab->setModel(RH.afficher());

}



void MainWindow::on_comboBox_activated(const QString &arg1)
{
    int ID_EMP = ui->comboBox->currentText().toInt();

             QString id_string= QString::number(ID_EMP);
                    QSqlQuery query;
                    query.prepare("select * from RESSOURCE_HUMAINE where ID_EMP='"+id_string+"'");

                    if(query.exec()){

                        while(query.next())
                        { ui->textEdit->setText(query.value(7).toString());


                            if  (ui->textEdit->toPlainText()== "Tunis")
                                        {ui->label_pic->clear();

                                  QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Tunis.jpg");
                                 int w = ui->label_pic->width();
                                 int h = ui->label_pic->height();
                                  ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                              }
                           else if  (ui->textEdit->toPlainText()== "Mahdia")
                                        {ui->label_pic->clear();

                                  QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Mahdia.jpg");
                                 int w = ui->label_pic->width();
                                 int h = ui->label_pic->height();
                                  ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                              }
                            else if  (ui->textEdit->toPlainText()== "Bizerte")
                                         {ui->label_pic->clear();

                                   QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Bizerte.jpg");
                                  int w = ui->label_pic->width();
                                  int h = ui->label_pic->height();
                                   ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                               }
                            else if  (ui->textEdit->toPlainText()== "Ariana")
                                         {ui->label_pic->clear();

                                   QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Ariana.jpg");
                                  int w = ui->label_pic->width();
                                  int h = ui->label_pic->height();
                                   ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                               }
                            else if  (ui->textEdit->toPlainText()== "Beja")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Beja.png");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Gabes")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Gabes.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Gafsa")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Gafsa.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Jendouba")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Jendouba.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Kairouan")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Kairouan.png");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Kasserine")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Kasserine.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Kebili")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Kebili.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Kef")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Kef.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Manouba")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Manouba.png");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Medenine")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Medenine.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Monastir")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Monastir.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Nabeul")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Nabeul.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Sfax")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Sfax.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "SidiBouzid")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Sidibouzid.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Siliana")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Siliana.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Sousse")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Soussa.png");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Tataouine")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Tataouine.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Tozeur")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Tozeur.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                            else if  (ui->textEdit->toPlainText()== "Zaghouan")
                            {ui->label_pic->clear();

                      QPixmap pix("C:/Users/dalys/OneDrive/Bureau/Integration/Maps/Zaghouan.jpg");
                     int w = ui->label_pic->width();
                     int h = ui->label_pic->height();
                      ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                  }
                      else
                                 {
                                     QMessageBox msgBox;

                                            msgBox.setText("region introuvable ");
                                        msgBox.exec();}








                        }} else
                        QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                                    QObject::tr("Erreur !.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString link="https://web.skype.com/";
    QDesktopServices::openUrl(QUrl(link));
}







// ////////////////////////////////////////////////////////////////////// //////////////////////////////////


bool MainWindow::controlSaisie1(){
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);

            if(
                !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) )
            { QMessageBox::critical(nullptr, QObject::tr("not ok"),
              QObject::tr("nom invalide.\n"
              "Click cancel to exit."), QMessageBox::Cancel);
                return 0;}



              if(
                  !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) )
                { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                  QObject::tr("prenom invalide.\n"
                 "Click cancel to exit."), QMessageBox::Cancel);
             return 0;}
            if(ui->le_id->text().isEmpty() ||
               ui->le_id->text().toInt() == 0)
    { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                 QObject::tr("id invalide.\n"
                 "Click cancel to exit."), QMessageBox::Cancel);
           return 0;}


            if(ui->le_cin->text().isEmpty() ||
            ui->le_cin->text().toInt() == 0 )
            { QMessageBox::critical(nullptr, QObject::tr("not ok"),
               QObject::tr("cin invalide.\n"
               "Click cancel to exit."), QMessageBox::Cancel);
                   return 0;}

            if(ui->le_numd->text().isEmpty() ||
            ui->le_numd->text().toInt() == 0)
            { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("numd invalide.\n"
                "Click cancel to exit."), QMessageBox::Cancel);
                   return 0;}

            if(
                !(mailREX.exactMatch(ui->le_email->text()))) { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                   QObject::tr("email invalide.\n"
                   "Click cancel to exit."), QMessageBox::Cancel);
                   return 0;}

        return 1;
}

void MainWindow::on_pb_ajouter_clicked()
{
    if (controlSaisie1()){
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
               QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
                   if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
                   {
                   QMessageBox::warning(this,"title","file not open");
                   }
                   QTextStream outt(&f);
                   QString text = "  ajouter \r\n";
                   QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
                   outt << sDate;
                   outt << text ;
                   f.flush();
                   f.close();
                   QString strStream;
                   QTextStream out(&strStream);           msgBox.exec();
           }
           else
           {
               msgBox.setText("echec");
           msgBox.exec();
           }
    ui->tableView->setModel(C.afficher());
    ui->combo_sup->setModel(C.afficher());
    ui->combo_modif->setModel(C.afficher());
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("echec veuillez remplir les champs correctement");
        msgBox.exec();
    }

}

void MainWindow::on_pb_supp_clicked()
{
    int id =ui->combo_sup->currentText().toInt();
        bool test=C.supprimer(id);

        if(test){
            QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
                if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
                {
                QMessageBox::warning(this,"title","file not open");
                }
                QTextStream outt(&f);
                QString text = "  supprimer \r\n";
                QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
                outt << sDate;
                outt << text ;
                f.flush();
                f.close();
                QString strStream;
                QTextStream out(&strStream);
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);}
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("échec suprresion.\n"
                                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(C.afficher());
        ui->combo_sup->setModel(C.afficher());
        ui->combo_modif->setModel(C.afficher());
}





void MainWindow::on_pb_modifier_clicked()
{
    if (controlSaisie1()){
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
          QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
              if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
              {
              QMessageBox::warning(this,"title","file not open");
              }
              QTextStream outt(&f);
              QString text = "  modifier \r\n";
              QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
              outt << sDate;
              outt << text ;
              f.flush();
              f.close();
              QString strStream;
              QTextStream out(&strStream);    QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

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
    ui->tableView->setModel(C.afficher());
    ui->combo_sup->setModel(C.afficher());
    ui->combo_modif->setModel(C.afficher());
}


void MainWindow::on_tr1_clicked()
{
ui->tableView->setModel(C.trierid());
QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
    if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
    {
    QMessageBox::warning(this,"title","file not open");
    }
    QTextStream outt(&f);
    QString text = "  tri par id \r\n";
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
    outt << sDate;
    outt << text ;
    f.flush();
    f.close();
    QString strStream;
    QTextStream out(&strStream);
}

void MainWindow::on_tr2_clicked()
{
ui->tableView->setModel(C.triernom());
QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
    if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
    {
    QMessageBox::warning(this,"title","file not open");
    }
    QTextStream outt(&f);
    QString text = "  tri par nom \r\n";
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
    outt << sDate;
    outt << text ;
    f.flush();
    f.close();
    QString strStream;
    QTextStream out(&strStream);
}

void MainWindow::on_tr3_clicked()
{
ui->tableView->setModel(C.trierdate());
QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
    if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
    {
    QMessageBox::warning(this,"title","file not open");
    }
    QTextStream outt(&f);
    QString text = "  tri par date \r\n";
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
    outt << sDate;
    outt << text ;
    f.flush();
    f.close();
    QString strStream;
    QTextStream out(&strStream);}


void MainWindow::on_cherche_li_2_textChanged(const QString &arg1)
{
    Contrat C;

    QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  recherche \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        QString strStream;
        QTextStream out(&strStream);

    int id_contrat= ui->cherche_li_2->text().toInt();

    QString nom = ui->cherche_li_2->text();

    QString prenom = ui->cherche_li_2->text();

    C.recherche(ui->tableView,id_contrat,nom,prenom);

    if (ui->cherche_li_2->text().isEmpty())

    {

        ui->tableView->setModel(C.afficher());
}
}




void MainWindow::on_trang_clicked()
{
    QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  traduction anglais \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        QString strStream;
        QTextStream out(&strStream);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
        lng="ANG";
                           // page biblo

                           ui->nom_2->setText("Name");
                           ui->prenom_2->setText("First name");
                           ui->id->setText("Contract id");
                           ui->email->setText("Email");
                           ui->datee->setText("Contract date");
                           ui->cin_2->setText("NIC");
                           ui->num->setText("File number");
                           ui->pb_ajouter->setText("Add");
                           ui->pb_modifier->setText("Modify");
                           ui->pb_supp->setText("Delete");
                           ui->tr1->setText("Sort by name");
                           ui->tr2->setText("Sort by id");
                           ui->tr3->setText("Sort by date");
                           ui->cherche_li->setText("Search");
                           ui->imprimer->setText("Print");
                           ui->trfr->setText("Frensh");
                           ui->trang->setText("English");
}

void MainWindow::on_trfr_clicked()
{
    QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  traduction français \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        QString strStream;
        QTextStream out(&strStream);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("Traduction francais ","Traduction francais",QSystemTrayIcon::Information,15000);
        lng="fr";
                           // page biblo

                           ui->nom_2->setText("Nom");
                           ui->prenom_2->setText("Prenom");
                           ui->id->setText("Id contrat");
                           ui->email->setText("Email");
                           ui->datee->setText("Date Contrat");
                           ui->cin_2->setText("CIN");
                           ui->num->setText("Num dossier");
                           ui->pb_ajouter->setText("Ajouter");
                           ui->pb_modifier->setText("Modifier");
                           ui->pb_supp->setText("Supprimer");
                           ui->tr1->setText("Trie par nom");
                           ui->tr2->setText("Trie par id");
                           ui->tr3->setText("Trie par date");
                           ui->cherche_li->setText("Recherche");
                           ui->imprimer->setText("Imprimer");
                           ui->trfr->setText("Français");
                           ui->trang->setText("Anglais");
}

void MainWindow::on_imprimer_clicked()
{

    QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  imprimer \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        QString strStream;
        QTextStream out(&strStream);

                             const int rowCount = ui->tableView->model()->rowCount();
                             const int columnCount = ui->tableView->model()->columnCount();
                             QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                             out <<"<html>\n"
                                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 << "<title>ERP - CONTRAT<title>\n "
                                 << "</head>\n"
                                 "<body bgcolor=#4c4c4c link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> ******LISTE DES CONTRATS ******"+TT+" </strong></h1>"
                                 "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                   "</br> </br>";
                             // headers
                             out << "<thead><tr bgcolor=#d6e5ff>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tableView->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tableView->isColumnHidden(column)) {
                                         QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table>\n"
                                 "</body>\n"
                                 "</html>\n";

                             QTextDocument *document = new QTextDocument();
                             document->setHtml(strStream);

                             QPrinter printer;

                             QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                             if (dialog->exec() == QDialog::Accepted) {
                                 document->print(&printer);
                             }

                             delete document;

}




void MainWindow::on_his_clicked()
{
    QFile f("C:/Users/dalys/OneDrive/Bureau/Integration/historique.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  historique \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        if(!f.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"title","file not open");
                }
                QTextStream in(&f);
                QString textt = in.readAll();
                ui->plainTextEdit->setPlainText(textt);
                f.close();
}

void MainWindow::on_pdf_clicked()
{

    C.telechargerPDF();

     QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);


}



void MainWindow::on_imprimer2_clicked()
{
    H.saveimp();
    QTextEdit parent;
       parent.setText("We are the world!");
       parent.show();

       QString filename = QFileDialog::getOpenFileName(&parent,"Open File",QString(),"Pdf File(*.pdf)");
       qDebug()<<"Print file name is "<<filename;
       if(!filename.isEmpty()) {
           if(QFileInfo(filename).suffix().isEmpty()) {
               filename.append(".pdf");
           }

           QPrinter printer(QPrinter::HighResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName(filename);
           QPrintDialog*dlg = new QPrintDialog(&printer,&parent);
           dlg->setWindowTitle(QObject::tr("Print Document"));

           if(dlg->exec() == QDialog::Accepted) {
               parent.print(&printer);
           }
           delete dlg;
}
}

// ///////////////////////////////////////////////////////////////////////////////::

bool MainWindow::controlsaisie3(){

    if ( ui->le_num_2->text().isEmpty() ||
         ui->le_num_2->text().toInt() == 0 )
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
         if(   !(ui->le_diag_2->text().contains(QRegExp("^[A-Z a-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("diagnostic invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
           if ( !(ui->le_nom_2->text().contains(QRegExp("^[A-Z a-z]+$"))))
           {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("nom invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
           if ( !(ui->le_race->text().contains(QRegExp("^[A-Z a-z]+$"))))
           {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("race invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
           if ( !(ui->le_sexe_2->text().contains(QRegExp("^[A-Z a-z]+$")))) {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("sexe invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }

         if (!(ui->le_setri_2->text().contains(QRegExp("^[A-Z a-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("sterilisation invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
         if (!(ui->le_vaccn_2->text().contains(QRegExp("^[A-Z a-z]+$")))){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("vaccin invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }
         if (!(ui->le_trait_2->text().contains(QRegExp("^[A-Z a-z]+$")))){
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

         if (ui->le_temp_2->text().isEmpty() ||
         ui->le_temp_2->text().toDouble() == 0 ){
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                              QObject::tr("temperature invalide.\n"
                                                                                          "Click cancel to exit."), QMessageBox::Cancel);
                     return 0;
         }

           if ( ui->cin_emp_2->text().isEmpty() ||
            ui->cin_emp_2->text().toInt() == 0 ) {
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                                                QObject::tr("employee invalide.\n"
                                                                                            "Click cancel to exit."), QMessageBox::Cancel);
                       return 0;
           }
        return 1;
}

void MainWindow::on_pb_ajouter_3_clicked()
{
    if (controlsaisie3()){
    int num_doss=ui->le_num_2->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag_2->text();
    QString nom_animal=ui->le_nom_2->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poid=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe_2->text();
    double temperature=ui->le_temp_2->text().toDouble();
    QString sterilisation=ui->le_setri_2->text();

    QString etat_vaccin=ui->le_vaccn_2->text();
    QString traitement=ui->le_trait_2->text();

    int id_employe=ui->cin_emp_2->text().toInt();

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
    ui->tabafficher_2->setModel (DM.afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("veuiller remplir tous les champs correctement.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
}
}


void MainWindow::on_pb_supp_3_clicked()
{

    int num_doss=ui->le_supp_2->text().toInt();
    if(DM.dossierExist(num_doss)==0)
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("dossier nexiste.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    } else {
            bool test=DM.supprimer(num_doss);

            if(test)
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("supression effectué .\n"
                                        "Click Ok to exit."), QMessageBox::Ok);
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("échec suprresion.\n"
                                        "Click cancel to exit."), QMessageBox::Cancel);
            ui->tabafficher_2->setModel(DM.afficher());
    }
}
void MainWindow::on_pb_afficher_2_clicked()
{
    ui->tabafficher_2->setModel (DM.afficher());

}

void MainWindow::on_pb_modif_2_clicked()
{

    if (controlsaisie3()){
    int num_doss=ui->le_num_2->text().toInt();
    QString espece=ui->le_espece->text();
    QString maladie=ui->le_diag_2->text();
    QString nom_animal=ui->le_nom_2->text();
    QString race=ui->le_race->text();
    QDate date_naiss=ui->de_date->date();
    double poid=ui->le_poids->text().toDouble();
    QString sexe=ui->le_sexe_2->text();
    double temperature=ui->le_temp_2->text().toDouble();
    QString sterilisation=ui->le_setri_2->text();
    QString etat_vaccin=ui->le_vaccn_2->text();
    QString traitement=ui->le_trait_2->text();
    int id_employe=ui->cin_emp_2->text().toInt();

   Dossier_medical DM(num_doss,espece,maladie,nom_animal,race,date_naiss,poid,sexe, temperature,sterilisation,etat_vaccin,traitement,id_employe);
   if(DM.dossierExist(num_doss)==0)
   {
       QMessageBox::critical(nullptr, QObject::tr("not ok"),
                   QObject::tr("dossier nexiste.\n"
                               "Click cancel to exit."), QMessageBox::Cancel);
   } else {

         bool test=DM.modifier(num_doss,espece,maladie,nom_animal,race,date_naiss,poid,sexe, temperature,sterilisation,etat_vaccin,traitement,id_employe);
         if(test)
       {ui->tabafficher_2->setModel(DM.afficher());
       QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                         QObject::tr("invite modifiée.\n"
                                     "Click ok to exit."), QMessageBox::Ok);

         }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                              QObject::tr("echec d'ajout !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
   }} else {

             QMessageBox::critical(nullptr, QObject::tr("not ok"),

                         QObject::tr("veuiller remplir tous les champs correctement.\n"

                                     "Click cancel to exit."), QMessageBox::Cancel);


    }
     }

void MainWindow::on_trinum_2_clicked()
{
    ui->tabafficher_2->setModel(DM.triernum());
}

void MainWindow::on_tridate_2_clicked()
{
    ui->tabafficher_2->setModel(DM.trierdate());
}

void MainWindow::on_tabnom_2_clicked()
{
    ui->tabafficher_2->setModel(DM.triernom());
}

void MainWindow::on_cherche_li_4_textChanged(const QString &arg1)
{
    Dossier_medical DM;



   int num_doss= ui->cherche_li_4->text().toInt();

   QString nom = ui->cherche_li_4->text();

   QString maladie = ui->cherche_li_4->text();

   DM.recherche(ui->tabafficher_2,num_doss,nom,maladie);

   if (ui->cherche_li_4->text().isEmpty())

   {

       ui->tabafficher_2->setModel(DM.afficher());

   }
}

void MainWindow::on_tabafficher_2_clicked(const QModelIndex &index)
{
    ui->le_num_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),0)).toString());
    ui->le_nom_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),1)).toString());

    QString date_string_on_db = ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),2)).toString();
    QDate Date = QDate::fromString(date_string_on_db,"yyyy-MM-ddT00:00:00");
    qDebug(date_string_on_db.toLatin1());
    ui->de_date->setDate(Date);
    //....
 ui->le_espece->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),3)).toString());
 ui->le_race->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),4)).toString());
 ui->le_sexe_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),5)).toString());
 ui->le_poids->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),6)).toString());

  ui->le_diag_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),7)).toString());
    ui->le_temp_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),8)).toString());
    ui->le_setri_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),9)).toString());
     ui->le_vaccn_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),10)).toString());
     ui->le_trait_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),11)).toString());
      ui->cin_emp_2->setText(ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(index.row(),12)).toString());

    // a coninuer

      QString text ="dossier medicale details :"+ ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),1)).toString()
              +" "+ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),2)).toString()
              +" "+ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),3)).toString()
              +" "+ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),4)).toString()
              +" "+ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),5)).toString()
              +" "+ui->tabafficher_2->model()->data(ui->tabafficher_2->model()->index(ui->tabafficher_2->currentIndex().row(),6)).toString();
      //text="user data";
      using namespace qrcodegen;
        // Create the QR Code object
        QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
        qint32 sz = qr.getSize();
        QImage im(sz,sz, QImage::Format_RGB32);
          QRgb black = qRgb(  0,  0,  0);
          QRgb white = qRgb(255,255,255);
        for (int y = 0; y < sz; y++)
          for (int x = 0; x < sz; x++)
            im.setPixel(x,y,qr.getModule(x, y) ? black : white );
        ui->qrcode_2->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}








void MainWindow::on_pushButton_3_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino
    ui->comboBox_5->setModel(DM.afficher());

}

void MainWindow::on_pushButton_4_clicked()
{
    int toard = ui->label_8->text().toInt();
if(toard==0)
{
 A.write_to_arduino("0"); //envoyer 0 à arduino
}
else if(toard==1)
{
 A.write_to_arduino("2"); //envoyer 0 à arduino

}
}

void MainWindow::update_label()
{

    data=A.read_from_arduino();

    QSqlQuery query;

      if(data=="1")
      {
          ui->labell->setText("Porte ouvert ");

          int mtrcl1 = ui->comboBox_5->currentText().toInt();
          QString mtrcl=QString::number(mtrcl1);
          int data1 = 1;
          QString data_ar=QString::number(data1);
           qDebug() << DM.modifier_ardui(mtrcl, data_ar);
}
    else if (data=="0")
      {
        ui->labell->setText("Porte fermé ");

      int mtrcl2 = ui->comboBox_5->currentText().toInt();
      QString mtrcl3=QString::number(mtrcl2);
      int data2 = 0;
      QString data_ar2=QString::number(data2);
       qDebug() << DM.modifier_ardui(mtrcl3, data_ar2);
      }

}





void MainWindow::on_comboBox_5_activated(const QString &arg1)
{
    int ID = ui->comboBox_5->currentText().toInt();

             QString id_string= QString::number(ID);
                    QSqlQuery query;
                    query.prepare("select * from DOSSIER_MEDICAL where NUM_DOSS='"+id_string+"'");


                            if(query.exec()){

                                while(query.next())
                                {
                               ui->label_8->setText(query.value(13).toString());
                                }}



}

void MainWindow::on_ajouter_li_clicked()
{
    int num_op=ui->num_li->text().toInt();
          QString type=ui->type_li->text();
          QString descriptive=ui->descrip_li->text();
          double montant=ui->mon_li->text().toDouble();
          QDate date_ajout=ui->dateli_2->date();


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

           ui->affiche_tab_2->setModel (tr.afficher());
}

void MainWindow::on_modif_btn_clicked()
{
    int num_op=ui->num_li->text().toInt();
          QString type=ui->type_li->text();
          QString descriptive=ui->descrip_li->text();
          double montant=ui->mon_li->text().toDouble();
          QDate date_ajout=ui->dateli_2->date();



          tresorie tr(num_op,type,descriptive,montant,date_ajout);



             bool test=tr.modifier(num_op,type,descriptive,montant,date_ajout);

             if(test)

           {ui->affiche_tab_2->setModel(tr.afficher());

           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                             QObject::tr("invite modifiée.\n"

                                         "Click ok to exit."), QMessageBox::Ok);



           }

             else

                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                             QObject::tr("echec d'ajout !.\n"

                                         "Click Cancel to exit."), QMessageBox::Cancel);

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
           ui->affiche_tab_2->setModel(tr.afficher());
}

void MainWindow::on_tri_type_clicked()
{
    tresorie tr;
    ui->affiche_tab_2->setModel(tr.triertype());
}

void MainWindow::on_tri_date_2_clicked()
{
    tresorie tr;
    ui->affiche_tab_2->setModel(tr.trierdate());
}

void MainWindow::on_tri_montant_clicked()
{
    tresorie tr;
    ui->affiche_tab_2->setModel(tr.triermontant());
}

void MainWindow::on_cherche_li_3_textChanged(const QString &arg1)
{
    tresorie tr;



    int num_op= arg1.toInt();

    QString type = ui->cherche_li_3->text();

    QString descriptive = ui->cherche_li_3->text();

    tr.recherche(ui->affiche_tab_2,num_op,type,descriptive);

    if (ui->cherche_li_3->text().isEmpty())

    {

        ui->affiche_tab_2->setModel(tr.afficher());

    }
}

void MainWindow::on_imprimer_2_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->affiche_tab_2->model()->rowCount();
                                 const int columnCount = ui->affiche_tab_2->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#4c4c4c link=#5000A0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******Liste des opérations financiers ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->affiche_tab_2->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->affiche_tab_2->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->affiche_tab_2->isColumnHidden(column)) {
                                             QString data =ui->affiche_tab_2->model()->data(ui->affiche_tab_2->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;
}

void MainWindow::on_stat_clicked()
{
    tresorie tr;
    QChart* chart_bar = tr.chart_pie();
        QChartView* chart_view_bar = new QChartView(chart_bar, ui->label_stat);
        chart_view_bar->setRenderHint(QPainter::Antialiasing);
        chart_view_bar->setMinimumSize(575,300);
        chart_view_bar->show();

}

void MainWindow::on_pushButton_6_clicked()
{
    A.write_to_arduino("3"); //envoyer 1 à arduino
}

void MainWindow::on_pushButton_7_clicked()
{
    A.write_to_arduino("4"); //envoyer 0 à arduino
}

void MainWindow::on_pushButton_8_clicked()
{
    w = new Chat(this);
      w->show();
}

void MainWindow::Alert(){
    QSqlQueryModel* model =new QSqlQueryModel();
    QString S=QString::number(Seuil);
    model->setQuery("SELECT * FROM Stock WHERE quantite < "+S);
    if (model->rowCount() == 1){
        QString produitNom =model->data(ui->tab_stock->model()->index(0,3)).toString();

        notifyIcon->show();
        notifyIcon->showMessage("alerte produits ","le produit "+produitNom+" presque epuisé ",QSystemTrayIcon::Information,15000);

    } else if (model->rowCount() > 1) {
        notifyIcon->show();
        notifyIcon->showMessage("alerte produits ","vous avez beaucoup de produits presque epuisés ",QSystemTrayIcon::Information,15000);
    }
}
void MainWindow::on_pb_modifier_2_clicked()
{
    if (controlSaisie_stock()){
    int ref=ui->le_reference->text().toInt();
    int espece=ui->le_espece_2->currentIndex();
            QString race=ui->le_race_2->text();
            QString nom=ui->le_nom_3->text();
            int categorie=ui->le_categorie->currentIndex();
    int quantite=ui->le_quantite->text().toInt();
    QDate delai=ui->le_delai->date();



         ui->le_race_2->setMaxLength(20);
            ui->le_nom_3->setMaxLength(5); // max longueur

                    ui->le_reference->setMaxLength(7);

                    ui->le_quantite->setMaxLength(7);


            Stock S2(ref,espece,race,nom,categorie,quantite,delai);

            bool test=S2.modifierStock(S2.getref(),S2.getespece(),S2.getrace(),S2.getnom(),S2.getcategorie(),S2.getquantite(),S2.getdelai());

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
            }}
    else {
                  QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("veuiller remplir tous les champs correctement.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    if(!(ui->le_race_2->text().contains(QRegExp("^[A-Za-z]+$")))){

        QMessageBox::critical(nullptr, QObject::tr("not ok"),

                    QObject::tr("nom invalide doit saisir seulment des chaine de caractere .\n"

                                "Click cancel to exit."), QMessageBox::Cancel);}

    else if(!(ui->le_nom_3->text().contains(QRegExp("^[A-Za-z]+$")))) {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),

                    QObject::tr("prenom invalide.\n"

                                "Click cancel to exit."), QMessageBox::Cancel);
    }

    else {

        int ref=ui->le_reference->text().toInt();
        int espece=ui->le_espece_2->currentIndex();
        QString race=ui->le_race_2->text();
        QString nom=ui->le_nom_3->text();
        int categorie=ui->le_categorie->currentIndex();
        int quantite=ui->le_quantite->text().toInt();
        QDate delai=ui->le_delai->date();




         Stock S(ref ,espece ,race,nom,categorie,quantite,delai);



          bool test=S.ajouter();

                  QMessageBox msgBox;

                     if(test)

                     {

                         msgBox.setText("ajout avec succes");


                     msgBox.exec();

                     clear3();


                     }

                     else

                     {

                         msgBox.setText("echec");

                     msgBox.exec();

                     }

     ui->tab_stock->setModel(S.afficher());}



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

void MainWindow::on_bouton_excel_clicked()
{
    QTableView *table;
     table = ui->tab_stock;

     QString filters("CSV files (*.csv);;All files (*.*)");
     QString defaultFilter("CSV files (*.csv)");
     QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                        filters, &defaultFilter);
     QFile file(fileName);

     QAbstractItemModel *model =  table->model();
     if (file.open(QFile::WriteOnly | QFile::Truncate)) {
         QTextStream data(&file);
         QStringList strList;
         for (int i = 0; i < model->columnCount(); i++) {
             if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                 strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
             else
                 strList.append("");
         }
         data << strList.join(";") << "\n";
         for (int i = 0; i < model->rowCount(); i++) {
             strList.clear();
             for (int j = 0; j < model->columnCount(); j++) {

                 if (model->data(model->index(i, j)).toString().length() > 0)
                     strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") + "\n";
         }
         file.close();
         QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
     }
}
void MainWindow::on_triernom_clicked()
{
     ui->tab_stock->setModel(S.triernom());
}

void MainWindow::on_triercategorie_clicked()
{
    ui->tab_stock->setModel(S.triercategorie());
}

void MainWindow::on_trierrace_clicked()
{
    ui->tab_stock->setModel(S.trierrace());
}
bool MainWindow::controlSaisie_stock(){


    if (

            !(ui->le_race_2->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_nom_3->text().contains(QRegExp("^[A-Za-z]+$"))) )


        return 0;
    else
        return 1;
}
void MainWindow::clear3()

{

    ui->le_reference->clear();

     ui->le_espece_2->clear();

    ui->le_race_2->clear();

    ui->le_nom_3->clear();

     ui->le_categorie->clear();

 ui->le_quantite->clear();
  ui->le_delai->clear();


}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    Seuil = arg1;
    Alert();
}

void MainWindow::on_tab_stock_clicked(const QModelIndex &index)
{

    ui->le_reference->setText(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),2)).toString());

    ui->le_espece_2->setCurrentIndex(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),5)).toInt());

    ui->le_race_2->setText(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),4)).toString());

    ui->le_nom_3->setText(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),6)).toString());
 ui->le_categorie->setCurrentIndex(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),3)).toInt());
  ui->le_delai->setDate(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),0)).toDate());
    ui->le_quantite->setText(ui->tab_stock->model()->data(ui->tab_stock->model()->index(index.row(),1)).toString());
}

void MainWindow::on_le_rechercher_textChanged(const QString &arg1)
{
    Stock S;
    int ref= ui->le_rechercher->text().toInt();
     QString race = ui->le_rechercher->text();
    QString nom = ui->le_rechercher->text();
   S.recherche(ui->tab_stock,ref,race,nom);
    if (ui->le_rechercher->text().isEmpty())
    {
        ui->tab_stock->setModel(S.afficher());
    }
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool MainWindow::controlSaisieadherent(){

    if (
            !(ui->le_nom_a->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom_a->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->id_tresorie_a->text().isEmpty() ||
            ui->id_tresorie_a->text().toInt() == 0 ||
            ui->le_id_a->text().isEmpty() ||// si vide
            ui->le_id_a->text().toInt() == 0 ) //si contient 7arff (7arfa kif yosraa  sahbtyyy )

        return 0;
    else
        return 1;
}


void MainWindow::on_pb_ajouter_a_clicked()
{
    if(!(ui->le_nom_a->text().contains(QRegExp("^[A-Za-z]+$")))){
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("nom invalide doit saisir seulment des chaine de caractere .\n"
                                "Click cancel to exit."), QMessageBox::Cancel);}
    else if(!(ui->le_prenom_a->text().contains(QRegExp("^[A-Za-z]+$")))) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("prenom invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);

    }
    else {
        int ID_ADHERENT=ui->le_id_a->text().toInt();
          QString NOM_ADHERENT=ui->le_nom_a->text();
          QString PRENOM_ADHERENT=ui->le_prenom_a->text();
           double COTISATION=ui->le_cotisation_a->text().toDouble();
           int NUM_OP = ui->id_tresorie_a->text().toInt();
           QString EMAIL=ui->email_a_2->text();




          ADHERENT AD(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT ,COTISATION,NUM_OP,EMAIL);


          bool test=AD.ajouter();
                  QMessageBox msgBox;
                     if(test)
                     {
                         msgBox.setText("ajout avec succes");

                     msgBox.exec();
                     clear2();
                     on_cotisation_clicked();
                     }
                     else
                     {
                         msgBox.setText("echec");
                     msgBox.exec();
                     }

     ui->tab_adherent->setModel(AD.afficher());}
}

void MainWindow::clear2()
{
    ui->le_id_a->clear();
     ui->le_nom_a->clear();
    ui->le_prenom_a->clear();
    ui->le_cotisation_a->clear();

    ui->id_tresorie_a->clear();
    ui->email_a_2->clear();

}

void MainWindow::on_cotisation_clicked()
{
    QString link="file:///C:/Users/dalys/OneDrive/Bureau/Smart_Aid_Association_2A11-master/Smart_Aid_Association_2A11-master/penlgine.html";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_tab_adherent_clicked(const QModelIndex &index)
{
    ui->le_id_a->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),0)).toString());
    ui->le_nom_a->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),1)).toString());
    ui->le_prenom_a->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),2)).toString());
    ui->le_cotisation_a->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),3)).toString());
    ui->id_tresorie_a->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),4)).toString());
    ui->email_a_2->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),5)).toString());

}

void MainWindow::on_le_modif_a_clicked()
{
    int ID_ADHERENT=ui->le_id_a->text().toInt();
            QString NOM_ADHERENT=ui->le_nom_a->text();
            QString PRENOM_ADHERENT=ui->le_prenom_a->text();
            float COTISATION=ui->le_cotisation_a->text().toFloat();
int NUM_OPERATION=ui->id_tresorie_a->text().toInt();
QString EMAIL=ui->email_a_2->text();

               ADHERENT AD(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,  COTISATION ,NUM_OPERATION,EMAIL);


             bool test=AD.modifier(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT, COTISATION ,NUM_OPERATION,EMAIL);
             if(test)
           {
                 ui->tab_adherent->setModel(AD.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);
             clear2();

           }
             else{
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pb_supprimer_a_clicked()
{
    int ID_ADHERENT=ui->le_id_a->text().toInt();
        bool test=AD.supprimer(ID_ADHERENT);

        if(test)
        {
              clear2();
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);}
        else{
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("échec suprresion.\n"
                                    "Click cancel to exit."), QMessageBox::Cancel);}
        ui->tab_adherent->setModel(AD.afficher());

}
// ////////////////////////////////////////////////////////////////////////////////////////



bool MainWindow::controlSaisieDonneur(){

    if (
            !(ui->le_nom_d->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom_d->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->num_op_d->text().isEmpty() ||
            ui->num_op_d->text().toInt() == 0 ||
            ui->le_id_d->text().isEmpty() ||
            ui->le_id_d->text().toInt() == 0
             )
        return 0;
    else
        return 1;
}


void MainWindow::on_pb_ajouter_d_clicked()
{
    //pour nom tkharjena nom valide
    if(!(ui->le_nom_d->text().contains(QRegExp("^[A-Za-z]+$")))){
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("nom invalide doit saisir seulment des chaine de caractere .\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    }else if(!(ui->le_prenom_d->text().contains(QRegExp("^[A-Za-z]+$")))) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("prenom invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    }
    else {
    int ID_DONNEUR=ui->le_id_d->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
            QString TYPE=ui->type_d->currentText();
    int NUM_OPERATION=ui->num_op_d->text().toInt();
    QString EMAIL=ui->email_d_2->text();




      DONNEUR D(ID_DONNEUR,NOM,PRENOM,TYPE, NUM_OPERATION,EMAIL);


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
}

void MainWindow::on_t_nom_clicked()
{
    ui->tab_donneur->setModel(D.triernom());

}

void MainWindow::on_t_prenom_clicked()
{
    ui->tab_donneur->setModel(D.trierprenom());

}

void MainWindow::on_t_id_clicked()
{
    ui->tab_donneur->setModel(D.trierid());

}

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
    if (controlSaisieDonneur()){
    int ID_DONNEUR=ui->le_id_d->text().toInt();
            QString NOM=ui->le_nom_d->text();
            QString PRENOM=ui->le_prenom_d->text();
            QString TYPE=ui->type_d->currentText();

 int NUM_OPERATION=ui->num_op_d->text().toInt();

 QString EMAIL=ui->email_d_2->text();

               DONNEUR D(ID_DONNEUR,NOM,PRENOM,TYPE ,NUM_OPERATION, EMAIL );


             bool test=D.modifier(ID_DONNEUR,NOM,PRENOM,TYPE,NUM_OPERATION,EMAIL);
             if(test)
           {
                 ui->tab_donneur->setModel(D.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);
           clear();

           }
             else
             {
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}}
    else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("veuiller remplir tous les champs correctement.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_lien_recherche_textChanged(const QString &arg1)
{
    ui->tab_donneur->setModel(D.recherche(arg1));

}

void MainWindow::on_pushButton_10_clicked()
{
    A.write_to_arduino(("5"));//output

}

void MainWindow::on_pushButton_mail_a_clicked()
{
    smtp = new Smtp("aveaveyro15@gmail.com" , "ellaba200", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->message_mail->toPlainText();

        smtp->sendMail("ilyes_test",ui->a_mail->text(),ui->objet_mail->text(),msg);

        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sended Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::clear()
{
    ui->le_id_d->clear();
     ui->le_nom_d->clear();
    ui->le_prenom_d->clear();

    ui->num_op_d->clear();
    ui->email_d_2->clear();

}


void MainWindow::on_tab_donneur_clicked(const QModelIndex &index)
{
    ui->le_id_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),0)).toString());
    ui->le_nom_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),1)).toString());
    ui->le_prenom_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),2)).toString());
    ui->type_d->setCurrentText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),3)).toString());
    ui->num_op_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),4)).toString());
    ui->email_d_2->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),5)).toString());

}


void MainWindow::update_temperature()
{
   if (A.read_from_arduino()!="")
       //
      {
     /*  QMessageBox::critical(nullptr, QObject::tr("gaz"),
                   QObject::tr("alerte gaz!.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);*/

       QSqlQuery query;
       query.prepare("INSERT INTO ALERTE_GAZ (DATE_A) "
                     "VALUES (:DATE_A)");
       query.bindValue(":DATE_A",QDateTime::currentDateTime().toString());

       query.exec();
       ui->tableView_alerte->setModel(D.getAlertes());


   }
}

void MainWindow::on_pushButton_9_clicked()
{
    w = new Chat(this);
      w->show();
}

void MainWindow::on_n_pb_deco_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_n_pb_deco_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_n_pb_deco_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_n_pb_deco_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_n_pb_deco_2_clicked()
{

}

void MainWindow::on_n_pb_deco_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_n_pb_deco_8_clicked()
{

}

void MainWindow::on_n_pb_deco_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_n_pb_deco_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_combo_modif_activated(const QString &arg1)
{
    int ID = ui->combo_modif->currentText().toInt();
     QString id_string= QString::number(ID);
            QSqlQuery query;
            query.prepare("select * from CONTRAT where ID_CONTRAT='"+id_string+"'");

            if(query.exec()){

                while(query.next())
                {
               ui->le_id->setText(query.value(0).toString());
               ui->le_nom->setText(query.value(1).toString());
                ui->le_prenom->setText(query.value(2).toString());
                ui->le_email->setText(query.value(3).toString());
                ui->date_lee->setDate(query.value(4).toDate());
                 ui->le_cin->setText(query.value(5).toString());
                 ui->le_numd->setText(query.value(6).toString());

}}
            else
                QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_trang_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->label_48->setText("Refrence");
                       ui->label_49->setText("Specie");
                       ui->label_50->setText("Race");
                       ui->label_51->setText("Name");
                       ui->label_52->setText("Category");
                       ui->label_53->setText("Quantity");
                       ui->label_54->setText("Delay");
                       ui->pb_modifier_2->setText("Modify");
                       ui->pb_ajouter_2->setText("ADD");
                       ui->pushButton_9->setText("Chat");
                       ui->n_pb_deco->setText("LogOut");
                       ui->pb_supprimer->setText("Delete");
                       ui->trierrace->setText("Sort by race");
                       ui->triercategorie->setText("Sort by category");
                       ui->triernom->setText("Sort by name");
                       ui->label_56->setText("Search");
                       ui->label_55->setText("Refrence");
                       ui->trfr_2->setText("Frensh");
                       ui->trang_2->setText("English");
}

void MainWindow::on_trfr_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction francais ","Traduction francais",QSystemTrayIcon::Information,15000);
    lng="fr";
                       // page biblo

    ui->label_48->setText("Refrence");
    ui->label_49->setText("Espese");
    ui->label_50->setText("Race");
    ui->label_51->setText("Nom");
    ui->label_52->setText("Categorie");
    ui->label_53->setText("Quantite");
    ui->label_54->setText("Delai");
    ui->pb_modifier_2->setText("Modifier");
    ui->pb_ajouter_2->setText("Ajouter");
    ui->pushButton_9->setText("Chat");
    ui->n_pb_deco->setText("Deconnexion");
    ui->pb_supprimer->setText("Supprime");
    ui->trierrace->setText("Tri par race");
    ui->triercategorie->setText("Tri par categorie");
    ui->triernom->setText("Tri par Nom");
    ui->label_56->setText("Recherche");
    ui->label_55->setText("Refrence");
    ui->trfr_2->setText("Francais");
    ui->trang_2->setText("Englais");
}

void MainWindow::on_trang_3_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_3_clicked()
{

}

void MainWindow::on_trang_4_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_4_clicked()
{

}

void MainWindow::on_trang_7_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_7_clicked()
{

}

void MainWindow::on_trang_6_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_6_clicked()
{

}

void MainWindow::on_trang_5_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_5_clicked()
{

}

void MainWindow::on_trang_9_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_9_clicked()
{

}

void MainWindow::on_trang_8_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));

    notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
    lng="ANG";
                       // page biblo

                       ui->nom_2->setText("Name");
                       ui->prenom_2->setText("First name");
                       ui->id->setText("Contract id");
                       ui->email->setText("Email");
                       ui->datee->setText("Contract date");
                       ui->cin_2->setText("NIC");
                       ui->num->setText("File number");
                       ui->pb_ajouter->setText("Add");
                       ui->pb_modifier->setText("Modify");
                       ui->pb_supp->setText("Delete");
                       ui->tr1->setText("Sort by name");
                       ui->tr2->setText("Sort by id");
                       ui->tr3->setText("Sort by date");
                       ui->cherche_li->setText("Search");
                       ui->imprimer->setText("Print");
                       ui->trfr->setText("Frensh");
                       ui->trang->setText("English");
}

void MainWindow::on_trfr_8_clicked()
{

}
