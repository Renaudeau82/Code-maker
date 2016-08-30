#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QtWidgets>
#include <vector>
#include "attribut.h"
#include "fenetreajout.h"

class FenetrePrincipale : public QWidget
{
    Q_OBJECT // Pour définir ses propres Slots

    public:
        FenetrePrincipale(); // Constructeur
        QString genererH();
        QString genererCpp();

    private slots:
        void genererCode();
        void afficherAttributs();
        void creerFicher();
        void ajouterAttribut(QString type, QString nom, QString methode);

    private:
        QLineEdit *nom;
        QLineEdit *classeMere;
        QLineEdit *nameSpace;
        QCheckBox *protections;
        QCheckBox *genererConstructeur;
        QCheckBox *genererDestructeur;
        QPushButton *voirAttributs;
        QGroupBox *groupCommentaires;
        QLineEdit *auteur;
        QDateEdit *date;
        QTextEdit *role;
        QPushButton *generer;
        QPushButton *quitter;
        std::vector<Attribut> attributs;
        QString codeH;
        QString codeC;
};

#endif // FENETREPRINCIPALE_H

