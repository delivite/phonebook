#include "editcontact.h"
#include "ui_editcontact.h"
#include "datastore.h"

#include <iostream>
#include <QDoubleValidator>
#include <QMessageBox>

editcontact::editcontact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcontact)
{
    ui->setupUi(this);    
    ui->phone_edit->setValidator( new QDoubleValidator(0, 100, 2, this) );
}

editcontact::~editcontact()
{
    delete ui;
}


void editcontact::fill_data(QString name)
{    
    this->ui->name_edit->setText(name);
    DataStore d;
    ui->phone_edit->setText(QString::number(d.get_phone(name)));
    ui->email_edit->setText(d.get_email(name));
}

void editcontact::on_save_button_clicked()
{
    DataStore d;
    QString name {ui->name_edit->text()};
    long long phone {ui->phone_edit->text().toLongLong()};
    QString email{ui->email_edit->text()};
    QString job{d.get_job(name)}, org{d.get_meet(name)};

    emit edit(name, phone, email, job, org);
    close();
}

void editcontact::on_cancel_button_clicked()
{
    close();
}
