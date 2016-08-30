#include "fenetreajout.h"

FenetreAjout::FenetreAjout(QWidget *parent = 0, QWidget *grandparent = 0) : QDialog(grandparent)
{
    // création du fomulaire
    type = new QLineEdit;
    type->setText("int");
    nom = new QLineEdit;
    nom->setText("nouveau");
    methode = new QComboBox;
    methode->addItem("Rien");
    methode->addItem("Get");
    methode->addItem("Set");
    methode->addItem("Get/Set");

    QFormLayout *ajoutLayout = new QFormLayout;
    ajoutLayout->addRow("Type :", type);
    ajoutLayout->addRow("Nom :", nom);
    ajoutLayout->addRow("Methode", methode);

    QGroupBox *groupAjout = new QGroupBox("Ajouter un attribut");
    groupAjout->setLayout(ajoutLayout);

    // Création des boutons
    annuler = new QPushButton("annuler");
    ajouter = new QPushButton("Ajouter");

    QHBoxLayout *layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(ajouter);

    // Création de la fenêtre entière
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(groupAjout);
    layoutPrincipal->addLayout(layoutBoutons);

    setLayout(layoutPrincipal);

    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()), this , SLOT(cliquer()));
    QObject::connect(ajouter, SIGNAL(clicked()), this , SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()), parent, SLOT(close()));
    QObject::connect(this, SIGNAL(cliquAjouter(QString, QString, QString)), grandparent, SLOT(ajouterAttribut(QString, QString, QString)));
}

void FenetreAjout::cliquer()
{
    emit cliquAjouter(type->text(),nom->text(),methode->currentText());
}
