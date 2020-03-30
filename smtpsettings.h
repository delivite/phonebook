#ifndef SMTPSETTINGS_H
#define SMTPSETTINGS_H

#include <QDialog>

namespace Ui {
class SmtpSettings;
}

class SmtpSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SmtpSettings(QWidget *parent = nullptr);
    ~SmtpSettings();

signals:
    //void send_smtp_details(const QString &, const int &, const QString &, const QString &);
private slots:

    void on_save_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::SmtpSettings *ui;
    void load_data();
};

#endif // SMTPSETTINGS_H
