#include "emailall.h"
#include "ui_emailall.h"

#include <iostream>
#include <QDesktopServices>
#include <QUrl>

EmailAll::EmailAll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailAll)
{
    ui->setupUi(this);
    list_all_contacts();
    personalize_combo();
}

EmailAll::~EmailAll()
{
    delete ui;
}

void EmailAll::on_cancel_button_clicked()
{
    close();
}

void EmailAll::on_personalize_currentTextChanged()
{
    QString text = "[" + ui->personalize->currentText() + "] ";
    if(!ui->personalize->currentText().isEmpty()){
        ui->message_edit->insertPlainText(text);
        ui->message_edit->setFocus();
    }

}

void EmailAll::list_all_contacts()
{
    for (auto key : d.phonebook){
        QListWidgetItem* item = new QListWidgetItem(key.first, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set the checkable flag
        item->setCheckState(Qt::Checked); // also initialize check state
    }
}

void EmailAll::personalize_combo()
{
    ui->personalize->addItem("");
    ui->personalize->addItem("NAME");
    ui->personalize->addItem("PHONE");
    ui->personalize->addItem("EMAIL");
    ui->personalize->addItem("TITLE");
    ui->personalize->addItem("COMPANY");
}

void EmailAll::customize_email()
{
    QString emails{};
    for(int i = 0; i<ui->listWidget->count(); i++){
        if(ui->listWidget->item(i)->checkState()){
            emails += d.get_email(ui->listWidget->item(i)->text()) + ";";
            QString subject_line = ui->subject_edit->text();
            QString message_text = ui->message_edit->toPlainText();

            replace_personalizers(subject_line, i);
            replace_personalizers (message_text, i);
            std::cout<<message_text.toStdString()<<std::endl;
            std::cout<<subject_line.toStdString()<<std::endl;
        }
    }
    //QDesktopServices::openUrl(QUrl("mailto:?to=" + emails +"&subject=" + ui->subject_edit->text() +"&body=" + text, QUrl::TolerantMode));
}

void EmailAll::replace_personalizers(QString &text, int i)
{
     text.replace("[NAME]", ui->listWidget->item(i)->text());
     text.replace("[EMAIL]", d.get_email(ui->listWidget->item(i)->text()));
     text.replace("[PHONE]", QString::number(d.get_phone(ui->listWidget->item(i)->text())));
     text.replace("[TITLE]", d.get_job(ui->listWidget->item(i)->text()));
     text.replace("[COMPANY]", d.get_meet(ui->listWidget->item(i)->text()));
}


void EmailAll::on_send_button_clicked()
{
    customize_email();
}
