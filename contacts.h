#ifndef CONTACTS_H
#define CONTACTS_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <person.h>
#include "datastore.h"
#include "newcontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Contacts; }
QT_END_NAMESPACE


class Contacts : public QMainWindow
{
    Q_OBJECT

public:
    Contacts(QWidget *parent = nullptr);
    Contacts (const Contacts &e)=delete;
    Contacts operator=(const Contacts &e) = delete;
    ~Contacts();
    void edit(std::string);        
    void remove_name(std::string name);
    bool contains(QString key);
    long long get_phone(QString name);
    QString get_email(QString name);
    QListWidgetItem* current_name()const;

signals:
    //void list(QString name);
public slots:
    void save_data(QString name, long long phone, QString email);

private slots:
    void on_new_contact_clicked();

    void on_exit_app_clicked();

    void on_delete_contact_clicked();

    void on_edit_contact_clicked();

    void on_listWidget_itemSelectionChanged();
    //void list_it(QString name);

private:
    Ui::Contacts *ui;
    DataStore store;
    //NewContact con;
    void save_to_disk();
    void load_data();
    void list_contacts();
    void remove_current();
    void list_insert (QString key);


};
#endif // CONTACTS_H
void to_camel_case(std::string &word);

