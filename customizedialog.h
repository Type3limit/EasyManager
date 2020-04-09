#ifndef CUSTOMIZEDIALOG_H
#define CUSTOMIZEDIALOG_H

#include <QDialog>

namespace Ui {
class CustomizeDialog;
}

class CustomizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomizeDialog(QWidget *parent = nullptr);
    ~CustomizeDialog();

private:
    Ui::CustomizeDialog *ui;
};

#endif // CUSTOMIZEDIALOG_H
