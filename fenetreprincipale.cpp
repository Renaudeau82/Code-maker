#include "fenetreprincipale.h"
#include "fenetrecode.h"
#include "fenetreattributs.h"
#include "attribut.h"
#include <fstream>
#include <iostream>

FenetrePrincipale::FenetrePrincipale()
{
    /// Création de la fenetre
    /// Etape 1: Création de chaque section
    // Groupe : Définition de la classe
    nom = new QLineEdit;
    classeMere = new QLineEdit;

    QFormLayout *definitionLayout = new QFormLayout;
    definitionLayout->addRow("&Nom :",nom);
    definitionLayout->addRow("Classe &mère :",classeMere);

    QGroupBox *groupDefinition = new QGroupBox("Définition de la classe");
    groupDefinition->setLayout(definitionLayout);

    //Groupe : Options
    protections = new QCheckBox("Protéger le &header contre les inclusions multiples");
    protections->setChecked(true);
    genererConstructeur = new QCheckBox("Générer un &constructeur par défaut");
    genererDestructeur = new QCheckBox("Générer un &destructeur");

    QVBoxLayout *optionsLayout = new QVBoxLayout;
    optionsLayout->addWidget(protections);
    optionsLayout->addWidget(genererConstructeur);
    optionsLayout->addWidget(genererDestructeur);

    QGroupBox *groupOptions = new QGroupBox("Options");
    groupOptions->setLayout(optionsLayout);

    // Groupe : Attributs
    voirAttributs = new QPushButton("Voir Attributs");

    QHBoxLayout *attributsLayout = new QHBoxLayout;
    attributsLayout->setAlignment(Qt::AlignCenter);
    attributsLayout->addWidget(voirAttributs);

    QGroupBox *groupAttributs = new QGroupBox("Attributs");
    groupAttributs->setLayout(attributsLayout);

    // Groupe : Commentaires
    auteur = new QLineEdit;
    date = new QDateEdit;
    date->setDate(QDate::currentDate());
    role = new QTextEdit;

    QFormLayout *commentairesLayout = new QFormLayout;
    commentairesLayout->addRow("&Auteur :", auteur);
    commentairesLayout->addRow("Date de création :", date);
    commentairesLayout->addRow("Explications", role);

    groupCommentaires = new QGroupBox("Ajouter des commentaire");
    groupCommentaires->setCheckable(true);
    groupCommentaires->setChecked(false);
    groupCommentaires->setLayout(commentairesLayout);

    // Boutons du bas
    generer = new QPushButton("&Générer");
    quitter = new QPushButton("&Quitter");

    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    boutonsLayout->setAlignment(Qt::AlignRight);
    boutonsLayout->addWidget(generer);
    boutonsLayout->addWidget(quitter);

    /// Etape 2: Placer les sections dans la fenetre
    // Définition du layout principale
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(groupDefinition);
    layoutPrincipal->addWidget(groupOptions);
    layoutPrincipal->addWidget(groupAttributs);
    layoutPrincipal->addWidget(groupCommentaires);
    layoutPrincipal->addLayout(boutonsLayout);

    setLayout(layoutPrincipal);
    setWindowTitle("Zero Class Generator");
    setWindowIcon(QIcon("icone.png"));
    resize(400, 450);


    /// Etape 3: Connexions des signaux et des slots
    QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(generer, SIGNAL(clicked()), this, SLOT(genererCode()));
    QObject::connect(voirAttributs, SIGNAL(clicked()), this, SLOT(afficherAttributs()));
}

void FenetrePrincipale::genererCode()
{
    // On vérifie que le nom de la classe de soit pas vide
    if (nom->text().isEmpty())
    {
        QMessageBox::critical(this, "Errer", "Veuillez entrer au moins un nom de classe");
        return; // arret de la methode;
    }

    // Si tout va bien, on génére le code .h
    codeH = genererH();

    // Si tout va bien, on génére le code .h
    codeC = genererCpp();

    // On crée puis affiche la fenêtre qui affichera le code généré
    FenetreCode *fenetreCode = new FenetreCode(codeH,codeC,this); // le code est envoyé en paramètre
    fenetreCode->exec();
}

