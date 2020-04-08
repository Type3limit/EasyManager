#include "mainwindow.h"


#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStyleFactory>
int main(int argc, char *argv[])
{

    QSqlDatabase database ;
    database = QSqlDatabase::database("QMYSQL");
    database.setHostName("127.0.0.1");
    database.setPort(3306);
    database.setDatabaseName("EasyManager");
    database.setUserName("root");
    database.setPassword("3939520");

    qDebug()<<database.lastError().text();

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    MainWindow w;
    w.show();
    return  a.exec();
}
