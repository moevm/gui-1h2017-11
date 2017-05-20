#ifndef HUMAN_H
#define HUMAN_H

#include "QString"
#include"player.h"
class Player;

class Human : public Player
{

public:
    Human();
    void mainAction(int &act, int betOn);
};

#endif // HUMAN_H
