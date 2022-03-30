#ifndef RESSOURCEHUMAINE_H
#define RESSOURCEHUMAINE_H
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPdfWriter>
#include <QString>
#include <QPainter>

//dsfdsf

class RESSOURCE_HUMAINE

{

public:

    RESSOURCE_HUMAINE();

    RESSOURCE_HUMAINE(int,QString,QString,QString,QDate,int,float,QString,int);

    int getID_EMP();

    QString getNOM();

     QString getPRENOM();

     QString getMETIER();

     QDate getDATE_NAISSANCE();

     int getTEL();

    float getSALAIRE();

    QString getVILLE();

    int getID_DIRIGEANT();


    void setID_EMP(int);

    void setNOM(QString);

    void setPRENOM(QString);

     void setMETIER(QString);

     void setDATE_NAISSANCE(QDate);

     void setTEL(int);

    void setSALAIRE(float);

    void setVILLE(QString);

    void setID_DIRIGEANT(int);



    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QDate,int,float,QString,int);
    QSqlQueryModel * triercin();
    QSqlQueryModel * trierdate();
    QSqlQueryModel * triersalaire();
    void recherche(QTableView * tabl, int,QString,QString);
    void telechargerPDF();

    bool modifier_emploi(QString mtrcl, QDateTime dateS, QDateTime dateE);

private:

    int ID_EMP;

    QString NOM,PRENOM,METIER;

    QDate DATE_NAISSANCE;

    int TEL;

    float SALAIRE;

    QString VILLE;

    int ID_DIRIGEANT;
    QString emploi;


};

#endif // RESSOURCEHUMAINE_H
