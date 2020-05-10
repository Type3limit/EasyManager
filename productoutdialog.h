#ifndef PRODUCTOUTDIALOG_H
#define PRODUCTOUTDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
#include <QListWidget>
#include<QListWidgetItem>
#include <QAction>
namespace Ui {
class ProductOutDialog;
}

class ProductOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductOutDialog(QWidget *parent = nullptr);
    ~ProductOutDialog();

private slots:

    void on_ComfirmButton_clicked();

    void on_ProductView_itemDoubleClicked(QListWidgetItem *item);

public:
    void Initialize();

private:
    Ui::ProductOutDialog *ui;
    SqlConnect *sql;
    QString * IDs;
    QString * Names;
    QString * Images;
    QString * Costs;
    QString * Infoes;

    QString CurrentName;
    QString CurrentCount;
    QString CurrentCost;

    int count ;
};


#endif // PRODUCTOUTDIALOG_H
