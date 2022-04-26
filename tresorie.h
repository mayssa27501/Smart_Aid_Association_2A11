#ifndef TRESORIE_H
#define TRESORIE_H
//
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPainter>
#include <QChart>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

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
    QChart* chart_pie();

private:

    int num_op;

    QString type,descriptive;
    float montant;

    QDate date_ajout;

};
#endif // TRESORIE_H
