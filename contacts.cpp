#include <iostream>
#include <fstream>
#include <QMessageBox>

#include "contacts.h"
#include "ui_contacts.h"
#include "newcontact.h"
#include "editcontact.h"
#include "data_store.h"

Contacts::Contacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contacts)
{
    ui->setupUi(this);
    load_data();
    list_contacts();
}

Contacts::~Contacts()
{
        if(!st.empty()){
            save_to_disk();
            }
        delete ui;
}

void Contacts::insert(std::string key)
{
    QString name = QString::fromStdString(key); //QListWidget takes QString parameters, so we convert it->first to a QString
    ui->listWidget->addItem(name);
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
        for (auto each : st){

        fs<<each.first<<";"<<each.second<<std::endl;

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
        std::string temp, name, phone;
        while(std::getline(fs,name, ';')){

            std::getline(fs, phone );
            to_camel_case(name);
            st[name] = std::stoll(phone);
        }
        fs.close();

    }else
        QMessageBox::critical(this,"Error", "Error opening file!",QMessageBox::Ok);
}

void Contacts::list_contacts()
{
  for (auto each : st){
        insert(each.first);
    }
}


void Contacts::on_new_contact_clicked()
{
    NewContact con;
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
    qDeleteAll(ui->listWidget->findItems(QString::fromStdString(name), Qt::MatchFixedString));
}

QString Contacts::current_name() const
{
    return ui->listWidget->currentItem()->text();
}

void Contacts::remove_current()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    std::string name = item->text().toStdString();
    st.erase(name);
    delete ui->listWidget->takeItem(ui->listWidget->row(item));
}
