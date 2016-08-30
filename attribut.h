#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <QString>

class Attribut
{
    private:
        QString m_type;
        QString m_nom;
        QString m_methode;

    public:
        Attribut();
        void setType(QString type);
        void setNom(QString nom);
        void setMethode(QString methode);
        QString getType();
        QString getNom();
        QString getMethode();

};

#endif // ATTRIBUT_H

