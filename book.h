#ifndef BOOK_H
#define BOOK_H

#include "medien.h"

class Book : public Medien
{
private:
    int seiteZahl;
public:
    Book(string, string, int, int, bool, Kunde*); // allgemein Konstruktur mit ID Attribute
    Book(string, string, int, bool, Kunde*); // allgemein Konstruktur ohne ID Attribute
    Book(string, string, int, int); // allgemein Konstruktur ohne borrowed, Entleiher Attribute

    int getSeiteZahl() const;

    void setSeiteZahl(int);
};

#endif // BOOK_H
