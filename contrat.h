#ifndef CONTRAT_H
#define CONTRAT_H
#include <QString>
#include <QSqlQueryModel>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QMainWindow>

class Contrat
{
public:
    Contrat();
    Contrat(int,QString,QString,QString,int,int);
    int getid_contrat();
    QString getnom();
    QString getprenom();
    QString getemail();
    int getdate_contrat();
    int getnum_dossier();
    void setid_contrat(int);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void setdate_contrat(int);
    void setnum_dossier(int);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int,int);
private:
    int id_contrat;
    QString nom,prenom,email;
    int date_contrat;
    int num_dossier;
};

#endif // CONTRAT_H
