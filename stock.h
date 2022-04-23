#ifndef STOCK_H
#define STOCK_H
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QTableView>
#include <QSystemTrayIcon>
#include <QLabel>
class Stock
{
public:
    Stock();
    Stock (int ,int,QString,QString,int,int,QDate);
    int getref();
    int getespece();
    QString getrace();
    QString getnom();
    int getcategorie();
    int getquantite();
    QDate getdelai ();
    void setref(int);
    void setespece(int);
    void setrace(QString);
    void setnom(QString);
    void setcategorie(int);
    void setquantite (int);
    void setdelai (QDate);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierStock(int ref,int espece,QString race,QString nom,int categorie,int quantite,QDate delai);
    QSqlQueryModel * triernom();
    QSqlQueryModel * triercategorie();
    QSqlQueryModel * trierrace();
     void recherche(QTableView * table, int,QString,QString);
      bool envoyerMessage(int ,QString );
     QSqlQueryModel * messagesEnvoyees();
     QSqlQueryModel * getTRESORIER();
      bool envoyerM(int ,QString );
      QSqlQueryModel * getstock();

private:
    int ref,quantite ,categorie ,espece;
    QString   race ,nom ;
    QDate delai ;
    QSystemTrayIcon* sticon;
    QLabel* text;

     
};

#endif // STOCK_H
