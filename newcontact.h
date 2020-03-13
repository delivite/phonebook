#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#include <QDialog>

#include "contacts.h"
#include "person.h"

namespace Ui {
class NewContact;
}



class NewContact : public QDialog
{
    Q_OBJECT

public:
    explicit NewContact(QWidget *parent = nullptr);
    ~NewContact();

private slots:
    void on_save_button_clicked();
    void on_cancel_button_clicked();

private:
    Ui::NewContact *ui;

    Contacts contact;

};

#endif // NEWCONTACT_H
