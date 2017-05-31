#ifndef TABLE_H
#define TABLE_H
#include <QWidget>
#include <QMatrix>
#include "card.h"
#include "deck.h"
#include "human.h"
#include "gameover.h"


class Deck;
class Card;
class Human;
class Computer;
class GameOver;

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
    Human human;
    QVector <Computer> comp;
    Deck deck1;
    Card tableCards[5];

    int bind;
    int pot;
    int betOn;
    int action;
    int bet;
    int rational;
    int winner;
    int maxPoints;
    int roundWinner;

    QVector <int> handPoints;
    int bestHand[6][3];

    void sayHello(QString name);
    void getName(QString);
    void showCard(QString cardN);
    void flop();
    void turn();
    void river();
    int takeBets();
    int playersToBet();
    int oneLeft();
    int getWinner();
    int getScore(Card hand[]);
    void evaluateHands();
    int tryHand(int array[], int player);




    void startGame();
    void deal();

   
    int playersLeft();


private slots:
    void on_FlopButton_clicked();

    void on_CallButton_clicked();

    void on_CheckButton_clicked();

    void on_pushButton_clicked();

    void on_betButton_clicked();

private:
  Ui::Table *ui;
protected:
  GameOver *gameover;


};

#endif // TABLE_H
