#ifndef FENETRECODE_H
#define FENETRECODE_H

#include <QtWidgets>

class FenetreCode : public QDialog
{
    public:
        FenetreCode(QString &codeH, QString &codeC, QWidget *parent); // Constructeur

    private:
        QTextEdit *codeHGenere;
        QTextEdit *codeCGenere;
        QPushButton *fermer;
        QPushButton *sauver;
};



#endif // FENETRECODE_H

