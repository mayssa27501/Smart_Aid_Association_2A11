#ifndef CONTRAT_H
#define CONTRAT_H
#include <QString>
#include <QSqlQueryModel>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QMainWindow>
#include <QDate>
#include <QTableView>



class Contrat
{
public:
    Contrat();
    Contrat(int,QString,QString,QString,QDate,int,int);
    int getid_contrat();
    QString getnom();
    QString getprenom();
    QString getemail();
    QDate getdate_contrat();
    int getcin_employe();
    int getnum_dossier();
    void setid_contrat(int);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void setdate_contrat(QDate);
    void setcin_employe(int);
    void setnum_dossier(int);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QDate,int,int);
    QSqlQueryModel * trierid();
    QSqlQueryModel * triernom();
    QSqlQueryModel * trierdate();
    void recherche(QTableView * tabl, int,QString,QString);
    void telechargerPDF();

private:
    int id_contrat;
    QString nom,prenom,email;
    QDate date_contrat;
    int cin_employe;
    int num_dossier;
};

#endif // CONTRAT_H
