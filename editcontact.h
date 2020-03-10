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

private:
    Ui::editcontact *ui;
};

#endif // EDITCONTACT_H
