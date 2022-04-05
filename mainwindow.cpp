#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include <QMessageBox>
#include <QMainWindow>
#include "donneur.h"
#include <QtWidgets/QRadioButton>
#include <QtSql/QSqlQueryModel>
#include <QDesktopServices>

//besmeeelaaahhhhhh  //
ADHERENT A;
DONNEUR D;
void recherche(QTableView * tab_donneur, int,QString,QString);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_adherent->setModel(A.afficher());
     ui->tab_donneur->setModel(D.afficher());
     QValidator *validator = new QIntValidator(1, 99999999, this); // pour les int
    QValidator *validatorDouble = new QDoubleValidator(0.0, 999,2, this);
     //alidator hya validateur yaaml condiction mn 1  l 999999 akahw
     //QLineEdit *edit = new QLineEdit(this);
     //donneur
     ui->le_id_d->setValidator(validator);
     ui->num_op_donneur->setValidator(validator);
     ui->le_id->setValidator(validator);
     ui->id_tresorie_adherent->setValidator(validator);
     ui->le_cotisation->setValidator(validatorDouble);

     // adherent
     ////vali
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::controlSaisie(){
    QRegularExpression regex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");


    if (
            !(ui->le_nom_d->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom_d->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_email->text().contains(QRegExp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b"))) ||
            ui->num_op_donneur->text().isEmpty() ||
            ui->num_op_donneur->text().toInt() == 0 ||
            ui->le_id_d->text().isEmpty() ||
            ui->le_id_d->text().toInt() == 0
             )
        return 0;
    else
        return 1;
}
bool MainWindow::controlSaisie2(){

    if (
            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) || //frme mn google ( regex )
            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_email_a->text().contains(QRegExp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b"))) ||
            ui->id_tresorie_adherent->text().isEmpty() ||
            ui->id_tresorie_adherent->text().toInt() == 0 ||
            ui->le_id->text().isEmpty() ||// si vide
            ui->le_id->text().toInt() == 0 ) //si contient 7arff (7arfa kif yosraa  sahbtyyy )

        return 0;
    else
        return 1;
}
//adherent

void MainWindow::on_pb_ajouter_clicked()
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);

    if(!(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$")))){
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("nom invalide doit saisir seulment des chaine de caractere .\n"
                                "Click cancel to exit."), QMessageBox::Cancel);}
    else if(!(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$")))) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("prenom invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);

    } else if(!mailREX.exactMatch(ui->le_email_a->text())) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("email invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);

    }
    else {
        int ID_ADHERENT=ui->le_id->text().toInt();
          QString NOM_ADHERENT=ui->le_nom->text();
          QString PRENOM_ADHERENT=ui->le_prenom->text();
          QString EMAIL=ui->le_email_a->text();
           double COTISATION=ui->le_cotisation->text().toDouble();
           int NUM_OPERATION = ui->id_tresorie_adherent->text().toInt();



          ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT ,EMAIL, COTISATION,NUM_OPERATION);


          bool test=A.ajouter();
                  QMessageBox msgBox;
                     if(test)
                     {
                         msgBox.setText("ajout avec succes");

                     msgBox.exec();
                     clear2();
                     QString link="file:///C:/Users/user/Desktop/web/penlgine.html";
                         QDesktopServices::openUrl(QUrl(link));
                     }
                     else
                     {
                         msgBox.setText("echec");
                     msgBox.exec();
                     }
     ui->tab_adherent->setModel(A.afficher());}

}
void MainWindow::on_pb_supprimer_clicked()

    {
        int ID_ADHERENT=ui->le_id->text().toInt();
            bool test=A.supprimer(ID_ADHERENT);

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
            ui->tab_adherent->setModel(A.afficher());


}



void MainWindow::on_le_afficher_clicked()
{

}

