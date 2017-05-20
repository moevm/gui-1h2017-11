#include "computer.h"

Computer::Computer()
{

}
void Computer::mainAction(int &act, int betOn)
{
    if (playerCards.at(0).rank < 8 && playerCards.at(1).rank < 8)
    {
        if (playerCards.at(0).rank != playerCards.at(1).rank)
            act = 0;
        else
            act= 1;
    }
    else
    {
        if (playerCards.at(0).rank < 10 && playerCards.at(1).rank < 10)
        {
            if (playerCards.at(0).rank != playerCards.at(1).rank)
                act= 1;
            else
                act= 2;
        }
        else
        {
            act = 2;
        }
    }
}
