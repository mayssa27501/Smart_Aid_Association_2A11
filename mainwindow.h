#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_mod_btn_clicked();

    void on_tri_cin_clicked();



    void on_tri_date_clicked();

    void on_tri_salaire_clicked();

    void on_Afficher_li_clicked();

    void on_cherche_li_textChanged(const QString &arg1);


    void on_connecter_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
