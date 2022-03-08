#ifndef RESSOURCEHUMAINE_H
#define RESSOURCEHUMAINE_H
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>

#include <QString>



class RESSOURCE_HUMAINE

{

public:

    RESSOURCE_HUMAINE();

    RESSOURCE_HUMAINE(int,QString,QString,QString,QDate,int,float,int,int,int);

    int getCIN();

    QString getNOM();

     QString getPRENOM();

     QString getMETIER();

     QDate getDATE_NAISSANCE();

     int getTEL();

    float getSALAIRE();

    int getID_TRESORIE();

    int getID_STOCK();

    int getCIN_DIRIGEANT();


     void setCIN(int);

    void setNOM(QString);

    void setPRENOM(QString);

     void setMETIER(QString);

     void setDATE_NAISSANCE(QDate);

     void setTEL(int);

    void setSALAIRE(float);

    void setID_TRESORIE(int);

     void setID_STOCK(int);

    void setCIN_DIRIGEANT(int);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QDate,int,float,int,int,int);
    QSqlQueryModel * triercin();
QSqlQueryModel * trierdate();
QSqlQueryModel * triersalaire();
void recherche(QTableView * tabl, int,QString,QString);


private:

    int CIN;

    QString NOM,PRENOM,METIER;

    QDate DATE_NAISSANCE;

    int TEL;

    float SALAIRE;

    int ID_TRESORIE,ID_STOCK,CIN_DIRIGEANT;
};

#endif // RESSOURCEHUMAINE_H
