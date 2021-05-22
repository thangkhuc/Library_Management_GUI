#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>

#include <vector>
#include <random>
#include <unistd.h>
#include <fstream>

#include "book.h"
#include "cd.h"
#include "anzeige_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Library; }
QT_END_NAMESPACE

enum medienTyp {book, cd};

class Library : public QMainWindow
{
    Q_OBJECT

public:
    Library(QWidget *parent = nullptr);
    ~Library();

    //void print_book(Book*) const;
    //void print_CD(CD*) const;
    medienTyp Medien_Auswahl();
    void meldung(string) const;

private slots:
    void anlegen();
    void anzeigen();
    void bibliothek_laden();
    void bibliothek_speichern() const;
    void loeschen();
    void ausleihen();
    void kunde_hinzufuegen();
    void empfehlen();
    void zurueckgeben();
    void nach_Autor_sortieren();


private:
    Ui::Library *ui;
    QVector<Book*> books;
    QVector<CD*> CDs;
    QVector<Kunde*> kunden;
};
#endif // LIBRARY_H
