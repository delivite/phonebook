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

}

NewContact::~NewContact()
{
    delete ui;
}

void NewContact::on_save_button_clicked()
{
    if(!(ui->phone_edit->text().isEmpty())){
         /* Phone field cannot be empty.
          * If it is, prompt the user to input a phone number
         */
         if((ui->name_edit->text().isEmpty())){
             /*If name field is empty, use the phone number as the name key*/
             name = ui->phone_edit->text().toStdString();
         }else{
             name = ui->name_edit->text().toStdString();
         }

         phone = ui->phone_edit->text().toLongLong();

         cache->st.insert(std::pair<std::string, long long>(name,phone));
      //   cache->st[name]=phone;
         QMessageBox::information(this,"Success", "Saved!",QMessageBox::Ok);
         close();
     }else{
         QMessageBox::critical(this,"Can't Do It!", "Phone Field Cannot Be Empty!");

     }
}

void NewContact::on_cancel_button_clicked()
{
    close();
}
