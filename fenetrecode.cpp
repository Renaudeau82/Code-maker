#include "fenetrecode.h"
#include <fstream>
#include <string>

FenetreCode::FenetreCode(QString &codeH, QString &codeC, QWidget *parent = 0) : QDialog(parent)
{
    // 1 : Créer le QTabWidget
    QTabWidget *onglets = new QTabWidget(this);
    onglets->setGeometry(30, 20, 240, 300);

    // 2 : Créer les pages, en utilisant un widget parent pour contenir chacune des pages
    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget; // Comme un QLabel est aussi un QWidget (il en hérite)

    // 3 : Créer le contenu des pages de widgets
    // Page 1
    codeHGenere = new QTextEdit();
    codeHGenere->setPlainText(codeH);
    codeHGenere->setReadOnly(true);
    codeHGenere->setFont(QFont("Courier"));
    codeHGenere->setLineWrapMode(QTextEdit::NoWrap);
    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(codeHGenere);
    page1->setLayout(vbox1);
    // Page 2
    codeCGenere = new QTextEdit();
    codeCGenere->setPlainText(codeC);
    codeCGenere->setReadOnly(true);
    codeCGenere->setFont(QFont("Courier"));
    codeCGenere->setLineWrapMode(QTextEdit::NoWrap);
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(codeCGenere);
    page2->setLayout(vbox2);

    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(page1, "Code .h");
    onglets->addTab(page2, "Code .cpp");

    fermer = new QPushButton("Fermer");
    sauver = new QPushButton("Sauver");
    QHBoxLayout *LayoutBoutons = new QHBoxLayout;
    LayoutBoutons->addWidget(fermer);
    LayoutBoutons->addWidget(sauver);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(onglets);
    layoutPrincipal->addLayout(LayoutBoutons);

    resize(350, 450);
    setLayout(layoutPrincipal);

    QObject::connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(sauver, SIGNAL(clicked()), parent, SLOT(creerFicher()));
}


