#ifndef EMAILALL_H
#define EMAILALL_H

#include <QDialog>
#include <QFileDialog>

#include "datastore.h"

namespace Ui {
class EmailAll;
}

class EmailAll : public QDialog
{
    Q_OBJECT

public:
    explicit EmailAll(QWidget *parent = nullptr);
    ~EmailAll();

private slots:
    void on_cancel_button_clicked();

    void on_personalize_currentTextChanged(/*const QString &arg1*/);

    void on_send_button_clicked();

    void mailSent(QString);

    void on_browse_button_clicked();

private:
    Ui::EmailAll *ui;
    DataStore d;
    QStringList files;

    void list_all_contacts();
    void personalize_combo();
    void customize_email();
    void replace_personalizers(QString &source, int i);
    void sendMail();
    void browse();
};

#endif // EMAILALL_H
