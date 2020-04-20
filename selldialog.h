#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>

namespace Ui {
class SellDialog;
}

class SellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SellDialog(QWidget *parent = nullptr);
    ~SellDialog();

private:
    Ui::SellDialog *ui;
};

#endif // SELLDIALOG_H
