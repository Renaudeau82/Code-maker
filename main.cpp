#include <QApplication>
#include "fenetreprincipale.h"

// ne sert qu'à lancer l'appli
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
