#include "library.h"
#include "ui_library.h"

bool ok = true;

Library::Library(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Library)
{
    ui->setupUi(this);
    connect(ui->anlegen_button, &QPushButton::clicked, this, &Library::anlegen);
    connect(ui->anzeigen_button, &QPushButton::clicked, this, &Library::anzeigen);
    connect(ui->verlassen_button, &QPushButton::clicked, this, &Library::close);
    connect(ui->laden_button, &QPushButton::clicked, this, &Library::bibliothek_laden);
    connect(ui->speichern_button, &QPushButton::clicked, this, &Library::bibliothek_speichern);
    connect(ui->loeschen_button, &QPushButton::clicked, this, &Library::loeschen);
    connect(ui->ausleihen_button, &QPushButton::clicked, this, &Library::ausleihen);
    connect(ui->kunde_hinzufuegen_button, &QPushButton::clicked, this, &Library::kunde_hinzufuegen);
    connect(ui->zurueckgeben_button, &QPushButton::clicked, this, &Library::zurueckgeben);
    connect(ui->nach_Autor_sortieren_button, &QPushButton::clicked, this, &Library::nach_Autor_sortieren);
    connect(ui->empfehlen_button, &QPushButton::clicked, this, &Library::empfehlen);
}

Library::~Library()
{
    delete ui;
    for (int i = 0; i < books.size() ;i++ )
        delete books[i];

    for (int i = 0; i < CDs.size() ;i++ )
        delete CDs[i];
}

medienTyp Library::Medien_Auswahl()
{
    QStringList items;
    items << "Book" << "CD";
    QString item = QInputDialog::getItem(this, "Medien auswählen", "Medien auswaehlen", items, 0, false, &ok);

    if (item == "Book") return book;
    else return cd;
}

void Library::anlegen()
{
    QString autor, titel, spielDauer;
    int seiteZahl;
    medienTyp medienAuswahl = Medien_Auswahl();

    if (ok)
        titel = QInputDialog::getText(this, "Titel", "Titel", QLineEdit::Normal, "", &ok);
    if (ok)
        autor = QInputDialog::getText(this, "Autor", "Autor", QLineEdit::Normal, "", &ok);
    if (ok) {
        if (medienAuswahl == book) {
            seiteZahl = QInputDialog::getInt(this, "Seiteanzahl", "Seiteanzahl",0,0,100000, 1, &ok);

            if (ok && !titel.isEmpty() && !autor.isEmpty()) {
                Book* newBook = new Book(titel.toStdString(), autor.toStdString(), seiteZahl, false, nullptr);
                books.push_back(newBook);
            }
        }
        else {
            spielDauer = QInputDialog::getText(this, "Spieldauer", "Spieldauer", QLineEdit::Normal, "", &ok);

            if (ok && !titel.isEmpty() && !autor.isEmpty() && !spielDauer.isEmpty()) {
                CD* newCD= new CD(titel.toStdString(), autor.toStdString(), spielDauer.toStdString(), false, nullptr);
                CDs.push_back(newCD);
            }
        }
    }
}

void Library :: loeschen()
{
    int ID;
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    if (auswahl == book) {
        ID = QInputDialog::getInt(this,"ID", "ID", 0, 0, books.size() + CDs.size(), 1, &ok);

        if (!ok) return;

        for (int i = 0; i < books.size(); i++) {
            if (ID == books.at(i)->getID()) {
                if (books.at(i)->getBorrowed())
                    meldung("Das Buch wurde schon ausgeliehen");
                else {
                    for (int j = i + 1; j < books.size() ; j++) {
                        Book* temp = books[j - 1];
                        books[j - 1] = books[j];
                        books[j] = temp;
                    }
                    delete books.at(books.size() - 1);
                    books.pop_back();

                    meldung("Das Buch ist geloescht");
                }
                break;
            }
        }
    }
    else {
        ID = QInputDialog::getInt(this,"ID", "ID", 0, 0, books.size() + CDs.size(), 1, &ok);

        if (!ok) return;

        for (int i = 0; i < CDs.size(); i++) {
            if (ID == CDs.at(i)->getID()) {
                if (CDs.at(i)->getBorrowed())
                    meldung("Das CD wurde schon ausgeliehen");
                else {
                    for (int j = i + 1; j < CDs.size() ; j++) {
                        CD* temp = CDs[j - 1];
                        CDs[j - 1] = CDs[j];
                        CDs[j] = temp;
                    }
                    delete CDs.at(CDs.size() - 1);
                    CDs.pop_back();

                    meldung("Das CD ist geloescht");
                }
                break;
            }
        }
    }
}

