#ifndef LOGINWINDOWS_H
#define LOGINWINDOWS_H

#include <QMainWindow>

namespace Ui {
class LoginWindows;
}

class LoginWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindows(QWidget *parent = nullptr);
    ~LoginWindows();

private:
    Ui::LoginWindows *ui;
};

#endif // LOGINWINDOWS_H
