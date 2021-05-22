#include "book.h"

Book :: Book (string autor, string titel, int seiteZahl, int ID, bool borrowed, Kunde* entleiher) : Medien(autor, titel, ID, borrowed, entleiher), seiteZahl(seiteZahl) {}

Book :: Book (string autor, string titel, int seiteZahl, bool borrowed, Kunde* entleiher) : Medien(autor, titel, borrowed, entleiher), seiteZahl(seiteZahl) {}

Book :: Book (string autor, string titel, int seiteZahl, int ID) : Medien(autor, titel, ID), seiteZahl(seiteZahl) {}

int Book :: getSeiteZahl() const {return this->seiteZahl;}

void Book :: setSeiteZahl(int seiteZahl) {this->seiteZahl = seiteZahl;}

