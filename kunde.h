#ifndef KUNDE_H
#define KUNDE_H
#include <iostream>

using namespace std;
class Kunde
{
private:
    string vorname;
    string nachname;
    unsigned kundeId;
    static unsigned staticKundeID;
public:
    Kunde();
    Kunde(string, string);
    Kunde(string, string, unsigned);

    string getVorname() const;
    string getNachname() const;
    unsigned getKundeID() const;
    string getKundeID_String() const;
    unsigned getStaticKundenID() const;
};


#endif // KUNDE_H
