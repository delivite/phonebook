#ifndef PERSON_H
#define PERSON_H

#include <QDialog>

struct Person
{
    QString name{};
    long long phone{};
    QString email{};
    QString job{};
    QString meeting{};
    QString remember{};

    Person();
    Person(QString name, long long phone, QString email, QString job, QString meeting, QString remember);
};

#endif // PERSON_H
