#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#include <QDialog>

namespace Ui {
class NewContact;
}



class NewContact : public QDialog
{
    Q_OBJECT

public:
    explicit NewContact(QWidget *parent = 0 /*nullptr*/);
    ~NewContact();

private slots:
    void on_save_button_clicked();
    void on_cancel_button_clicked();

signals:
    void send(QString name, long long phone, QString email);

private:
    Ui::NewContact *ui;
};
QString to_camel_case(const QString &);
#endif // NEWCONTACT_H
