#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QKeyEvent>
#include <QCloseEvent>

#include <loginwindows.h>
#include <sqlconnect.h>
#include <customizedialog.h>
#include <customeradddialog.h>
#include <selldialog.h>
#include <customerrechargedialog.h>
#include <productinmodeldialog.h>
#include <customerviewdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SysStart();
    void LoadCustomize();

protected:
    void keyPressEvent(QKeyEvent*event);

public slots:
    void on_loginwindows_close();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void on_LoginoutButton_2_clicked();

    void on_SellButton_clicked();

    void on_CutomeraddButton_clicked();

    void on_CustomerrechargeButton_clicked();

    void on_ProductinButton_clicked();

    void on_CustomerinfoButton_clicked();

private:
    Ui::MainWindow *ui;
    SqlConnect *sql;
    int ModelChoose[ModelNumber];


private:
    LoginWindows loginwindow;
    CustomizeDialog customizeDialog;
    CustomerAddDialog customerAddDialog;
    SellDialog sellDialog;
    CustomerRechargeDialog CRechargeDialog;
    ProductInModelDialog ModelDialog;
    CustomerViewDialog CustomerView;

};
#endif // MAINWINDOW_H