void Library :: anzeigen()
{
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    if (auswahl == cd) {
        Anzeige_Dialog* anzeige = new Anzeige_Dialog(this->CDs);
        anzeige->show();
    }
    else {
        Anzeige_Dialog* anzeige = new Anzeige_Dialog(this->books);
        anzeige->show();
    }
}

void Library :: bibliothek_laden()
{
    ifstream savedFile("medien.txt");
    if (savedFile.is_open()) {
        // loeschen alle vorhandene Buecher
        while (books.size() != 0) {
            books[0]->setStaticID(1);
            delete books.at(books.size() - 1);
            books.pop_back();
        }

        while (CDs.size() != 0) {
            CDs[0]->setStaticID(1);
            delete CDs.at(CDs.size() - 1);
            CDs.pop_back();
        }

        string line, auswahl;
        getline(savedFile, auswahl);

        // load saved file
        while (getline(savedFile, line)){
            if (line != "CDs" && auswahl == "Buecher") {
                string autor = "", titel = "", vorname = "", nachname = "";
                int ID = 0, kundeID = 0, seiteZahl = 0, counter = 0;

                unsigned int i = 0;
                while (i != line.length()) {
                    if (line.at(i) == ';'){
                        i++;
                        counter++;
                    }
                    else if (counter == 0) { // get Book ID
                        ID = ID * 10 + line.at(i) - '0';
                        i++;
                    }
                    else if (counter == 1) { // get Name des Autors
                        autor = autor + line.at(i);
                        i++;
                    }
                    else if (counter == 2) { // get Name des Mediens
                        titel = titel + line.at(i);
                        i++;
                    }
                    else if (counter == 3) { // get Seite Anzahl
                        seiteZahl = seiteZahl * 10 + line.at(i) - '0';
                        i++;
                    }
                    else if (counter == 4) { // get kunden ID
                        kundeID = kundeID * 10 + line.at(i) - '0';
                        i++;
                    }
                    else if (counter == 5) { // get Vorname des Kundes
                        vorname = vorname + line.at(i);
                        i++;
                    }
                    else if (counter == 6) { // get Nachname des Kundes
                        nachname = nachname + line.at(i);
                        i++;
                    }
                }

                Book* book = new Book(autor, titel, seiteZahl, ID);

                //fuegt den gespeicherten Kunden hinzu, wenn er sich noch nicht in kunden vector befindet
                bool a = false;
                if (counter > 3) {
                    for (int i = 0; i < kunden.size() ;i++ ) {
                        if (kundeID == (int) kunden[i]->getKundeID()) {
                            book->setEntleiher(kunden[i]);
                            book->setBorrowed(true);
                            a = true;
                        }
                    }
                    if (a == false) {
                        Kunde* kunde = new Kunde(vorname, nachname, kundeID);
                        this->kunden.push_back(kunde);
                        book->setEntleiher(kunde);
                        book->setBorrowed(true);
                    }
                }
                this->books.push_back(book);
            }
            else if (line == "CDs" || auswahl == "CDs"){
                string autor = "", titel = "", spielDauer = "", vorname = "", nachname = "";
                int ID = 0, kundeID = 0, exponent = 0, counter = 0;
                auswahl = "CDs";

                if (line == "CDs")
                    getline(savedFile, line);

                unsigned int i = 0;
                while (i != line.length()) {
                    if (line.at(i) == ';'){
                        exponent = 0;
                        i++;
                        counter++;
                    }
                    else if (counter == 0) { // Get CD ID
                            ID = ID * pow(10, exponent) + line.at(i) - '0';
                            exponent++;
                            i++;
                    }
                    if (counter == 1) { // Get Name des Autors
                        autor = autor + line.at(i);
                        i++;
                    }
                    else if (counter == 2) { // Get Name des Mediens
                        titel = titel + line.at(i);
                        i++;
                    }
                    else if (counter == 3) { // Get Spieldauer
                        spielDauer = spielDauer + line.at(i);
                        i++;
                    }
                    else if (counter == 4) { // Get Kunde ID
                            kundeID = kundeID * 10 + line.at(i) - '0';
                            i++;
                    }
                    else if (counter == 5) { // Get Vorname des Kundes
                        vorname = vorname + line.at(i);
                        i++;
                    }
                    else if (counter == 6) { // Get Nachname des Kundes
                        nachname = nachname + line.at(i);
                        i++;
                    }
                }

                CD* cd = new CD(autor, titel, spielDauer, ID);
                //fuegt den gespeicherten Kunden hinzu, wenn er sich noch nicht in kunden vector befindet
                bool a = false;
                if (counter > 3) {
                    for (int i = 0; i < kunden.size() ;i++ ) {
                        if (kundeID == (int) kunden[i]->getKundeID()) {
                            cd->setEntleiher(kunden[i]);
                            cd->setBorrowed(true);
                            a = true;
                        }
                    }
                    if (a == false) {
                        Kunde* kunde = new Kunde(vorname, nachname, kundeID);
                        this->kunden.push_back(kunde);
                        cd->setEntleiher(kunde);
                        cd->setBorrowed(true);
                    }
                }
                this->CDs.push_back(cd);
            }
        }

        meldung("Die Bibliothek ist erfolgreich geladet");
    }
    else
        meldung("Saved File ist nicht gefunden");
}

