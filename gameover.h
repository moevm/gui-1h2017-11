#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QWidget>
#include "table.h"

namespace Ui {
class GameOver;
}
class GameOver: public QWidget
{
    Q_OBJECT
public:
    GameOver(QWidget* parent = 0);
    ~GameOver();
protected:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
