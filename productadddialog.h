#ifndef PRODUCTADDDIALOG_H
#define PRODUCTADDDIALOG_H


#include <QDialog>
#include <QImage>
#include <QFileDialog>
#include <sqlconnect.h>

namespace Ui {
class ProductAddDialog;
}

class ProductAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductAddDialog(QWidget *parent = nullptr);
    ~ProductAddDialog();

private slots:
    void on_FileChooseButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ProductAddDialog *ui;
    SqlConnect *sql;
};

#endif // PRODUCTADDDIALOG_H
