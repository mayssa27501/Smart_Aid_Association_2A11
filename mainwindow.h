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
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

private:
    Ui::MainWindow *ui;
    Stock S;
};

#endif // MAINWINDOW_H
