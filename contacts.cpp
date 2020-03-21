#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QDesktopServices>
#include <memory>
#include <QUrl>

#include "contacts.h"
#include "ui_contacts.h"
#include "newcontact.h"
#include "editcontact.h"
#include "person.h"


Contacts::Contacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contacts)
{
    ui->setupUi(this);    
    load_data();
    list_contacts();
    ui->listWidget->setCurrentRow(0);
    ui->statusbar->showMessage("Ready!");
    connect(this, &Contacts::current_contact, &e, &editcontact::fill_data);
    connect(&e, &editcontact::edit, this, &Contacts::edit_data);    
}

Contacts::~Contacts()
{
        if(!store.phonebook.empty()){
            save_to_disk();
            }

        delete ui;
}

void Contacts::save_data(QString name, long long phone, QString email, QString job, QString meeting, QString remember)
{
    if(store.contains(name)){
    QMessageBox::StandardButtons change;
    change = QMessageBox::warning(this, "Exists", "This contact is already here. Do you want to replace it?", QMessageBox::Yes|QMessageBox::No);
    if (change==QMessageBox::Yes){
        store.phonebook.erase(name);
        store.phonebook.insert(std::pair<QString, Person>(name, Person(name, phone, email, job, meeting, remember)));
        QMessageBox::information(this,"Success", "Contact change successful!", QMessageBox::Ok);
    }
    }else{
    store.phonebook.insert(std::pair<QString, Person>(name, Person(name, phone, email, job, meeting, remember)));
    QMessageBox::information(this, "Success", "Saved!", QMessageBox::Ok);

    list_insert(name);
    }
}

void Contacts::edit_data(QString name, long long phone, QString email, QString job, QString meeting)
{
    QString remember = ui->remember_show->toPlainText();
     remove_current();
     store.phonebook.insert(std::pair<QString, Person>(name, Person(name, phone, email, job, meeting, remember)));
     list_insert(name);

     QMessageBox::information(this, "Success", "Contact change successful!", QMessageBox::Ok);
}


void Contacts::list_insert(QString key)
{
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/img/people_106508.png"), key);
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void Contacts::email_all_contacts()
{
    QString all_emails = store.get_all_emails();
    QDesktopServices::openUrl(QUrl("mailto:" + all_emails, QUrl::TolerantMode));

}


void Contacts::save_to_disk()
{
    std::string filename{"data.csv"};
    std::fstream fs;

    fs.open(filename, std::ios::out);
    if(fs.is_open()){
    while(fs.is_open()){
        for (auto each : store.phonebook){
        fs<<each.first.toStdString()<<";"<<each.second.phone<<";"<<each.second.email.toStdString()
         <<";"<<each.second.job.toStdString()<<";"<<each.second.meeting.toStdString()<<";"<<each.second.remember.toStdString()<<std::endl;
        }
             fs.close();
    }
}else
        QMessageBox::critical(this,"Error", "Error saving file!",QMessageBox::Ok);
}

void Contacts::load_data()
{
    std::fstream fs;
    std::string filename{"data.csv"};
    fs.open(filename, std::ios::in);
    if(fs.is_open()){
        std::string email, name, phone, job, meeting, remember;
        if (!(fs.peek() == std::ifstream::traits_type::eof())){

        while(std::getline(fs,name, ';')){
            std::getline(fs, phone, ';' );
            std::getline(fs, email, ';' );
            std::getline(fs, job, ';' );
            std::getline(fs, meeting, ';' );
            std::getline(fs, remember);

            store.phonebook[QString::fromStdString(name)] = Person(QString::fromStdString(name), std::stoll(phone)
                                , QString::fromStdString(email), QString::fromStdString(job)
                                , QString::fromStdString(meeting), QString::fromStdString(remember));
        }
        }
        fs.close();

    }else
        ui->statusbar->showMessage("Unable to open file");
}

void Contacts::list_contacts()
{

  for (auto each : store.phonebook){      
        list_insert(each.first);
    }
}


void Contacts::on_new_contact_clicked()
{
    NewContact con;
    connect(&con, &NewContact::send, this, &Contacts::save_data);
    con.setModal(true);
    con.exec();
}

void Contacts::on_exit_app_clicked()
{
    QApplication::quit();
}

void Contacts::on_delete_contact_clicked()
{
    QMessageBox::StandardButtons confirm;
    confirm = QMessageBox::warning(this, "Confirm", "Delete Contact?", QMessageBox::Yes|QMessageBox::No);
    if (confirm == QMessageBox::Yes){
    remove_current();
    ui->statusbar->showMessage("Contact Deleted");
    }
}

void Contacts::on_edit_contact_clicked()
{
    emit current_contact(ui->listWidget->currentItem()->text()); //Send selected contact as a signal to the Contacts class

    //Show dialog
    e.setModal(true);
    e.exec();
}

void Contacts::remove_current()
{
    QListWidgetItem* item = ui->listWidget->currentItem();    
    store.phonebook.erase(item->text());
    delete ui->listWidget->takeItem(ui->listWidget->row(item));
}

void Contacts::on_listWidget_itemSelectionChanged()
{
    QString key = ui->listWidget->currentItem()->text();
    ui->name_show->setText(key);
    ui->phone_show->setText(QString::number(store.get_phone(key)));
    ui->email_show->setText(store.get_email(key));
    ui->job_show->setText(store.get_job(key) + " at " + store.get_meet(key));
    ui->remember_show->setPlainText(store.get_remember(key));
    ui->statusbar->showMessage(key);
}

void Contacts::on_pushButton_clicked()
{
    QString email = store.get_email(ui->listWidget->currentItem()->text());
    QDesktopServices::openUrl(QUrl("mailto:" + email, QUrl::TolerantMode));

}

/*void Contacts::on_pushButton_4_clicked()
{
    ui->remember_show->setTextInteractionFlags(Qt::TextInteractionFlag::TextEditable);
    auto newCursor = new QTextCursor(ui->remember_show->document());
    newCursor->movePosition(QTextCursor::End);
    ui->remember_show->setTextCursor(*newCursor);
   // ui->->setTextCursor(newCursor);
}*/

void Contacts::on_save_remember_clicked()
{
    QString name = ui->listWidget->currentItem()->text();
    QString text = ui->remember_show->toPlainText();
    store.set_remember(name, text);
    ui->statusbar->showMessage("Remember text saved!");
}

void Contacts::on_actionEmail_All_Contacts_triggered()
{
    email_all_contacts();
}

void Contacts::on_actionClose_triggered()
{
    QApplication::quit();
}

void Contacts::on_actionNew_Contact_triggered()
{
    on_new_contact_clicked();
}

void Contacts::on_pushButton_3_clicked()
{
    email_all_contacts();
}
