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
#include <QPdfWriter>


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
               QFile f("C:/Atelier_Connexion/historique.txt");
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
            QFile f("C:/Atelier_Connexion/historique.txt");
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
                QTextStream out(&strStream);            QMessageBox::information(nullptr, QObject::tr("ok"),
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
          QFile f("C:/Atelier_Connexion/historique.txt");
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
}


void MainWindow::on_tr1_clicked()
{
ui->tableView->setModel(C.trierid());
QFile f("C:/Atelier_Connexion/historique.txt");
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
QFile f("C:/Atelier_Connexion/historique.txt");
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
QFile f("C:/Atelier_Connexion/historique.txt");
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


void MainWindow::on_cherche_li_textChanged(const QString &arg1)
{
    Contrat C;

    QFile f("C:/Atelier_Connexion/historique.txt");
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

    int id_contrat= ui->cherche_li->text().toInt();

    QString nom = ui->cherche_li->text();

    QString prenom = ui->cherche_li->text();

    C.recherche(ui->tableView,id_contrat,nom,prenom);

    if (ui->cherche_li->text().isEmpty())

    {

        ui->tableView->setModel(C.afficher());
}
}




void MainWindow::on_trang_clicked()
{
    QFile f("C:/Atelier_Connexion/historique.txt");
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
                           ui->imprimer2->setText("Print2");
                           ui->imprimer->setText("Print");
                           ui->trfr->setText("Frensh");
                           ui->trang->setText("English");
}

void MainWindow::on_trfr_clicked()
{
    QFile f("C:/Atelier_Connexion/historique.txt");
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
                           ui->imprimer2->setText("Imprimer2");
                           ui->imprimer->setText("Imprimer");
                           ui->trfr->setText("Français");
                           ui->trang->setText("Anglais");
}

void MainWindow::on_imprimer_clicked()
{

    QFile f("C:/Atelier_Connexion/historique.txt");
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
    QFile f("C:/Atelier_Connexion/historique.txt");
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
