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
    void insert (std::string key);
    void edit(std::string);        
    void remove_name(std::string name);
    QString current_name()const;




private slots:
    void on_new_contact_clicked();

    void on_exit_app_clicked();

    void on_delete_contact_clicked();

    void on_edit_contact_clicked();

private:
    Ui::Contacts *ui;
    void save_to_disk();
    void load_data();
    void list_contacts();
    void remove_current();

};
#endif // CONTACTS_H
void to_camel_case(std::string &word);
