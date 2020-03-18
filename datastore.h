#ifndef DATASTORE_H
#define DATASTORE_H
#include <QDialog>
#include <map>

#include "person.h"
struct DataStore
{
    static std::map<QString, Person> phonebook;

};

#endif // DATASTORE_H
