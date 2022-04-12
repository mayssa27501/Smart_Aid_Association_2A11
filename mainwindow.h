#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ressourcehumaine.h"
#include "arduino.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
     bool controlSaisie();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Ajouter_clicked();



    void on_Supp_btn_clicked();


    void on_tri_cin_clicked();



    void on_tri_date_clicked();

    void on_tri_salaire_clicked();

    void on_cherche_li_textChanged(const QString &arg1);

    void showtime();

    void on_connecter_clicked();

    void on_calendarWidget_clicked(const QDate &date);




    void on_change_activated(const QString &arg1);





    void on_modifer_btn_clicked();

    void on_Afficher_li_clicked();

    void on_telechargerPDF_clicked();


    void on_tableView_emploi_clicked(const QModelIndex &index);


    void on_pushButton_emploi_goto_clicked();

    void on_dateTimeEdit_emploiS_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_emploiE_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_mdf_emploi_clicked();


    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    RESSOURCE_HUMAINE RH;
    bool dateTimeEditS_hadfocus = false;
    bool dateTimeEditE_hadfocus = false;
    void peupler_champs_modif(const QString& matricule);
 Arduino A; // objet temporaire
};

#endif // MAINWINDOW_H
