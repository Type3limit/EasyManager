#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <loginwindows.h>
#include <sqlconnect.h>
#include <customizedialog.h>
#include <customeradddialog.h>
#include <QKeyEvent>
#include <QCloseEvent>

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

private:
    Ui::MainWindow *ui;
    LoginWindows loginwindow;
    CustomizeDialog customizeDialog;
    CustomerAddDialog customerAddDialog;
    SqlConnect *sql;
    int ModelChoose[ModelNumber];

};
#endif // MAINWINDOW_H
