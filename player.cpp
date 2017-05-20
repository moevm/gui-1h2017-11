#include "player.h"
#include "card.h"
Player::Player()
{
    money = 1000;
    playing = 1;
    round = 0;
    goodToGo= 0;
    Card car;
    car.rank=0;
    car.suit=0;
    playerCards.push_back(car);
    playerCards.push_back(car);

    //cards.push_back(card);

}
Player::~Player()
{

}

void Player::setCards(Card c1, Card c2)
{
    playerCards.push_back(c1);
    playerCards.push_back(c2);
}

void Player::setGTG(int j)
{
    this->goodToGo = j;
}

