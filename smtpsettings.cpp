#include "smtpsettings.h"
#include "ui_smtpsettings.h"

#include <QFile>
#include <QTextStream>
#include <QIntValidator>

SmtpSettings::SmtpSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmtpSettings)
{
    ui->setupUi(this);
    ui->port_edit->setValidator( new QIntValidator(this) );
    load_data();
}

SmtpSettings::~SmtpSettings()
{
    delete ui;
}

void SmtpSettings::load_data()
{
    QFile file("smtpdata.csv");
    QTextStream stream(&file);
    if(file.exists()){
        if(file.open(QFile::ReadOnly)){
            QString server, port, username, password;

            while (!stream.atEnd()){
                const QStringList data_line { stream.readLine().split(';') };
                server = data_line[0];
                port = data_line[1];
                username = data_line[2];
                password = data_line[3];
            }
            file.close();
            ui->server_edit->setText(server);
            ui->port_edit->setText(port);
            ui->username_edit->setText(username);
            ui->password_edit->setText(password);
        }
    }else
    {
        ui->server_edit->setText("smtp.gmail.com");
        ui->port_edit->setText("465");
    }
}

void SmtpSettings::on_save_button_clicked()
{
    QString server = ui->server_edit->text();
    QString username = ui->username_edit->text();
    QString password = ui->password_edit->text();
    int port = ui->port_edit->text().toInt();;
    QString filename{"smtpdata.csv"};
    QFile file(filename);
    if(file.open(QFile::WriteOnly)){
        QTextStream data_stream(&file);
        data_stream<<server<<";"<<port<<";"<<username<<";"<<password<<"\n";
        data_stream.flush();

        file.close();
    }
    close();
    //send_smtp_details(server, port, username, password);
}

void SmtpSettings::on_cancel_button_clicked()
{
    close();
}
