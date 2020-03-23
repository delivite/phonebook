#ifndef EMAILALL_H
#define EMAILALL_H

#include <QDialog>

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

private:
    Ui::EmailAll *ui;
    DataStore d;

    void list_all_contacts();
    void personalize_combo();
    void customize_email();
    void replace_personalizers(QString &source, int i);
};

#endif // EMAILALL_H
