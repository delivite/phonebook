#include <iostream>
#include <fstream>
#include <QMessageBox>

#include "contacts.h"
#include "ui_contacts.h"
#include "newcontact.h"

Contacts::Contacts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Contacts)
{
    ui->setupUi(this);
}

Contacts::~Contacts()
{
        if(!st.empty()){
            save_to_disk();
            }
    delete ui;
}

void Contacts::save_to_disk()
{
    std::string filename{"data.csv"};
    std::fstream fs;

    fs.open(filename, std::ios::out);
    if(fs.is_open()){
    while(fs.is_open()){
        for (auto each : st){
        std::cout<<each.first<<'\t'<<each.second<<std::endl;
        fs<<each.first<<";"<<each.second<<std::endl;

        }
             fs.close();
    }
}else
        QMessageBox::critical(this,"Error", "Error saving file!",QMessageBox::Ok);
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