void Library :: bibliothek_speichern() const
{
    ofstream savedFile("medien.txt");
    if (savedFile.is_open()) {
        savedFile << "Buecher\n";
        for (int i = 0; i < books.size(); i++) {
            savedFile << books.at(i)->getID() << ";";
            savedFile << books.at(i)->getAutor() << ";";
            savedFile << books.at(i)->getTitel() << ";";
            if (!books.at(i)->getBorrowed())
                savedFile << books.at(i)->getSeiteZahl() << "\n";
            else {
                savedFile << books.at(i)->getSeiteZahl() << ";";
                savedFile << books.at(i)->getEntleiher()->getKundeID() << ";";
                savedFile << books.at(i)->getEntleiher()->getVorname() << ";";
                savedFile << books.at(i)->getEntleiher()->getNachname() << "\n";
            }
        }
        savedFile << "CDs\n";
        for (int i = 0; i < CDs.size(); i++) {
            savedFile << CDs.at(i)->getID() << ";";
            savedFile << CDs.at(i)->getAutor() << ";";
            savedFile << CDs.at(i)->getTitel() << ";";
            if (!CDs.at(i)->getBorrowed())
                savedFile << CDs.at(i)->getSpielDauer() << "\n";
            else {
                savedFile << CDs.at(i)->getSpielDauer() << ";";
                savedFile << CDs.at(i)->getEntleiher()->getKundeID() << ";";
                savedFile << CDs.at(i)->getEntleiher()->getVorname() << ";";
                savedFile << CDs.at(i)->getEntleiher()->getNachname() << "\n";
            }
        }

        meldung("Die Bibliothek ist erfolgreich gespeichert");
    }
    else
        meldung("Saved File ist nicht gefunden");
}

void Library :: ausleihen()
{
    unsigned kundeID, medienID;
    unsigned kundeIndex;
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    //check kundeID
    kundeID = QInputDialog::getInt(this, "Kunde ID", "Kunde ID", 0, 0, kunden.size(), 1, &ok);

    if (ok) {
        //find Kunde
        for (int i = 0; i < this->kunden.size(); i++) {
            if (kundeID == this->kunden[i]->getKundeID())
                kundeIndex = i;
        }
    }

    if (auswahl == book) {
        //check bookID

        medienID = QInputDialog::getInt(this, "Book ID", "Book ID", 0, 0, this->books.size() + this->CDs.size(), 1, &ok);

        if (!ok) return;

        for (int i = 0; i < books.size(); i++) {
            if (medienID == (unsigned) books.at(i)->getID()) {
                if (books.at(i)->getBorrowed())
                    meldung("Das Buch wurde schon ausgeliehen");
                else {
                    books.at(i)->setBorrowed(true);
                    books.at(i)->setEntleiher(this->kunden[kundeIndex]);
                }
                break;
            }
            else if (i == books.size() - 1)
                meldung("Es gibt kein Buch mit diesem ID");
        }
    }
    else {
        medienID = QInputDialog::getInt(this, "Book ID", "Book ID", 0, 0, this->books.size() + this->CDs.size(), 1, &ok);

        if (!ok) return;

        for (int i = 0; i < CDs.size(); i++) {
            if (medienID == (unsigned) CDs.at(i)->getID()) {
                if (CDs.at(i)->getBorrowed())
                    meldung("Das Buch wurde schon ausgeliehen");
                else {
                    CDs.at(i)->setBorrowed(true);
                    CDs.at(i)->setEntleiher(this->kunden[kundeIndex]);
                }
                break;
            }
            else if (i == books.size() - 1)
                meldung("Es gibt kein CDmit diesem ID");
        }
    }
}

