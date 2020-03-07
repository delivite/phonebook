#ifndef CONTACTS_H
#define CONTACTS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Contacts; }
QT_END_NAMESPACE

class Contacts : public QMainWindow
{
    Q_OBJECT

public:
    Contacts(QWidget *parent = nullptr);
    ~Contacts();
    std::map<std::string, long long> st;
    void save_to_disk();

private slots:
    void on_new_contact_clicked();

    void on_exit_app_clicked();

private:
    Ui::Contacts *ui;
};
#endif // CONTACTS_H
