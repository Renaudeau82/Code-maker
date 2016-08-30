#ifndef FENETREATTRIBUTS_H
#define FENETREATTRIBUTS_H

#include <QtWidgets>
#include <vector>
#include "attribut.h"
#include "fenetreajout.h"

class FenetreAttributs : public QDialog
{
    Q_OBJECT

    public:
        FenetreAttributs(std::vector<Attribut> &attributs, QWidget *parent); // Constructeur

    private slots:
        void fenetreAjout();

    private:
        QWidget *m_parent;
        QTextEdit *textAttribut;
        QPushButton *ajouter;
        QPushButton *fermer;
};

#endif // FENETREATTRIBUTS_H

