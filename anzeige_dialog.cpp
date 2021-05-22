#include "anzeige_dialog.h"
#include "ui_anzeige_dialog.h"

Anzeige_Dialog::Anzeige_Dialog(QVector<Book*> books, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Anzeige_Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Buecher");
    ui->table->setRowCount(books.size());


    // das 3. Colomm modifizieren
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::fromStdString("Seiteanzahl"));
    ui->table->setHorizontalHeaderItem(3, item);

    for (int row = 0; row < books.size(); row++ ) {
        for (int col = 0; col < 6 ; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (col == 0) {
                item->setText(QString::number(books[row]->getID()));
                ui->table->setItem(row, col, item);
            }
            if (col == 1) {
                item->setText(QString::fromStdString(books[row]->getTitel()));
                ui->table->setItem(row, col, item);
            }
            if (col == 2) {
                item->setText(QString::fromStdString(books[row]->getAutor()));
                ui->table->setItem(row, col, item);
            }
            if (col == 3) {
                item->setText(QString::number(books[row]->getSeiteZahl()));
                ui->table->setItem(row, col, item);
            }
            if (col == 4) {
                if (books[row]->getBorrowed()) {
                    item->setText(QString::fromStdString("true"));
                    ui->table->setItem(row, col, item);
                }
                else {
                    item->setText(QString::fromStdString("false"));
                    ui->table->setItem(row, col, item);
                }
            }
            if (col == 5) {
                if (books[row]->getBorrowed()) {
                    item->setText(QString::fromStdString(books[row]->getEntleiher()->getVorname() + books[row]->getEntleiher()->getNachname()));
                    ui->table->setItem(row, col, item);
                }
            }
        }
    }

    connect(ui->cancel_button, &QPushButton::clicked, this, &Anzeige_Dialog::close);
}

Anzeige_Dialog::Anzeige_Dialog(QVector<CD*> cds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Anzeige_Dialog)
{
    ui->setupUi(this);
    ui->label->setText("CD");
    ui->table->setRowCount(cds.size());


    // das 3. Colomm modifizieren
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::fromStdString("Spieldauer"));
    ui->table->setHorizontalHeaderItem(3, item);

    for (int row = 0; row < cds.size(); row++ ) {
        for (int col = 0; col < 6 ; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (col == 0) {
                item->setText(QString::number(cds[row]->getID()));
                ui->table->setItem(row, col, item);
            }
            if (col == 1) {
                item->setText(QString::fromStdString(cds[row]->getTitel()));
                ui->table->setItem(row, col, item);
            }
            if (col == 2) {
                item->setText(QString::fromStdString(cds[row]->getAutor()));
                ui->table->setItem(row, col, item);
            }
            if (col == 3) {
                item->setText(QString::fromStdString(cds[row]->getSpielDauer()));
                ui->table->setItem(row, col, item);
            }
            if (col == 4) {
                if (cds[row]->getBorrowed()) {
                    item->setText(QString::fromStdString("true"));
                    ui->table->setItem(row, col, item);
                }
                else {
                    item->setText(QString::fromStdString("false"));
                    ui->table->setItem(row, col, item);
                }
            }
            if (col == 5) {
                if (cds[row]->getBorrowed()) {
                    item->setText(QString::fromStdString(cds[row]->getEntleiher()->getVorname() + cds[row]->getEntleiher()->getNachname()));
                    ui->table->setItem(row, col, item);
                }
            }
        }
    }
    connect(ui->cancel_button, &QPushButton::clicked, this, &Anzeige_Dialog::close);
}

Anzeige_Dialog::Anzeige_Dialog(Book* book, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Anzeige_Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Empfohlenes Buch");
    ui->table->setRowCount(1);


    // das 3. Colomm modifizieren
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::fromStdString("Seiteanzahl"));
    ui->table->setHorizontalHeaderItem(3, item);

        for (int col = 0; col < 6 ; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (col == 0) {
                item->setText(QString::number(book->getID()));
                ui->table->setItem(0, col, item);
            }
            if (col == 1) {
                item->setText(QString::fromStdString(book->getTitel()));
                ui->table->setItem(0, col, item);
            }
            if (col == 2) {
                item->setText(QString::fromStdString(book->getAutor()));
                ui->table->setItem(0, col, item);
            }
            if (col == 3) {
                item->setText(QString::number(book->getSeiteZahl()));
                ui->table->setItem(0, col, item);
            }
            if (col == 4) {
                if (book->getBorrowed()) {
                    item->setText(QString::fromStdString("true"));
                    ui->table->setItem(0, col, item);
                }
                else {
                    item->setText(QString::fromStdString("false"));
                    ui->table->setItem(0, col, item);
                }
            }
            if (col == 5) {
                if (book->getBorrowed()) {
                    item->setText(QString::fromStdString(book->getEntleiher()->getVorname() + book->getEntleiher()->getNachname()));
                    ui->table->setItem(0, col, item);
                }
            }
        }

    connect(ui->cancel_button, &QPushButton::clicked, this, &Anzeige_Dialog::close);
}

Anzeige_Dialog::Anzeige_Dialog(CD* cd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Anzeige_Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Empfohlenes CD");
    ui->table->setRowCount(1);


    // das 3. Colomm modifizieren
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::fromStdString("Spieldauer"));
    ui->table->setHorizontalHeaderItem(3, item);

        for (int col = 0; col < 6 ; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (col == 0) {
                item->setText(QString::number(cd->getID()));
                ui->table->setItem(0, col, item);
            }
            if (col == 1) {
                item->setText(QString::fromStdString(cd->getTitel()));
                ui->table->setItem(0, col, item);
            }
            if (col == 2) {
                item->setText(QString::fromStdString(cd->getAutor()));
                ui->table->setItem(0, col, item);
            }
            if (col == 3) {
                item->setText(QString::fromStdString(cd->getSpielDauer()));
                ui->table->setItem(0, col, item);
            }
            if (col == 4) {
                if (cd->getBorrowed()) {
                    item->setText(QString::fromStdString("true"));
                    ui->table->setItem(0, col, item);
                }
                else {
                    item->setText(QString::fromStdString("false"));
                    ui->table->setItem(0, col, item);
                }
            }
            if (col == 5) {
                if (cd->getBorrowed()) {
                    item->setText(QString::fromStdString(cd->getEntleiher()->getVorname() + cd->getEntleiher()->getNachname()));
                    ui->table->setItem(0, col, item);
                }
            }
        }

    connect(ui->cancel_button, &QPushButton::clicked, this, &Anzeige_Dialog::close);
}

Anzeige_Dialog::~Anzeige_Dialog()
{
    delete ui;
}
