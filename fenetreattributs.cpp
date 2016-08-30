#include "fenetreattributs.h"

FenetreAttributs::FenetreAttributs(std::vector<Attribut> &attributs, QWidget *parent = 0) : QDialog(parent)
{
    m_parent = parent;
    textAttribut = new QTextEdit();
    textAttribut->setReadOnly(true);
    textAttribut->setFont(QFont("Courier"));
    textAttribut->setLineWrapMode(QTextEdit::NoWrap);

    // Ecrire les attributs
    QString text;

    for (unsigned int i=0; i < attributs.size(); i++)
    {
        text += attributs[i].getType() + " " + attributs[i].getNom() + " // " +attributs[i].getMethode();
    }
    textAttribut->setPlainText(text);

    // création des boutons
    fermer = new QPushButton("Fermer");
    ajouter = new QPushButton("Ajouter");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(textAttribut);
    layoutPrincipal->addWidget(ajouter);
    layoutPrincipal->addWidget(fermer);

    resize(350, 450);
    setLayout(layoutPrincipal);

    QObject::connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(fenetreAjout()));
}

void FenetreAttributs::fenetreAjout()
{
    // On crée puis affiche la fenêtre d'ajout d'un attribut
    FenetreAjout *fenetreAjout = new FenetreAjout(this, m_parent);
    fenetreAjout->exec();
}
