#include "customizedialog.h"
#include "ui_customizedialog.h"

CustomizeDialog::CustomizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizeDialog)
{
    ui->setupUi(this);
}

CustomizeDialog::~CustomizeDialog()
{
    delete ui;
}
