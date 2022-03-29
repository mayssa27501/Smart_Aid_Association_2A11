#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

class historique
{
    QString tmp;
public:
    historique();
    void saveajouter();
    void savesupp();
    void savemodifier();
    void saveang();
    void savefr();
    void saveimp();
    void savecher();
    void savetri1();
    void savetri2();
    void savetri3();

};

#endif // HISTORIQUE_H
