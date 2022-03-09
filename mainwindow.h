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
//8888888git
private slots:
bool controlsaisie();

    void on_pb_ajouter_clicked();


    void on_pb_supp_clicked();

    void on_pb_afficher_clicked();

    void on_pb_modif_clicked();

    void on_trinum_clicked();

    void on_tridate_clicked();

    void on_tabnom_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_cherche_li_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Dossier_medical DM;
};

#endif // MAINWINDOW_H
