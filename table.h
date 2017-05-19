#ifndef TABLE_H
#define TABLE_H
#include <QWidget>
#include "card.h"
#include "deck.h"
class Deck;
class Card;
class Player;

namespace Ui {
  class Table;
}
class Table : public QWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent=0);
    ~Table();
    QString name="player";
    void sayHello(QString name);
    void getName(QString);

    void deal();
    void flop();
    void turn();
    void river();

    //Deck deck1;
    int bind;
    Card tableCards[5];
    int pot, action, bet, rational, betOn, winner, maxPoints, roundWinner;
    int handPoints[6];
    int bestHand[6][3];
    int playersLeft();
    int computerAction(int playerNum);
    /*checks if someone still got bet/call*/
    int playersToBet();
    int takeBets();
    int oneLeft();
    int getWinner();
    int getScore(Card hand[]);
    int tryHand(int array[], int player);
    void evaluateHands();
    void startGame();
    void SMS(int k, int &money)
    {
        pot = pot + k;
        money = money - k;
    }


private:
  Ui::Table *ui;

};

#endif // TABLE_H
