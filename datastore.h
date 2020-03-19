#ifndef DATASTORE_H
#define DATASTORE_H
#include <QDialog>
#include <map>

#include "person.h"
struct DataStore
{
    static std::map<QString, Person> phonebook;
    QString get_email(QString name);
    long long get_phone(QString name);
    bool contains(QString name);

};

#endif // DATASTORE_H
