#include "editcontact.h"
#include "ui_editcontact.h"
#include "contacts.h"
#include "datastore.h"

#include <iostream>
#include <QDoubleValidator>
#include <QMessageBox>

editcontact::editcontact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcontact)//, contact(new Contacts)
{
    ui->setupUi(this);
    name = contact->current_name()->text();
    ui->phone_edit->setValidator( new QDoubleValidator(0, 100, 2, this) );
    fill_data();
}

editcontact::~editcontact()
{
    //delete contact;
    delete ui;
}

void editcontact::fill_data()
{

    ui->name_edit->setText(name);
    ui->phone_edit->setText(QString::number(contact->get_phone(name)));
    ui->email_edit->setText(contact->get_email(name));

}

void editcontact::on_save_button_clicked()
{
  /* QString key = ui->name_edit->text();
   long long value = ui->phone_edit->text().toULongLong();
   QString email = ui->email_edit->text();
   if(contact->contains(key)){
       phonebook[key] = Person(key, value, email);
   }else{
       phonebook.erase(contact->current_name());
       contact->remove_name(contact->current_name().toStdString());
       phonebook[key] = Person(key, value, email);
       contact->list_insert(key);
      }
   QMessageBox::information(this,"Success", "Contact change successful!",QMessageBox::Ok);
   close();*/
}

void editcontact::on_cancel_button_clicked()
{
    close();
}
