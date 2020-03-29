#include "person.h"


Person::Person()
{

}

Person::Person(QString name, long long phone, QString email, QString job, QString meeting, QString remember):
    name(name), phone(phone), email(email)
  , job(job), meeting(meeting), remember(remember)
{

}
