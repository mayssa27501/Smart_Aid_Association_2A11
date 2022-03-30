#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include "historique.h"
#include <QMessageBox>
#include <QMainWindow>
#include<QFileDialog>
#include<QPrinter>
#include<QString>
#include<QDateTime>
#include<QTextStream>
#include<QTextDocument>
#include<QPrintDialog>
#include <QSystemTrayIcon>
#include <QTimer>


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
    showtime();
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();
}

void MainWindow::showtime()
{
    QTime time=QTime::currentTime();

    QString time_next=time.toString("hh : mm : ss");
    ui->digital_clock->setText(time_next);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::controlSaisie(){
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
               H.saveajouter();
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

        if(test){
            H.savesupp();
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("supression effectué .\n"
                                    "Click Ok to exit."), QMessageBox::Ok);}
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
    H.savemodifier();
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


void MainWindow::on_tr1_clicked()
{
ui->tableView->setModel(C.trierid());
H.savetri1();
}

void MainWindow::on_tr2_clicked()
{
ui->tableView->setModel(C.triernom());
H.savetri2();
}

void MainWindow::on_tr3_clicked()
{
ui->tableView->setModel(C.trierdate());
H.savetri3();
}


void MainWindow::on_cherche_li_textChanged(const QString &arg1)
{
    Contrat C;



    int id_contrat= ui->cherche_li->text().toInt();

    QString nom = ui->cherche_li->text();

    QString prenom = ui->cherche_li->text();

    C.recherche(ui->tableView,id_contrat,nom,prenom);

    if (ui->cherche_li->text().isEmpty())

    {
    H.savecher();
        ui->tableView->setModel(C.afficher());
}
}




void MainWindow::on_trang_clicked()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    H.saveang();
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("Traduction Anglais ","Traduction Anglais",QSystemTrayIcon::Information,15000);
        lng="ANG";
                           // page biblo

                           ui->nom->setText("Name");
                           ui->prenom->setText("First name");
                           ui->id->setText("Contract id");
                           ui->email->setText("Email");
                           ui->datee->setText("Contract date");
                           ui->cin->setText("NIC");
                           ui->num->setText("File number");
                           ui->pb_ajouter->setText("Add");
                           ui->pb_modifier->setText("Modify");
                           ui->pb_supp->setText("Delete");
                           ui->tr1->setText("Sort by name");
                           ui->tr2->setText("Sort by id");
                           ui->tr3->setText("Sort by date");
                           ui->cherche_li->setText("Search");
                           ui->archiver->setText("Archive");
                           ui->imprimer->setText("Print");
                           ui->trfr->setText("Frensh");
                           ui->trang->setText("English");
}

void MainWindow::on_trfr_clicked()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    H.savefr();
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("Traduction francais ","Traduction francais",QSystemTrayIcon::Information,15000);
        lng="fr";
                           // page biblo

                           ui->nom->setText("Nom");
                           ui->prenom->setText("Prenom");
                           ui->id->setText("Id contrat");
                           ui->email->setText("Email");
                           ui->datee->setText("Date Contrat");
                           ui->cin->setText("CIN");
                           ui->num->setText("Num dossier");
                           ui->pb_ajouter->setText("Ajouter");
                           ui->pb_modifier->setText("Modifier");
                           ui->pb_supp->setText("Supprimer");
                           ui->tr1->setText("Trie par nom");
                           ui->tr2->setText("Trie par id");
                           ui->tr3->setText("Trie par date");
                           ui->cherche_li->setText("Recherche");
                           ui->archiver->setText("Archiver");
                           ui->imprimer->setText("Imprimer");
                           ui->trfr->setText("Français");
                           ui->trang->setText("Anglais");
}

void MainWindow::on_imprimer_clicked()
{
    H.saveimp();
    QPrinter printer;

        printer.setPrinterName("desiered printer name");

      QPrintDialog dialog(&printer,this);

        if(dialog.exec()== QDialog::Rejected)

            return;
}



