#include "editcontact.h"
#include "ui_editcontact.h"

editcontact::editcontact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcontact)
{
    ui->setupUi(this);
}

editcontact::~editcontact()
{
    delete ui;
}
