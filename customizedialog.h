#ifndef CUSTOMIZEDIALOG_H
#define CUSTOMIZEDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <sqlconnect.h>

const int ProcessStep = (100/ModelNumber);

namespace Ui {
class CustomizeDialog;
}

class CustomizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomizeDialog(QWidget *parent = nullptr);
    ~CustomizeDialog();

    bool SetName(QString Name);
protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void on_StartButton_clicked();

    void on_SureButton_clicked();

    void on_CancelButton_clicked();

    void on_backbutton_clicked();

    void on_CompliteButton_clicked();

private:
    Ui::CustomizeDialog *ui;
    SqlConnect * sql;
    QString UserName;
    int Model[ModelNumber];
    QString ModelDescribe[ModelNumber];
    int CurrentIndex;
private:
    void ModelProcess();
    void initilize();
};

#endif // CUSTOMIZEDIALOG_H
