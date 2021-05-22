#ifndef ANZEIGE_DIALOG_H
#define ANZEIGE_DIALOG_H

#include <QDialog>
#include "book.h"
#include "cd.h"

namespace Ui {
class Anzeige_Dialog;
}

class Anzeige_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Anzeige_Dialog(QVector<Book*>, QWidget *parent = nullptr);
    explicit Anzeige_Dialog(QVector<CD*>, QWidget *parent = nullptr);
    explicit Anzeige_Dialog(Book*, QWidget *parent = nullptr);
    explicit Anzeige_Dialog(CD*, QWidget *parent = nullptr);
    ~Anzeige_Dialog();

private:
    Ui::Anzeige_Dialog *ui;
};

#endif // ANZEIGE_DIALOG_H
