#ifndef DATASTORE_H
#define DATASTORE_H
#include <QDialog>
#include <map>

#include "person.h"
struct DataStore
{
    static std::map<QString, Person> phonebook;
public:
    QString get_name(QString name);
    QString get_email(QString name);
    long long get_phone(QString name);
    QString get_job(QString name);
    QString get_meet(QString name);
    QString get_remember(QString name);
    bool contains(QString name);
    void set_remember(QString name, QString text);
    QString get_all_emails();

};

#endif // DATASTORE_H
