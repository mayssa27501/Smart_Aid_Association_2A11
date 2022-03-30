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
#include <QDateTime>

RESSOURCE_HUMAINE RH;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cin->setValidator(new QIntValidator(0,99999999,this));
    ui->numero->setValidator(new QIntValidator(0,99999999,this));
    ui->cin_Dirgeant->setValidator(new QIntValidator(0,99999999,this));

    ui->affiche_tab->setModel(RH.afficher());
    ui->change->setModel(RH.afficher());
    ui->comboBox_2->setModel(RH.afficher());
    ui->comboBox->setModel(RH.afficher());

        ui->tableView_emploi->setModel(RH.afficher());
        ui->dateEdit_emploi->setDisplayFormat("d MMM yyyy");
        ui->dateTimeEdit_emploiS->setDisplayFormat("d MMM yyyy h:m");
        ui->dateTimeEdit_emploiE->setDisplayFormat("d MMM yyyy h:m");
        ui->dateEdit_emploi->setDate(QDate::currentDate());
        ui->dateTimeEdit_emploiS->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEdit_emploiE->setDateTime(QDateTime::currentDateTime().addDays(1));
        ui->calendarWidget->setDateRange(QDate::currentDate(), QDate::currentDate().addDays(14));

        showtime();
        QTimer *timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
        timer->start();

}

void MainWindow::showtime()
{
    QTime time=QTime::currentTime();

    QString time_next=time.toString("hh : mm : ss");
    ui->Digital_clock->setText(time_next);
    ui->Digital_clock_2->setText(time_next);
    ui->Digital_clock_3->setText(time_next);
    ui->Digital_clock_4->setText(time_next);

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
        QString VILLE=ui->le_ville->text();
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
                 ui->le_ville->setText(query.value(7).toString());
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
    QString VILLE=ui->le_ville->text();
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
    ui->tableView_emploi->setModel(RH.afficher());

}

void MainWindow::on_telechargerPDF_clicked()
{
    RH.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}


void MainWindow::on_tableView_emploi_clicked(const QModelIndex &index)
{
    QString mtrcl_emp = ui->tableView_emploi->model()->index(index.row(), 0).data().toString();
     ui->label_mtrcl_emploi->setText(mtrcl_emp);
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

    QString mtrcl = ui->label_mtrcl_emploi->text();
     QDateTime dateS = ui->dateTimeEdit_emploiS->dateTime();
     QDateTime dateE = ui->dateTimeEdit_emploiE->dateTime();
     qDebug() << RH.modifier_emploi(mtrcl, dateS, dateE);

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


                            if  (ui->textEdit->toPlainText()== "tunis")
                                        {ui->label_pic->clear();

                                  QPixmap pix("C:/Users/dalys/OneDrive/Bureau/map.png");
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
