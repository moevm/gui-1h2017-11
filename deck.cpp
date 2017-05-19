#include "deck.h"
#include"card.h"
Deck::Deck(QWidget *parent):
    QWidget(parent)
{

    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<13; j++)
        {
            cards[i * 13 + j].suit = i;
            cards[i * 13 + j].rank = j;
        }
    }
    suits[0] = 'D';
    suits[1] = 'S';
    suits[2] = 'H';
    suits[3] = 'C';

    ranks[0] = '2';
    ranks[1] = '3';
    ranks[2] = '4';
    ranks[3] = '5';
    ranks[4] = '6';
    ranks[5] = '7';
    ranks[6] = '8';
    ranks[7] = '9';
    ranks[8] = 'T';
    ranks[9] = 'J';
    ranks[10] = 'Q';
    ranks[11] = 'K';
    ranks[12] = 'A';
    top = 51;
}


void Deck::shuffle()
{
    int x;
    top = 51;
    Card tempCard;
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<13; j++)
        {
            cards[i * 13 + j].suit = i;
            cards[i * 13 + j].rank = j;
        }
    }
    for (int i = 0; i<52; i++)
    {
        x = rand() % 52;
        //tempCard = cards[i];
        //cards[i] = cards[x];
        //cards[x] = tempCard;
    }
}
Card Deck::hitme()
{
    //top--;
    //return cards[top + 1];
}
