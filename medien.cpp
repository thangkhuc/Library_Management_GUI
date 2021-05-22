#include "medien.h"

int Medien :: _id = 1;
Medien :: Medien()
{
    this->ID = _id;
    _id++;
    borrowed = false;
    entleiher = nullptr;
}

Medien :: Medien(string autor, string titel, int ID, bool borrowed, Kunde* entleiher) : autor(autor), titel(titel), ID(ID), borrowed(borrowed), entleiher(entleiher)
{
    int a = getStaticID();
    while (a != ID + 1) {
        a++;
        setStaticID(a);
    }
}

Medien :: Medien(string autor, string titel, bool borrowed, Kunde* entleiher) : autor(autor), titel(titel), borrowed(borrowed), entleiher(entleiher)
{
    this->ID = _id;
    _id++;
}

Medien :: Medien(string autor, string titel, int ID) : autor(autor), titel(titel), ID(ID)
{
    int a = getStaticID();
    while (a != ID + 1) {
        a++;
        setStaticID(a);
    }
    borrowed = false;
    entleiher = nullptr;
}

int Medien :: getID() const {return this->ID;}

string Medien :: getAutor() const {return this->autor;}

string Medien :: getTitel() const {return this->titel;}

Kunde* Medien :: getEntleiher() const {return this->entleiher;}

bool Medien :: getBorrowed() const {return this->borrowed;}

int Medien :: getStaticID() const {return this->_id;}

void Medien :: setID(int id) {this->ID= id;}

void Medien :: setAutor(string autor) {this->autor = autor;}

void Medien :: setTitel(string titel) {this->titel = titel;}

void Medien :: setStaticID(int _id) {this->_id = _id;}

void Medien :: setEntleiher(Kunde* entleiher) {this->entleiher = entleiher;}

void Medien :: setBorrowed(bool borrowed) {this->borrowed = borrowed;}
