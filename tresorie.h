#ifndef TRESORIE_H
#define TRESORIE_H
//
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>


#include <QString>



class tresorie

{

public:

    tresorie();

    tresorie(int,QString,QString,float,QDate);

    int getnum_op();

    QString gettype();

     QString getdescriptive();

     float getmontant();

     QDate getdate_ajout();


     void setnum_op(int);

    void settype(QString);

    void setdescriptive(QString);

     void setmontant(float);

     void setdate_ajout(QDate);

    bool ajouter();
    QSqlQueryModel* afficher();

    bool supprimer(int);

    bool modifier(int,QString,QString,float,QDate);

    QSqlQueryModel * trierdate();

    QSqlQueryModel * triertype();

    QSqlQueryModel * triermontant();

    void recherche(QTableView * tabl, int,QString,QString);


private:

    int num_op;

    QString type,descriptive;
    float montant;

    QDate date_ajout;

};
#endif // TRESORIE_H
