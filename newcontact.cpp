#include <iostream>
#include <QMessageBox>
#include <QDoubleValidator>
#include <map>
#include "newcontact.h"
#include "ui_newcontact.h"

NewContact::NewContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewContact)
{
    ui->setupUi(this);
    ui->phone_edit->setValidator( new QDoubleValidator(0, 100, 2, this) );

}

NewContact::~NewContact()
{
    //delete contact;
    delete ui;
}

void NewContact::on_save_button_clicked()
{
    QString name;
    long long phone;
    QString email;
    if(!(ui->phone_edit->text().isEmpty())){
         /* Phone field cannot be empty.
          * If it is, prompt the user to input a phone number
         */
         if((ui->name_edit->text().isEmpty())){
             /*If name field is empty, use the phone number as the name key*/
             name = ui->phone_edit->text();
         }else{
             name = ui->name_edit->text();
         }
         //to_camel_case(name.toStdString());

         phone = ui->phone_edit->text().toLongLong();
         email = ui->email_edit->text();
         contact.save_data(name, phone, email);
         close();

     }else{
         QMessageBox::critical(this,"Can't Do It!", "Phone Field Cannot Be Empty!");

     }
}

void NewContact::on_cancel_button_clicked()
{
    close();
}
