#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&loginwindow,(&LoginWindows::close),this,(&MainWindow::on_loginwindows_close));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SysStart()
{
    loginwindow.show();
}

void MainWindow::on_loginwindows_close()
{
    this->show();
    QString WelcomeWords = QString("Welcome! %1").arg(loginwindow.GetCurrentUser());
    ui->WelcomeLabel->setText(WelcomeWords);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::No == QMessageBox::question(this,"warning","确认退出吗？",QMessageBox::Ok,QMessageBox::No)) event->ignore();
    else {
        QMainWindow::closeEvent(event);
    }
}
