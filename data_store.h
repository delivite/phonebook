#ifndef DATA_STORE_H
#define DATA_STORE_H

//#include <string>
#include <map>

#include "newcontact.h"

struct data_store
{
    std::map<std::string, long long> phonebook;
    NewContact *person;
    void insert_contact();

};

#endif // DATA_STORE_H
