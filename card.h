#ifndef CARD_H
#define CARD_H
#include <QWidget>

class Card: public QWidget
{
    Q_OBJECT
public:
    Card(QWidget* parent = 0);
    int rank;
    int suit;
    //String img='';
};

#endif // CARD_H
