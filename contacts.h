#ifndef CONTACTS_H
#define CONTACTS_H

#include <QMainWindow>

#include "datastore.h"
#include "editcontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Contacts; }
QT_END_NAMESPACE


class Contacts : public QMainWindow
{
    Q_OBJECT

public:
    Contacts(QWidget *parent = nullptr);
    //Contacts (const Contacts &e)=delete;
    //Contacts operator=(const Contacts &e) = delete;
    ~Contacts();

signals:
    void current_contact(QString name);

public slots:
    void save_data(QString name, long long phone, QString email);
    void edit_data(QString name, long long phone, QString email);

private slots:
    void on_new_contact_clicked();

    void on_exit_app_clicked();

    void on_delete_contact_clicked();

    void on_edit_contact_clicked();

    void on_listWidget_itemSelectionChanged();

private:
    Ui::Contacts *ui;
    DataStore store;
    editcontact e;

    void save_to_disk();
    void load_data();
    void list_contacts();
    void remove_current();
    void list_insert (QString key);    

};
#endif // CONTACTS_H


