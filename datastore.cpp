#include "datastore.h"


std::map<QString, Person> DataStore::phonebook{};

QString DataStore::get_email(QString name)
{
    auto it = phonebook.find(name);
    return it->second.email;
}

long long DataStore::get_phone(QString name)
{
    auto it = phonebook.find(name);
    return it->second.phone;
}

bool DataStore::contains(QString name)
{
    auto it = phonebook.find(name);
    return (it!= phonebook.end())?true:false;
}
