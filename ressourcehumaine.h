#ifndef RESSOURCEHUMAINE_H
#define RESSOURCEHUMAINE_H
#include <QDate>
#include <QSqlQueryModel>


#include <QString>



class RESSOURCE_HUMAINE

{

public:

    RESSOURCE_HUMAINE();

    RESSOURCE_HUMAINE(int,QString,QString,QString,QDate,int,float);

    int getCIN();

    QString getNOM();

     QString getPRENOM();

     QString getMETIER();

     QDate getDATE_NAISSANCE();

     int getTEL();

    float getSALAIRE();


     void setCIN(int);

    void setNOM(QString);

    void setPRENOM(QString);

     void setMETIER(QString);

     void setDATE_NAISSANCE(QDate);

     void setTEL(int);

    void setSALAIRE(float);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QDate,int,float);




private:

    int CIN;

    QString NOM,PRENOM,METIER;

    QDate DATE_NAISSANCE;

    int TEL;

    float SALAIRE;
};

#endif // RESSOURCEHUMAINE_H
