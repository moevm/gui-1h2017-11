#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <QWidget>

class Deck: public QWidget
{
    Q_OBJECT
public:
    Deck(QWidget *parent=0);
private:
    Card cards[52];

public:
    Card hitme();
    char suits[4];
    char ranks[13];
    int top;
    Deck();
    void shuffle();
};

#endif // DECK_H