void MainWindow::on_le_modif_clicked()
{
    int ID_ADHERENT=ui->le_id->text().toInt();
            QString NOM_ADHERENT=ui->le_nom->text();
            QString PRENOM_ADHERENT=ui->le_prenom->text();
             QString EMAIL=ui->le_email_a->text();
            float COTISATION=ui->le_cotisation->text().toFloat();
int NUM_OPERATION=ui->num_op_donneur->text().toInt();
               ADHERENT A(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,EMAIL, COTISATION ,NUM_OPERATION);


             bool test=A.modifier(ID_ADHERENT,NOM_ADHERENT,PRENOM_ADHERENT,EMAIL, COTISATION ,NUM_OPERATION);
             if(test)
           {
                 ui->tab_adherent->setModel(A.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                             QObject::tr("invite modifiée.\n"
                                         "Click ok to exit."), QMessageBox::Ok);
             clear2();

           }
             else{
                 QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                             QObject::tr("echec d'ajout !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);} }

void MainWindow::clear2()
{
    ui->le_id->clear();
     ui->le_nom->clear();
    ui->le_prenom->clear();
    ui->le_cotisation->clear();
     ui->le_email_a->clear();

    ui->id_tresorie_adherent->clear();
}

/*donneuuuuuuuuuuuuuur*/ //yemchyyyyyyyyyyyyyyy//


void MainWindow::on_pb_ajouter_d_clicked()
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
    //pour nom tkharjena nom valide
    if(!(ui->le_nom_d->text().contains(QRegExp("^[A-Za-z]+$")))){
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("nom invalide doit saisir seulment des chaine de caractere .\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    }else if(!(ui->le_prenom_d->text().contains(QRegExp("^[A-Za-z]+$")))) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("prenom invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
    } else if(!mailREX.exactMatch(ui->le_email->text())) {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("email invalide.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);

    }
    else {
    int ID_DONNEUR=ui->le_id_d->text().toInt();
      QString NOM=ui->le_nom_d->text();
      QString PRENOM=ui->le_prenom_d->text();
       QString EMAIL=ui->le_email->text();
            QString TYPE=ui->type_d->currentText();
    int NUM_OPERATION=ui->num_op_donneur->text().toInt();



      DONNEUR D(ID_DONNEUR,NOM,PRENOM,EMAIL,TYPE, NUM_OPERATION );


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
// pour clear

void MainWindow::clear()
{
    ui->le_id_d->clear();
     ui->le_nom_d->clear();
    ui->le_prenom_d->clear();
    ui->le_email->clear();

    ui->num_op_donneur->clear();
}





//affich donneur


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
    if (controlSaisie()){
    int ID_DONNEUR=ui->le_id_d->text().toInt();
            QString NOM=ui->le_nom_d->text();
            QString PRENOM=ui->le_prenom_d->text();
            QString EMAIL=ui->le_email->text();
            QString TYPE=ui->type_d->currentText();

 int NUM_OPERATION=ui->num_op_donneur->text().toInt();


               DONNEUR D(ID_DONNEUR,NOM,PRENOM,EMAIL,TYPE ,NUM_OPERATION );


             bool test=D.modifier(ID_DONNEUR,NOM,PRENOM,EMAIL,TYPE,NUM_OPERATION);
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






// pour selectionnnnn modiferr et suprr
// model afiicher de donne
// data donne
void MainWindow::on_tab_donneur_clicked(const QModelIndex &index)
{
    ui->le_id_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),0)).toString());
    ui->le_nom_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),1)).toString());
    ui->le_prenom_d->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),2)).toString());
    ui->type_d->setCurrentText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),3)).toString());
    ui->num_op_donneur->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),4)).toString());
    ui->le_email->setText(ui->tab_donneur->model()->data(ui->tab_donneur->model()->index(index.row(),5)).toString());
}







/*

    smtp = new Smtp("aveaveyro15@gmail.com" , "ellaba200", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    msg=ui->message_mail->toPlainText();

    smtp->sendMail("ilyes_test",ui->a_mail->text(),ui->objet_mail->text(),msg);

    QMessageBox::information(nullptr, QObject::tr("SENT"),
                             QObject::tr("Email Sended Successfully.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

  */

void MainWindow::on_tab_adherent_clicked(const QModelIndex &index)
{

    ui->le_id->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),0)).toString());
    ui->le_nom->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),1)).toString());
    ui->le_prenom->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),2)).toString());
    ui->le_cotisation->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),3)).toString());
    ui->id_tresorie_adherent->setText(ui->tab_adherent->model()->data(ui->tab_adherent->model()->index(index.row(),4)).toString());
}


//recherche//
void MainWindow::on_le_id_d_textChanged(const QString &arg1)
{
   // ui->tab_donneur->setModel(D.recherche(arg1));
}

void MainWindow::on_le_nom_d_textChanged(const QString &arg1)
{
    // ui->tab_donneur->setModel(D.rechercheN(arg1));
}

void MainWindow::on_le_prenom_d_textChanged(const QString &arg1)
{
 //   ui->tab_donneur->setModel(D.rechercheP(arg1));
}

void MainWindow::on_lien_recherche_textChanged(const QString &arg1)
{
    ui->tab_donneur->setModel(D.recherche(arg1));
}

void MainWindow::on_pushButton_clicked()
{
    smtp = new Smtp("aveaveyro15@gmail.com" , "ellaba200", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->message_mail->toPlainText();

        smtp->sendMail("object abrar",ui->a_mail->text(),ui->objet_mail->text(),msg);

        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sended Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}
//cotisation booooutoon
void MainWindow::on_pushButton_lien_clicked()
{
    QString link="file:///C:/Users/user/Desktop/web/penlgine.html";
        QDesktopServices::openUrl(QUrl(link));

}
//exit
void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0); //tbdel l page//
}
