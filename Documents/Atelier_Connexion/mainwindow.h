#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"adherent.h"
#include"donneur.h"

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

    
    void on_pb_supprimer_clicked();



    void on_le_afficher_clicked();

    void on_le_modif_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
   ADHERENT A;
   DONNEUR D;

};

#endif // MAINWINDOW_H
