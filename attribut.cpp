#include "attribut.h"

Attribut::Attribut()
{
    m_type = "int";
    m_nom = "nouvelAttribut";
    m_methode = "getset";
}

void Attribut::setType(QString type)
{
    m_type = type;
}

void Attribut::setNom(QString nom)
{
    m_nom = nom;
}

void Attribut::setMethode(QString methode)
{
    m_methode = methode;
}

QString Attribut::getType()
{
    return m_type;
}

QString Attribut::getNom()
{
    return m_nom;
}

QString Attribut::getMethode()
{
    return m_methode;
}
