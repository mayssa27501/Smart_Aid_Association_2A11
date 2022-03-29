#include "historique.h"

historique::historique()
{

}

void historique::saveajouter()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"un ajout effectuer"<<endl;
file.close();
     }
}
void historique::savemodifier()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une modification effectuer"<<endl;
file.close();
     }
}
void historique::savesupp()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une suppression effectuer"<<endl;
file.close();
     }
}
void historique::saveang()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une traduction en anglais effectuer"<<endl;
file.close();
     }
}
void historique::savefr()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une traduction en français effectuer"<<endl;
file.close();
     }
}
void historique::saveimp()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une impression effectuer"<<endl;
file.close();
     }
}
void historique::savecher()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"une recherche effectuer"<<endl;
file.close();
     }
}
void historique::savetri1()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"un tri par id effectuer"<<endl;
file.close();
     }
}
void historique::savetri2()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"un tri par nom effectuer"<<endl;
file.close();
     }
}
void historique::savetri3()
{
    QFile file ("C:/Atelier_Connexion/historique.txt");
     if (file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
     {
         // code si l'ouverture fonctionne
     QTextStream out(&file);


     out<<"un tri par date effectuer"<<endl;
file.close();
     }
}
