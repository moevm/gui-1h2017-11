#ifndef DECK_H
#define DECK_H
#include "QVector"
#include "QString"
class Card;

class Deck
{

private:
    QVector <Card> cards;

public:
    Deck();
    Card hitme();
    QVector <QString> suits;
    QVector <QString> ranks;
    int top;

    void shuffle();
};

#endif // DECK_H
