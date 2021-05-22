#include "Kunde.h"

unsigned Kunde :: staticKundeID = 1;

Kunde :: Kunde() : vorname(""), nachname(""), kundeId(this->staticKundeID)
{
    staticKundeID++;
}

Kunde :: Kunde(string vorname, string nachname, unsigned id) : vorname(vorname), nachname(nachname)
{
    this->kundeId = id;
    while (id >= this->staticKundeID)
        this->staticKundeID++;
}

Kunde :: Kunde(string vorname, string nachname) : vorname(vorname),
    nachname(nachname), kundeId(staticKundeID) {staticKundeID++;};

string Kunde :: getVorname() const {return this->vorname;}

string Kunde :: getNachname() const {return this->nachname;}

unsigned Kunde :: getKundeID() const {return this->kundeId;}

unsigned Kunde :: getStaticKundenID() const {return this->staticKundeID;}

string Kunde :: getKundeID_String() const
{
    unsigned a = this->kundeId;
    string ID = "";
    if (a < 10)
        ID += (char) a + '0';
    else {
        ID += (char) a / 10 + '0';
        a = a % 10;
        ID += a + '0';
    }
    return ID;
}
