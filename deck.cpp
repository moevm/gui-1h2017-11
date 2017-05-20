#include "deck.h"
#include"card.h"

Deck::Deck()
{
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<13; j++)
        {
            Card card;
            card.suit=i;
            card.rank=j;
            cards.push_back(card);
        }
    }
    suits.push_back("D");
    suits.push_back("S");
    suits.push_back("H");
    suits.push_back("C");

    ranks.push_back("2");
    ranks.push_back("3");
    ranks.push_back("4");
    ranks.push_back("5");
    ranks.push_back("6");
    ranks.push_back("7");
    ranks.push_back("8");
    ranks.push_back("9");
    ranks.push_back("10");
    ranks.push_back("J");
    ranks.push_back("Q");
    ranks.push_back("K");
    ranks.push_back("A");
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
        tempCard = cards[i];
        cards[i] = cards[x];
        cards[x] = tempCard;
    }
}
Card Deck::hitme()
{
    top--;
    return cards[top + 1];
}
