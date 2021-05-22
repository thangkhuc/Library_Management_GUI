#ifndef MEDIEN_H
#define MEDIEN_H
#include "iostream"
#include "kunde.h"

using namespace std;

class Medien
{
private:
    static int _id;
    string autor;
    string titel;
    int ID;
    bool borrowed;
    Kunde* entleiher;
public:
    Medien();
    Medien(string, string, int, bool, Kunde*); // allgemein Konstruktur mit ID Attribute
    Medien(string, string, bool, Kunde*); // allgemein Konstruktur ohne ID Attribute
    Medien(string, string, int); // allgemein Konstruktur ohne borrowed, Entleiher Attribute

    int getID() const;
    string getAutor() const;
    string getTitel() const;
    bool getBorrowed() const;
    Kunde* getEntleiher() const;
    int getStaticID() const;

    void setStaticID(int);
    void setID(int);
    void setAutor(string);
    void setTitel(string);
    void setEntleiher(Kunde*);
    void setBorrowed(bool);
};

#endif // MEDIEN_H
