#ifndef FENETREAJOUT_H
#define FENETREAJOUT_H

#include <QtWidgets>
#include <vector>
#include "attribut.h"

class FenetreAjout : public QDialog
{
    Q_OBJECT

    public:
        FenetreAjout(QWidget *parent, QWidget *grandparent); // Constructeur

    signals:
        void cliquAjouter(QString ,QString, QString);

    private slots:
        void cliquer();

    private:
        QLineEdit *type;
        QLineEdit *nom;
        QComboBox *methode;
        QPushButton *ajouter;
        QPushButton *annuler;
};

#endif // FENETREAJOUT_H

