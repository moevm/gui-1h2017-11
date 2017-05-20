#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
class Card;

#include "QVector"
class Player
{
public:
    Player();
    ~Player();
    int money;
    QVector <Card> playerCards;
    int playing;
    int round;
    int goodToGo;
    void setGTG(int j);
    virtual void mainAction(){}
    void setCards(Card c1, Card c2);



};

#endif // PLAYER_H
