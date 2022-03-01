#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(mainwindow.ui);
}

login::~login()
{
    delete ui;
}




void login::on_login_btn_clicked()
{
    QString username = ui->nom_li->text();
            QString password = ui->pass_li->text();

            if(username ==  "ilef" && password == "ilef") {
                QMessageBox::information(this, "Login", "Username and password is correct");
                //hide();

            }
            else {
                QMessageBox::warning(this,"Login", "Username and password is not correct");
            }
}
