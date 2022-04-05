#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"adherent.h"
#include"donneur.h"
#include "smtp.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool controlSaisie(); //pour adherent
    bool controlSaisie2(); //pour donnneeeurrrr
    void clear();
    void clear2(); // ki tajoty tetnahaa

private slots:
    void on_pb_ajouter_clicked();

    
    void on_pb_supprimer_clicked();



    void on_le_afficher_clicked();

    void on_le_modif_clicked();



   // void on_pushButton_clicked();
//trinom
    void on_t_nom_clicked();

    void on_pb_suppr_d_clicked();

    void on_le_mod_d_clicked();

    void on_pb_ajouter_d_clicked();


    void on_t_prenom_clicked();

    void on_t_id_clicked();

    void on_tab_donneur_clicked(const QModelIndex &index);


    void on_tab_adherent_clicked(const QModelIndex &index);

   // void on_le_recherche_textChanged(const QString &arg1);

    void on_le_id_d_textChanged(const QString &arg1);

    void on_le_nom_d_textChanged(const QString &arg1);

    void on_le_prenom_d_textChanged(const QString &arg1);

    void on_lien_recherche_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_lien_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
   ADHERENT A;
   DONNEUR D;
   Smtp* smtp;//mail
   QString msg;
   QString mail;



};

#endif // MAINWINDOW_H
