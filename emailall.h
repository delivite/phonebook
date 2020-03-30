#ifndef EMAILALL_H
#define EMAILALL_H

#include <QDialog>
#include <QFileDialog>
#include <QStatusBar>


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

signals:
    void show_parent();

public slots:
    void show_status(const QString &);

private slots:
    void on_cancel_button_clicked();

    void on_personalize_currentTextChanged();

    void on_send_button_clicked();

    void on_browse_button_clicked();

private:
    Ui::EmailAll *ui;
    DataStore d;
    QStringList files;
    QStatusBar *bar;
    QString server, username, password;
    int port{};

    void list_all_contacts();
    void populate_combo();
    void send_email();
    void personalize(QString &source, int i);
    void browse();
    void get_smtp_details();
};

#endif // EMAILALL_H
