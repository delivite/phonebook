#ifndef PERSON_H
#define PERSON_H

#include <QDialog>

struct Person
{
    QString name{};
    long long phone{};
    QString email{};

    Person()
    {

    }

    Person(QString name, long long phone, QString email): name(name), phone(phone), email(email)
    {

    }
};

#endif // PERSON_H