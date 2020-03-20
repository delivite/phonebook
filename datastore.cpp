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

QString DataStore::get_job(QString name)
{
    auto it = phonebook.find(name);
    return it->second.job;
}

QString DataStore::get_meet(QString name)
{
    auto it = phonebook.find(name);
    return it->second.meeting;
}

QString DataStore::get_remember(QString name)
{
    auto it = phonebook.find(name);
    return it->second.remember;
}

bool DataStore::contains(QString name)
{
    auto it = phonebook.find(name);
    return (it!= phonebook.end())?true:false;
}
