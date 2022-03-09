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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool controlSaisie();
private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_modifier_clicked();

    void on_tr1_clicked();

    void on_tr2_clicked();

    void on_tr3_clicked();

    void on_cherche_li_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
