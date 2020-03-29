#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QDialog>

namespace Ui {
class editcontact;
}

class editcontact : public QDialog
{
    Q_OBJECT

public:
    explicit editcontact(QWidget *parent = nullptr);
    ~editcontact();

public slots:   
   void fill_data(QString name);

private slots:
    void on_save_button_clicked();

    void on_cancel_button_clicked();

signals:
    void edit(QString name, long long phone, QString email, QString job, QString meeting);

private:
    Ui::editcontact *ui;
    QString name{};
};

#endif // EDITCONTACT_H
