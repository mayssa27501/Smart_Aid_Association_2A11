#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <dossier_medical.h>
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

private slots:


    void on_pb_ajouter_clicked();


    void on_pb_supp_clicked();

    void on_pb_afficher_clicked();

    void on_pb_modif_clicked();

    void on_trinum_clicked();

    void on_tridate_clicked();

    void on_tabnom_clicked();

private:
    Ui::MainWindow *ui;
    Dossier_medical DM;
};

#endif // MAINWINDOW_H
