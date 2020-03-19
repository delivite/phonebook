#include <iostream>
#include <QMessageBox>
#include <QDoubleValidator>
#include "newcontact.h"
#include "ui_newcontact.h"

NewContact::NewContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewContact)
{
    ui->setupUi(this);
    ui->phone_edit->setValidator( new QDoubleValidator(this) );
}

NewContact::~NewContact()
{    
    delete ui;
}

void NewContact::on_save_button_clicked()
{
    QString name{};
    long long phone{};
    QString email{};
    if(!(ui->phone_edit->text().isEmpty())){

         if((ui->name_edit->text().isEmpty())){
             /*If name field is empty, use the phone number as the name key*/
             name = ui->phone_edit->text();
         }else{
             name = to_camel_case(ui->name_edit->text());
         }
         phone = ui->phone_edit->text().toLongLong();
         email = ui->email_edit->text();
         emit send(name, phone, email);
         close();

     }else{
        /* Phone field cannot be empty.
         * If it is, prompt the user to input a phone number
        */
         QMessageBox::critical(this,"Can't Do It!", "Phone Field Cannot Be Empty!");
     }
}

void NewContact::on_cancel_button_clicked()
{
    close();
}

QString to_camel_case(const QString &key) {
    std::string word = key.toStdString();
    char *s = &word[0];
    if (*s >= 'a' && *s <= 'z') { //Change the first character to upper case
        *s -= 32;
    }
    while (*s != 0) {
        ++s;
        if (*s == ' ') { //Move to the next character if current character is a space
            ++s;
            if (*s >= 'a' && *s <= 'z') { //Change the next character after a space to upper space
                *s -= 32;
            }
            ++s;
        }
        if (*s >= 'A' && *s <= 'Z') { //Change everything else to lower case
            *s += 32;
        }
    }
    return QString::fromStdString(word);
}
