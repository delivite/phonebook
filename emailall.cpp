#include "emailall.h"
#include "ui_emailall.h"

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

#include "smtp.h"

EmailAll::EmailAll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailAll)
{
    ui->setupUi(this);

    bar = new QStatusBar(this);
    ui->status_layout->addWidget(bar);
    bar->showMessage("Ready! Click on Add Personalization bar to add a personal touch.");

    get_smtp_details();

    list_all_contacts();
    populate_combo();
}

EmailAll::~EmailAll()
{
    emit show_parent();
    delete bar;
    delete ui;
}

void EmailAll::list_all_contacts()
{
    for (auto key : d.phonebook){
        QListWidgetItem* item = new QListWidgetItem(key.first, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set the checkable flag
        item->setCheckState(Qt::Checked); // also initialize check state
    }
}

void EmailAll::populate_combo()
{
    ui->personalize->addItem("");
    ui->personalize->addItem("NAME");
    ui->personalize->addItem("PHONE");
    ui->personalize->addItem("EMAIL");
    ui->personalize->addItem("TITLE");
    ui->personalize->addItem("COMPANY");
}

void EmailAll::send_email()
{
    int count = 0;
    QString emails{};
    for(int i = 0; i<ui->listWidget->count(); i++){
        if(ui->listWidget->item(i)->checkState()){
            //For each item in the contact list, I'm checking for the selected contacts

            QString email = d.get_email(ui->listWidget->item(i)->text());

            QString subject_line = ui->subject_edit->text();
            QString message_text = ui->message_edit->toPlainText();

            //Personalize the subject line and email text
            personalize(subject_line, i);
            personalize(message_text, i);

            //Send email
            Smtp* smtp = new Smtp(username, password, server, port);
            connect(smtp, &Smtp::send_status, this, &EmailAll::show_status);

            if( !files.isEmpty() )
                smtp->sendMail("sampinn316@gmail.com", email ,subject_line, message_text, files );
            else
                smtp->sendMail("sampinn316@gmail.com", email ,subject_line, message_text);
            bar->showMessage("Email Sent to " + email);
            ++count;
        }
    }
    if (count<=0)
    {
        QMessageBox::critical(this, "No Contact Selected", "Select at least one contact to send message", QMessageBox::Ok);
        bar->showMessage("No Contact Selected. Select at least one contact to send message");
    }else
    {
        QString email_trivia = (count>1)? " Emails":" Email";
        QMessageBox::information(this, "Success", QString::number(count) + email_trivia + " Sent Successfully!", QMessageBox::Ok);
        close();
    }
}

void EmailAll::personalize(QString &text, int i)
{
    text.replace("[NAME]", ui->listWidget->item(i)->text());
    text.replace("[EMAIL]", d.get_email(ui->listWidget->item(i)->text()));
    text.replace("[PHONE]", QString::number(d.get_phone(ui->listWidget->item(i)->text())));
    text.replace("[TITLE]", d.get_job(ui->listWidget->item(i)->text()));
    text.replace("[COMPANY]", d.get_meet(ui->listWidget->item(i)->text()));
}

void EmailAll::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void EmailAll::get_smtp_details()
{
    QFile file("smtpdata.csv");
    QTextStream stream(&file);
    if(file.exists()){
        if(file.open(QFile::ReadOnly)){

            while (!stream.atEnd()){
                const QStringList data_line { stream.readLine().split(';') };
                this->server = data_line[0];
                this->port = data_line[1].toInt();
                this->username = data_line[2];
                this->password = data_line[3];
            }
            file.close();
        }
    }else
        QMessageBox::critical(this, "Error", "Can't find the credentials", QMessageBox::Ok);
}

void EmailAll::on_personalize_currentTextChanged()
{
    QString text = "[" + ui->personalize->currentText() + "] ";
    if(!ui->personalize->currentText().isEmpty()){
        ui->message_edit->insertPlainText(text);
        ui->message_edit->setFocus();
    }
}

void EmailAll::show_status(const QString &message)
{
    bar->showMessage(message);
}

void EmailAll::on_cancel_button_clicked()
{
    close();
}

void EmailAll::on_send_button_clicked()
{
    send_email();
}

void EmailAll::on_browse_button_clicked()
{
    browse();
}
