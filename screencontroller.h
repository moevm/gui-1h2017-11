#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QWidget>
class Authorisation;
class Table;

class ScreenController : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenController(QWidget *parent = 0);

private slots:
    void on2game(); //переносит нас к игре

protected:
    Authorisation *auth;   //авторизация игрока
    Table *table;          //стол
};

#endif // MAINWINDOW_H
