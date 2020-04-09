#include "mainwindow.h"


#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStyleFactory>
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    MainWindow w;
    w.SysStart();
    return  a.exec();
}
