#ifndef STOCK_H
#define STOCK_H
#include <QSqlQueryModel>
#include <QString>
class Stock
{
public:
    Stock();
    Stock (int ,QString,QString,QString,QString);
    int getref();
    QString getespece();
    QString getrace();
    QString getnom();
    QString getcategorie();
    void setref(int);
    void setespece(QString);
    void setrace(QString);
    void setnom(QString);
    void setcategorie(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierStock(int ref,QString espece,QString race,QString nom,QString categorie);
private:
    int ref  ;
    QString  espece , race ,nom ,categorie;

     
};

#endif // STOCK_H