QString FenetrePrincipale::genererH()
{
    QString code;

    // On a demendé à inclure les commentaire
    if (groupCommentaires->isChecked())
    {
        code += "/*\nAuteur : " + auteur->text() + "\n";
        code += "Date de création : " + date->date().toString() + "\n\n";
        code += "Explication : \n" + role->toPlainText() + "\n*/\n\n\n";
    }

    // Les Protection
    if (protections->isChecked())
    {
        code += "#ifndef HEADER_" + nom->text().toUpper() + "\n";
        code += "#define HEADER_" + nom->text().toUpper() + "\n\n\n";
    }

    code += "class " + nom->text();

    // L'heritage
    if (!classeMere->text().isEmpty())
    {
        code += " : public " + classeMere->text();
    }

    code += "\n{\n    private:\n";
    for (unsigned int i=0; i < attributs.size(); i++)
    {
        code += "        " + attributs[i].getType() + " " + attributs[i].getNom() + ";\n ";
    }
    code += "\n\n    protected:\n";
    code += "\n\n    public:\n";
    if (genererConstructeur->isChecked())
    {
        code += "        " + nom->text() + "();\n";
    }
    if (genererDestructeur->isChecked())
    {
        code += "        ~" + nom->text() + "();\n";
    }
    for (unsigned int i=0; i < attributs.size(); i++)
    {
        if(attributs[i].getMethode() == "Get" || attributs[i].getMethode() =="Get/Set")
            code += "        " + attributs[i].getType() + " get" + attributs[i].getNom() + "();\n";
        if(attributs[i].getMethode() == "Set" || attributs[i].getMethode() =="Get/Set")
            code += "        void set" + attributs[i].getNom() + "(" + attributs[i].getType() + " _" + attributs[i].getNom() + ");\n";
    }
    code += "};\n\n";

    if (protections->isChecked())
    {
        code += "#endif\n";
    }

    return code;
}

QString FenetrePrincipale::genererCpp()
{
    QString code;

    // L'include du header
    code += "#include \"" + nom->text() + ".h\"\n\n";

    // le constructeur
    if (genererConstructeur->isChecked())
    {
        code += nom->text() + "::" + nom->text() + "()\n{\n\n}\n\n";
    }
    if (genererDestructeur->isChecked())
    {
        code += nom->text() + "::~" + nom->text() + "()\n{\n\n}\n\n";
    }
    for (unsigned int i=0; i < attributs.size(); i++)
    {
        if(attributs[i].getMethode() == "Get" || attributs[i].getMethode() =="Get/Set")
            code += attributs[i].getType() + " get" + attributs[i].getNom() + "()\n{\n    return " + attributs[i].getNom() + ";\n}\n\n";
        if(attributs[i].getMethode() == "Set" || attributs[i].getMethode() =="Get/Set")
            code += "void set" + attributs[i].getNom() + "(" + attributs[i].getType() + " _" + attributs[i].getNom() + ")\n{\n    " + attributs[i].getNom() + " = _" + attributs[i].getNom() + ";\n}\n\n";
    }

    return code;
}

void FenetrePrincipale::afficherAttributs()
{
    // On crée puis affiche la fenêtre des attributs
    FenetreAttributs *fenetreAttributs = new FenetreAttributs(attributs, this); // les attributs sont envoyés en paramètres
    fenetreAttributs->exec();
}

void FenetrePrincipale::ajouterAttribut(QString type, QString nom, QString methode)
{
    Attribut nouveau;
    nouveau.setType(type);
    nouveau.setNom(nom);
    nouveau.setMethode(methode);
    attributs.push_back(nouveau);
}

void FenetrePrincipale::creerFicher()
{
    QString dossier = QFileDialog::getExistingDirectory(this, "Choisissez un dossier");

    //Déclaration d'un flux permettant d'écrire dans un fichier.
    std::string const fichierH = dossier.toStdString() + "/" + nom->text().toStdString() + ".h";
    std::ofstream monFluxH(fichierH.c_str());
    if(monFluxH)  //On teste si tout est OK
    {
        //Tout est OK, on peut utiliser le fichier
        monFluxH << codeH.toStdString();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la sauvegarde");
    }
    std::cout << fichierH << "\n";

    std::string const fichierC = dossier.toStdString() + "/" + nom->text().toStdString() + ".cpp";
    std::ofstream monFluxC(fichierC.c_str());
    if(monFluxC)  //On teste si tout est OK
    {
        //Tout est OK, on peut utiliser le fichier
        monFluxC << codeC.toStdString();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la sauvegarde");
    }
}
