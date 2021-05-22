#include "cd.h"

CD :: CD(string autor, string titel, string spielDauer, int ID, bool borrowed, Kunde* entleiher) : Medien(autor, titel, ID, borrowed, entleiher), spielDauer(spielDauer) {}

CD :: CD(string autor, string titel, string spielDauer, bool borrowed, Kunde* entleiher) : Medien(autor, titel, borrowed, entleiher), spielDauer(spielDauer) {}

CD :: CD(string autor, string titel, string spielDauer, int ID) : Medien(autor, titel, ID), spielDauer(spielDauer) {}

string CD :: getSpielDauer() const {return this->spielDauer;}

void CD :: setSpielDauer (string spielDauer) {this->spielDauer = spielDauer;}
