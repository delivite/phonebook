#include "contacts.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Contacts w;
    w.show();
    return a.exec();
}
