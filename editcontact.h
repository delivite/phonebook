#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QDialog>
#include "contacts.h"

namespace Ui {
class editcontact;
}

class editcontact : public QDialog
{
    Q_OBJECT

public:
    explicit editcontact(QWidget *parent = nullptr);
    ~editcontact();

private slots:
    void on_save_button_clicked();

    void on_cancel_button_clicked();

private:
    void fill_data();
private:
    Ui::editcontact *ui;
    Contacts *contact;
    QString name;


};

#endif // EDITCONTACT_H
