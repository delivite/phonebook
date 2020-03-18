#include <iostream>
#include <fstream>
#include <QMessageBox>

#include "contacts.h"
#include "ui_contacts.h"
#include "newcontact.h"
#include "editcontact.h"
#include "person.h"

//Ui::Contacts *Contacts::ui = new Ui::Contacts;
Contacts::Contacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contacts)
{

    std::cout<<"I have been created"<<std::endl;
    ui->setupUi(this);    
    load_data();
    list_contacts();
    ui->listWidget->setCurrentRow(0);

    //connect(this, SIGNAL(list(QString)), this, SLOT(list_it(QString)));
}

Contacts::~Contacts()
{
        if(!store.phonebook.empty()){
            save_to_disk();
            }
        delete ui;
}

void Contacts::save_data(QString name, long long phone, QString email)
{
    if(contains(name)){
    QMessageBox::StandardButtons change;
    change = QMessageBox::warning(this, "Exists", "This contact is already here. Do you want to replace it?", QMessageBox::Yes|QMessageBox::No);
    if (change==QMessageBox::Yes){
        store.phonebook.erase(name);
        store.phonebook.insert(std::pair<QString, Person>(name, Person(name,phone,email)));
        QMessageBox::information(this,"Success", "Contact change successful!",QMessageBox::Ok);

    }
    }else{
    store.phonebook.insert(std::pair<QString, Person>(name, Person(name,phone,email)));
    QMessageBox::information(this,"Success", "Saved!",QMessageBox::Ok);

    list_insert(name);
    }
}

void Contacts::list_insert(QString key)
{

    QListWidgetItem* item = new QListWidgetItem(QIcon(":/img/people_106508.png"), key);
    ui->listWidget->addItem(item);
}

void Contacts::edit(std::string)
{

}


void Contacts::save_to_disk()
{
    std::string filename{"data.csv"};
    std::fstream fs;

    fs.open(filename, std::ios::out);
    if(fs.is_open()){
    while(fs.is_open()){
        for (auto each : store.phonebook){

        fs<<each.first.toStdString()<<";"<<each.second.phone<<";"<<each.second.email.toStdString()<<std::endl;

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
        std::string email, name, phone;
        while(std::getline(fs,name, ';')){

            std::getline(fs, phone, ';' );
            std::getline(fs, email );
            to_camel_case(name);
            store.phonebook[QString::fromStdString(name)] = Person(QString::fromStdString(name), std::stoll(phone), QString::fromStdString(email));
        }
        fs.close();

    }else
        QMessageBox::critical(this,"Error", "Error opening file!",QMessageBox::Ok);
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
    QMessageBox::information(this, "Success", "Contact deleted!");

    }
}

void Contacts::on_edit_contact_clicked()
{
    editcontact e;
    e.setModal(true);
    e.exec();
}

void to_camel_case(std::string &word) {
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
}

void Contacts::remove_name(std::string name)
{
    //qDeleteAll(ui->listWidget->findItems(QString::fromStdString(name), Qt::MatchFixedString));
}

bool Contacts::contains(QString key)
{
    auto it = store.phonebook.find(key);
    return (it!= store.phonebook.end())?true:false;
}

long long Contacts::get_phone(QString name)
{
    auto it = store.phonebook.find(name);
    return it->second.phone;
}

QString Contacts::get_email(QString name)
{
    auto it = store.phonebook.find(name);
    return it->second.email;
}

QListWidgetItem* Contacts::current_name() const
{

   return ui->listWidget->currentItem();
}

void Contacts::remove_current()
{
    QListWidgetItem* item = ui->listWidget->currentItem();    
    store.phonebook.erase(item->text());
    delete ui->listWidget->takeItem(ui->listWidget->row(item));
}

void Contacts::on_listWidget_itemSelectionChanged()
{
    QString key = current_name()->text();
    ui->name_show->setText(key);
    auto it = store.phonebook.find(key);
    if(it != store.phonebook.end()){
        ui->phone_show->setText(QString::number(it->second.phone));
        ui->email_show->setText(it->second.email);
    }
}


