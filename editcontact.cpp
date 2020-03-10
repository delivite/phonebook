#include "editcontact.h"
#include "ui_editcontact.h"
#include "contacts.h"

#include <iostream>
#include <QDoubleValidator>
#include <QMessageBox>

editcontact::editcontact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcontact)
{
    ui->setupUi(this);
    ui->phone_edit->setValidator( new QDoubleValidator(0, 100, 2, this) );
    fill_data();
}

editcontact::~editcontact()
{
    delete ui;
}

void editcontact::fill_data()
{
    ui->name_edit->setText(name);
    std::string p = name.toStdString();                                     //Convert name to std::string from Qstring, the key is an std::string
    QString ph = QString::fromStdString(std::to_string(contact->st[p]));    //Convert phone number to QString
    ui->phone_edit->setText(ph);

}

void editcontact::on_save_button_clicked()
{
   std::string key = ui->name_edit->text().toStdString();
   long long value = ui->phone_edit->text().toULongLong();
   if(contact->st[key]){
       contact->st[key] = value;
   }else{
       contact->st.erase(contact->current_name().toStdString());
       contact->remove_name(contact->current_name().toStdString());
       contact->st[key] = value;
       contact->insert(key);
      }
   QMessageBox::information(this,"Success", "Contact change successful!",QMessageBox::Ok);
   close();
}

void editcontact::on_cancel_button_clicked()
{
    close();
}
