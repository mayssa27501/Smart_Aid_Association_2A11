#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ressourcehumaine.h"
#include "arduino.h"
#include "contrat.h"
#include "historique.h"
#include "dossier_medical.h"
#include "tresorie.h"
#include "chat.h"
#include "stock.h"
using namespace DuarteCorporation;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
     bool controlSaisie();
     bool controlSaisie1();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void clear3();
     bool controlSaisie_stock();

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

    void on_triernom_clicked();

    void on_triercategorie_clicked();

    void on_trierrace_clicked();


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

    void update_label();


   //  //////////////////////////////////////////////////////////////////////// //



    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_modifier_clicked();

    void on_tr1_clicked();

    void on_tr2_clicked();

    void on_tr3_clicked();

    void on_cherche_li_2_textChanged(const QString &arg1);


    void on_trang_clicked();

    void on_trfr_clicked();

    void on_imprimer_clicked();

    void on_his_clicked();

    void on_pdf_clicked();


    void on_imprimer2_clicked();

 // ////////////////////////////////////////////////////////////////////////////////

    bool controlsaisie3();

    void on_pb_ajouter_3_clicked();


    void on_pb_supp_3_clicked();

    void on_pb_afficher_2_clicked();

    void on_pb_modif_2_clicked();

    void on_trinum_2_clicked();

    void on_tridate_2_clicked();

    void on_tabnom_2_clicked();

   // void on_lineEdit_textChanged(const QString &arg1);

    void on_cherche_li_4_textChanged(const QString &arg1);

    void on_tabafficher_2_clicked(const QModelIndex &index);





    void on_comboBox_5_activated(const QString &arg1);

    void on_ajouter_li_clicked();

    void on_modif_btn_clicked();

    void on_supp_btn_clicked();

    void on_tri_type_clicked();

    void on_tri_date_2_clicked();

    void on_tri_montant_clicked();

    void on_cherche_li_3_textChanged(const QString &arg1);

    void on_imprimer_2_clicked();

    void on_stat_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_clicked();

    void on_bouton_excel_clicked();

    void Alert();

    void on_spinBox_valueChanged(int arg1);

    void on_tab_stock_clicked(const QModelIndex &index);

    void on_le_rechercher_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    RESSOURCE_HUMAINE RH;
    bool dateTimeEditS_hadfocus = false;
    bool dateTimeEditE_hadfocus = false;
    void peupler_champs_modif(const QString& matricule);
 Arduino A; // objet temporaire
 QString lng;
 Chat *w;
 historique H;
 Dossier_medical DM;
 QByteArray data; // variable contenant les données reçues
 Stock S;
 int Seuil;
 QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

};

#endif // MAINWINDOW_H
