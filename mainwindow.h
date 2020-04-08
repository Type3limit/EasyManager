#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <loginwindows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show();

private:
    Ui::MainWindow *ui;
    LoginWindows loginwindow;
    //Ui::LoginWindows loginWindow;
};
#endif // MAINWINDOW_H