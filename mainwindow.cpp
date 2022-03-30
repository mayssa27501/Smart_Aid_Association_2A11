#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stock.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QIntValidator>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlRecord>
Stock S;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_reference->setValidator(new QIntValidator(0, 9999999, this));
      ui->le_quantite->setValidator(new QIntValidator(0, 999999, this));
    ui->tab_stock->setModel(S.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::controlSaisie(){


    if (

            !(ui->le_race->text().contains(QRegExp("^[A-Za-z]+$"))) ||
            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) )


        return 0;
    else
        return 1;
}

void MainWindow::on_pb_ajouter_clicked()
{
    if (controlSaisie()){
    int ref=ui->le_reference->text().toInt();
    int espece=ui->le_espece->currentIndex();
    QString race=ui->le_race->text();
    QString nom=ui->le_nom->text();
    int categorie=ui->le_categorie->currentIndex();
    int quantite=ui->le_quantite->text().toInt();
    QDate delai=ui->le_delai->date();

    Stock S(ref ,espece ,race,nom,categorie,quantite,delai);
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
               }}
     else {
                   QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("veuiller remplir tous les champs correctement.\n"
                                           "Click cancel to exit."), QMessageBox::Cancel);
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
    if (controlSaisie()){
    int ref=ui->le_reference->text().toInt();
    int espece=ui->le_espece->currentIndex();
            QString race=ui->le_race->text();
            QString nom=ui->le_nom->text();
            int categorie=ui->le_categorie->currentIndex();
    int quantite=ui->le_quantite->text().toInt();
    QDate delai=ui->le_delai->date();



         ui->le_race->setMaxLength(20);
            ui->le_nom->setMaxLength(5); // max longueur

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





void MainWindow::on_le_rechercher_textChanged(const QString &arg1)
{
    Stock S;
    int ref= ui->le_rechercher->text().toInt();
    int espece = ui->le_rechercher->text().toInt();
    QString nom = ui->le_rechercher->text();
   S.recherche(ui->tab_stock,ref,espece,nom);
    if (ui->le_rechercher->text().isEmpty())
    {
        ui->tab_stock->setModel(S.afficher());
    }
}

void MainWindow::on_bouton_excel_clicked()
{

    QTableView *table;
                   table = ui->tab_stock;

                   QString filters("CSV files (.xlsx);;All files (.*)");
                   QString defaultFilter("CSV files (*.xlsx)");
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
                       QMessageBox::information(nullptr, QObject::tr("Exporter le fichier excel"),
                                                 QObject::tr("Fichier Générer avec succès .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }
}
