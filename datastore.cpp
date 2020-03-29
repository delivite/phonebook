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

QString DataStore::get_name(QString name)
{
    auto it = phonebook.find(name);
    return it->first;
}

bool DataStore::contains(QString name)
{
    auto it = phonebook.find(name);
    return (it!= phonebook.end())?true:false;
}

void DataStore::set_remember(QString name, QString text)
{
    auto it = phonebook.find(name);
    it->second.remember = text;
}

QString DataStore::get_all_emails()
{
    QString all_emails;
    for(auto it : phonebook){
        all_emails += it.second.email + ";";
    }
    return all_emails;
}
