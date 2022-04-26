#include "DuMesengerConnectionDialog.h"
#include "ui_DuMesengerConnectionDialog.h"
namespace DuarteCorporation
{
DuMesengerConnectionDialog::DuMesengerConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMesengerConnectionDialog)
{
    ui->setupUi(this);
}

DuMesengerConnectionDialog::~DuMesengerConnectionDialog()
{
    delete ui;
}

void DuarteCorporation::DuMesengerConnectionDialog::on_ok_clicked()
{
    mHostname = ui->hostname->text();
    mPort = ui->port->value();
    accept();
}
}

void DuarteCorporation::DuMesengerConnectionDialog::on_cancel_clicked()
{
    reject();
}
