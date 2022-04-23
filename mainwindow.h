#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stock.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool controlSaisie();
     void Alert();
     void refresh();
     void refresh1();
     void clear3();
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();
    void on_triernom_clicked();

    void on_triercategorie_clicked();

    void on_trierrace_clicked();






    void on_le_rechercher_textChanged(const QString &arg1);

    void on_bouton_excel_clicked();

    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_envoyerMessage_clicked();
void on_pb_envoyer_clicked();
void on_tab_stock_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Stock S;
    int Seuil;
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
};

#endif // MAINWINDOW_H
