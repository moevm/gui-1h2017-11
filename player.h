#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <QWidget>
class Player: public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent=0);
    int money;
    Card cards[2];
    int playing;
    int round;
    int goodToGo;

};

#endif // PLAYER_H
