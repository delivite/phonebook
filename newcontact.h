#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#include <QDialog>

#include "contacts.h"

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
    std::string name{};
    std::string email{"john@doe.com"};
    long long phone{};
    Contacts *cache;

};

#endif // NEWCONTACT_H
