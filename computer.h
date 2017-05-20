#ifndef COMPUTER_H
#define COMPUTER_H

#include "QString"
#include "player.h"
class Player;

class Computer: public Player
{
public:

    Computer();
    void mainAction(int &act, int betOn);
};

#endif // COMPUTER_H
