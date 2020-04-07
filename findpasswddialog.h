#ifndef FINDPASSWDDIALOG_H
#define FINDPASSWDDIALOG_H

#include <QDialog>

namespace Ui {
class FindPasswdDialog;
}

class FindPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindPasswdDialog(QWidget *parent = nullptr);
    ~FindPasswdDialog();

private:
    Ui::FindPasswdDialog *ui;
};

#endif // FINDPASSWDDIALOG_H