void Library :: kunde_hinzufuegen()
{
    QString vorname, nachname;

    vorname = QInputDialog::getText(this, "Vorname", "Vorname", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    nachname = QInputDialog::getText(this, "Vorname", "Nachname", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    Kunde* newKunde = new Kunde(vorname.toStdString(), nachname.toStdString());
    this->kunden.push_back(newKunde);
}

void Library :: empfehlen()
{
    QString autor;
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    autor = QInputDialog::getText(this, "Name des Autors", "Name des Autors", QLineEdit::Normal, "", &ok);

    if (!ok) return;

    if (auswahl == book) {
        vector<Book*> p; // speichern alle Buecher des Autors

        for (int i = 0; i < books.size() ; i++) {
            if (autor.toStdString() == books.at(i)->getAutor())
                p.push_back(books.at(i));
        }

        if (p.size() > 0) {
            int random;
            do {
                random = rand() % p.size();

                if (p.size() == 1 && p[0]->getBorrowed() == true) {
                    meldung("Kein Buch dieses Autors ist verfuegbar.");
                    break;
                }
                else if(p.at(random)->getBorrowed()) {
                    continue;
                }
                Anzeige_Dialog* anzeige = new Anzeige_Dialog(p.at(random));
                anzeige->show();
                break;
            } while (true);
        }
        else {
            int random;
            meldung("Kein Buch dieses Autors ist verfuegbar.");
            do {
                random = rand() % books.size();
                if (books.at(random)->getBorrowed()) {
                continue;
                }
                Anzeige_Dialog* anzeige = new Anzeige_Dialog(books.at(random));
                anzeige->show();
                break;
            } while (true);
        }
    }
    else {
        system("cls");
        vector<CD*> p; // speichern alle CD des Autors

        for (int i = 0; i < CDs.size() ; i++) {
            if (autor == QString::fromStdString(CDs.at(i)->getAutor()))
                p.push_back(CDs.at(i));
        }

        if (p.size() > 0) {
            int random;
            do {
                random = rand() % p.size();

                if (p.size() == 1 && p[0]->getBorrowed() == true) {
                    meldung("Kein CD dieses Autors ist verfuegbar.");
                    break;
                }
                else if(p.at(random)->getBorrowed()) {
                    continue;
                }
                Anzeige_Dialog* anzeige = new Anzeige_Dialog(p.at(random));
                anzeige->show();
                break;
            } while (true);
        }
        else {
            int random;
            meldung("Kein CD dieses Autors ist verfuegbar.");
            do {
                random = rand() % CDs.size();
                if (CDs.at(random)->getBorrowed()) {
                continue;
                }
                Anzeige_Dialog* anzeige = new Anzeige_Dialog(CDs.at(random));
                anzeige->show();
                break;
            } while (true);
        }
    }
}

void Library :: zurueckgeben()
{
    int ID;
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    if (auswahl == book) {
        ID = QInputDialog::getInt(this, "BookID", "BookID", 0, 0, books[books.size() - 1]->getID(), 1, &ok);
        if (!ok) return;

        for (int i = 0; i < books.size(); i++) {
            if (ID == books.at(i)->getID()) {
                books.at(i)->setBorrowed(false);
                books.at(i)->setEntleiher(nullptr);
                meldung("erfolgreich");
                break;
            }
            else if (i == books.size() - 1)
                meldung("Es gibt kein Buch mit diesem ID");
        }
    }
    else {
        ID = QInputDialog::getInt(this, "CD ID", "CD ID", 0, 0, CDs[CDs.size() - 1]->getID(), 1, &ok);
        if (!ok) return;

        for (int i = 0; i < CDs.size(); i++) {
            if (ID == CDs.at(i)->getID()) {
                CDs.at(i)->setBorrowed(false);
                CDs.at(i)->setEntleiher(nullptr);
                meldung("erfolgreich");
                break;
            }
            else if (i == books.size() - 1)
                meldung("Es gibt kein CD mit diesem ID");
        }
    }
}

void Library :: nach_Autor_sortieren()
{
    medienTyp auswahl = Medien_Auswahl();

    if (!ok) return;

    if (auswahl == book) {
        QVector<Book*> book;
        for (int i = 0; i < books.size() ; i++)
            book.push_back(books[i]);

        for (int i = 0; i < book.size(); i++) {
            for (int j = i + 1; j < book.size(); j++) {
                if (book[i]->getAutor() > book[j]->getAutor()) {
                    Book* temp = book[i];
                    book[i] = book[j];
                    book[j] = temp;
                }
            }
        }

        Anzeige_Dialog* anzeige = new Anzeige_Dialog(book);
        anzeige->show();
    }
    else {
        QVector<CD*> cd;
        for (int i = 0; i < CDs.size() ; i++)
            cd.push_back(CDs[i]);

        for (int i = 0; i < cd.size(); i++) {
            for (int j = i + 1; j < cd.size(); j++) {
                if (cd[i]->getAutor() > cd[j]->getAutor()) {
                    CD* temp = cd[i];
                    cd[i] = cd[j];
                    cd[j] = temp;
                }
            }
        }

        Anzeige_Dialog* anzeige = new Anzeige_Dialog(cd);
        anzeige->show();
    }
}

void Library :: meldung(string text) const
{
    QMessageBox* meldung = new QMessageBox();
    meldung->setInformativeText(QString::fromStdString(text));
    meldung->exec();
}
