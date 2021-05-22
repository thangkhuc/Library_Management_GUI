#ifndef CD_H
#define CD_H
#include "medien.h"

class CD : public Medien
{
private:
    string spielDauer;
public:
    CD(string, string, string, int, bool, Kunde*); // Allegemein Konstruktur mit ID Attribute
    CD(string, string, string, bool, Kunde*); // Allgemein Konstruktur ohne ID Attribute
    CD(string, string, string, int); // Allgemein Konstruktur ohne borrowed, Entleiher Attribute

    string getSpielDauer() const;

    void setSpielDauer(string);
};

#endif // CD_H
