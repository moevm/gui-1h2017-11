#include "table.h"
#include "ui_table.h"
#include <QStyle>
#include "human.h"
#include "computer.h"
#include "stdio.h"


Table::Table(QWidget *parent):
    QWidget(parent), ui(new Ui::Table) {

    Computer c;
    c.money = 1000;
    c.goodToGo= 0;
    c.playing = 1;
    c.round=0;
    Card car;
    car.rank=0;
    car.suit=0;
    c.playerCards.push_back(car);
    c.playerCards.push_back(car);
    //tableCards[0]=car;
    //tableCards[1]=car;
    for (int i=0; i<5; i++)
    {
        tableCards[i].rank=0;
        tableCards[i].suit=0;
    }

    for (int i=0; i<3; i++)
        comp.push_back(c);
    human.money=1000;
    human.goodToGo =0;
    human.playing=1;
    human.round=0;
    human.setCards(car, car);
    pot =20;


    ui->setupUi(this);
    ui->BankLabel->setText(QString::number(pot));
    gameover=new GameOver(parent);

    ui->CheckButton->setEnabled(false);
    ui->FlopButton->setEnabled(false);
    ui->CallButton->setEnabled(false);
    ui->pushButton->setEnabled(false);

    //sleep(10);

    startGame();


}

Table::~Table() {
  delete ui;
}
void Table::getName(QString Name){
    if(Name!=""||Name!=" ")
        name=Name;
     sayHello(name);
}

void Table::sayHello(QString name)
{
    ui->labelName->setText(name);
}

void Table::showCard(QString cardN)
{
    ui->PlayerCard1->setStyleSheet("border-image: url(:/imgs/cards/set/"+cardN+".png)");
}

int Table::playersLeft()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (comp.at(i).money>0)
                count++;

    if (human.money > 0)
        count++;
    return count;

}
void Table::deal()
{
    for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<2; j++)
            {
                if (comp.at(i).playing)
                {
                    comp[i].playerCards[j] = deck1.hitme();
                }
            }
        }
        for (int j = 0; j<2; j++)
        {
            if (human.playing)
            {
                human.playerCards[j] = deck1.hitme();
            }
        }
        for (int i = 0; i<5; i++)
            tableCards[i].rank = -1;
}


int Table::playersToBet()
{
    for (int i = 0; i < 3; i++)
        if (comp.at(i).round == 1 && comp.at(i).goodToGo == 0)
            return 1;
    if (human.round == 1 && human.goodToGo == 0)
        return 1;
    return 0;
}

void Table::turn()
{
    tableCards[3] = deck1.hitme();     //выкладывается четвертая карты на стол
}

void Table::river()
{
    tableCards[4] = deck1.hitme();     //выкладывается последняя карты на стол
}
void Table::flop()
{
    for (int i = 0; i<3; i++)
        tableCards[i] = deck1.hitme();    //выкладываются 3 карты на стол
}

int Table::takeBets()
{
    betOn = 0; //nobody make a bet yet
    for (int k = 0; k<3; k++)
        comp[k].goodToGo = 0;
    human.goodToGo = 0;

    //everyone can do his ход from bb+1
    for (int k = bind + 1; k < bind + 5; k++)
    {
        int count1 = 0; // count of players in current round
        for (int g = bind + 1; g < bind + 5; g++)
        {
            if (g == 3)
            {
                if (human.playing)
                    count1++;
            }
            else
                if (g==4)
                {
                    g=0;
                    if (comp[g].playing)
                        count1++;
                    g=4;
                }
                else
                    if (comp[g].playing)
                        count1++;
        }
        if (count1 == 1)
            return 0;    //left one player - winner

        if (k % 4 == 3)  //if this player - human
        {
            if (human.round)  //he doesn't check
            {
                //human.mainAction(action, betOn);
                if (betOn)  // if someone has made a bet then FLopButton & CallButton are active
                {
                    ui->FlopButton->setEnabled(true);
                    ui->CallButton->setEnabled(true);
                }
                else
                {   //all buttons are active
                    ui->FlopButton->setEnabled(true);
                    ui->CheckButton->setEnabled(true);
                    ui->CallButton->setEnabled(true);

                }
                //if Flop then human is out of game
                if (action == 1)
                {
                    human.round = 0;
                }
                else
                {// if Check then we go on
                    if (action == 2)
                        continue;
                    else
                    {
                        if (betOn)  //if someone has made a bet
                        {
                            pot += betOn;
                            human.money -= betOn;
                            human.goodToGo = 1;
                            ui->BankLabel->setText(QString :: number(pot));
                        }
                        else
                        {
                            ui->pushButton->setEnabled(true);

                            pot += bet;
                            ui->BankLabel->setText(QString :: number(pot));
                            human.money -= bet;
                            betOn = bet;
                            human.goodToGo = 1;
                        }
                    }
                }
            }
        }
        else //player - comp
        {
            if (comp.at(k%4).round == 0)
                continue;
            rational = rand() % 2;
            if (rational)
            {
                comp[k % 4].mainAction(action, betOn);
            }
            else
            {
                action = rand() % 4;
            }
            if (action == 0)
            {
                comp[k % 4].round = 0;
                //cout << (comp[k % 6]).name << " flops..."
             }
            else if (action == 1 && betOn == 0)
            {
                if (k%4 == 0) ui->MoneyCarl->setText("checks");
                if (k%4 == 1) ui->MoneyEli->setText("checks");
                if (k%4 == 2) ui->MoneyMax->setText("checks");
                //std::cout << (comp[k % 4]).name << " checks." << endl << endl;
                continue;
            }
            else
            {
                if ((betOn) && (comp.at(k%4).round))
                {
                    pot += betOn;
                    ui->BankLabel->setText(QString :: number(pot));
                    comp[k % 4].money -= betOn;
                    if (k%4 == 0) ui->MoneyCarl->setText(QString::number(comp.at(k%4).money));
                    if (k%4 == 1) ui->MoneyEli->setText(QString::number(comp.at(k%4).money));
                    if (k%4 == 2) ui->MoneyMax->setText(QString::number(comp.at(k%4).money));
                    // cout << (comp[k % 4]).name << " calls!" << endl << endl;
                    comp[k % 4].goodToGo = 1;
                }
                else
                {
                    bet = (rand() % (comp.at(k%4).money / 3) + 10);
                    pot += bet;
                    ui->BankLabel->setText(QString :: number(pot));
                    comp[k % 4].money -= bet;
                    if (k%4 == 0) ui->MoneyCarl->setText(QString::number(comp.at(k%4).money));
                    if (k%4 == 1) ui->MoneyEli->setText(QString::number(comp.at(k%4).money));
                    if (k%4 == 2) ui->MoneyMax->setText(QString::number(comp.at(k%4).money));
                    //  cout << comp[k % 4].name << " bets " << bet << endl << endl;
                    betOn = bet;
                   comp[k % 4].goodToGo = 1;
                }
            }
        }
    }
    if (betOn && playersToBet())
    {
        for (int k = bind + 1; k<bind + 5; k++)
        {
            if (k % 4 == 3) //if human
            {
                if (human.round == 0 && human.goodToGo == 0)
                {
                    ui->FlopButton->setEnabled(true);
                    ui->CallButton->setEnabled(true);

                    if (action == 1)
                        human.round = 0;
                    else
                    {
                        pot += betOn;
                        ui->BankLabel->setText(QString :: number(pot));
                            //(*human).money -= betOn;
                    }
                }
            }
            else  //if comp
            {
                if (comp.at(k%4).round == 0 || comp.at(k%4).goodToGo == 1)
                    continue;
                action = rand() % 2;
                if (action == 0)
                {
                    comp[k % 4].round = 0;
                    //    std::cout << (comp[k % 6]).name << " flops..." << endl << endl;
                }
                else
                {
                    pot += betOn;
                    ui->BankLabel->setText(QString :: number(pot));
                    comp[k % 4].money -= betOn;

                   //     std::cout << (comp[k % 6]).name << " calls!" << endl << endl;
                    comp[k % 4].goodToGo = 1;
                }
            }
        }
    }
    return 0;
}

void Table::startGame()
{
    int i = 0;
    while (this->playersLeft()>1)
    {
        bind = i % 4;
        /* starting default values*/
        for (int z = 0; z<3; z++)
        {
            if (comp.at(z).money<1)
            {
                comp[z].round=0;
                comp[z].playing=0;
            }
        }
        if (human.money<1)
        {
            human.playing = 0;
            human.round = 0;
        }

        for (int z=0; z<4; z++)
        {
            if (z!=3)//not human
            {
                if (comp.at(z).playing)
                {
                    comp[z].round=1;
                }

                handPoints.push_back(-1);
            }
            else
            {
                if (human.playing)
                    human.round=1;
                handPoints.push_back(-1);
            }
        }
        for (int x=0; x<4; x++)
        {
            for (int y = 0; y<3; y++)
            {
                bestHand[x][y] = -1;
            }
        }


        /* checking for game over*/

        if (human.playing == 0)
        {

            gameover->show();
            this->hide();
            //break;
        }

        if (i + 1 > 1)
        {
            pot = 0;
        }
        if (bind != 3)
        {
            if (comp.at(bind).money >= 20)
            {
                comp[bind].money-=20;
            }
            else
            {
                comp[bind].playing=0;
            }
        }
        else
        {
            if (human.money>=20)
                human.money-=20;
            else
                human.playing =0;
        }

        ui->label_2->setNum(i+1);
        deck1.shuffle();
        deal();


        ui->MoneyCarl->setNum(comp.at(0).money);
        ui->MoneyEli->setNum(comp.at(1).money);
        ui->MoneyMax->setNum(comp.at(2).money);
        ui->PlayerMoney->setNum(human.money);
        QString cardN1;
        QString cardN2;
        if (human.playerCards.at(0).rank>=0 && human.playerCards.at(0).suit>=0)
             cardN1=deck1.ranks.at(human.playerCards.at(0).rank)+deck1.suits.at(human.playerCards.at(0).suit);
        if (human.playerCards.at(1).rank>=0 && human.playerCards.at(1).suit>=0)
             cardN2=deck1.ranks.at(human.playerCards.at(1).rank)+deck1.suits.at(human.playerCards.at(1).suit);
        ui->PlayerCard1->setStyleSheet("border-image: url(:/imgs/cards/set/"+cardN1+".png)");
        ui->PlayerCard2->setStyleSheet("border-image: url(:/imgs/cards/set/"+cardN2+".png)");

       takeBets();

       if (oneLeft())
       {
           winner = getWinner();
           if (winner!=3)
           {
               if (winner==0) ui->labelWinner->setText("Kirill");
               if (winner ==1) ui->labelWinner->setText("Vladimir");
               if (winner==2) ui->labelWinner->setText("Aleksandr");
               ui->labelPot->setText("wins "+QString::number(pot)+"!!! Yay C:");
           }
           else
               ui->labelWinner->setText(name);
           i++;
           //continue;
       }

       /* flop */
       flop();
       takeBets();
       if (oneLeft())
       {
           winner = getWinner();
           if (winner!=3)
           {
               if (winner==0) ui->labelWinner->setText("Kirill");
               if (winner ==1) ui->labelWinner->setText("Vladimir");
               if (winner==2) ui->labelWinner->setText("Aleksandr");
               ui->labelPot->setText("wins "+QString::number(pot)+"!!! Yay C:");
           }
           else
               ui->labelWinner->setText(name);
           i++;
           //continue
       }

       /* turn */
       turn();
       takeBets();
       if (oneLeft())
       {
           winner = getWinner();
           if (winner!=3)
           {
               if (winner==0) ui->labelWinner->setText("Kirill");
               if (winner ==1) ui->labelWinner->setText("Vladimir");
               if (winner==2) ui->labelWinner->setText("Aleksandr");
               ui->labelPot->setText("wins $ "+QString::number(pot)+"!!! Yay C:");
           }
           else
               ui->labelWinner->setText(name);
           i++;
           //continue
       }

       /* river */
       river();
       takeBets();


       evaluateHands();
       /*find and declare round winner*/
       maxPoints = 0;
       for (int q = 0; q<4; q++)
       {
           if (q != 3)
           {
               if (comp.at(q).round)
               {
                   if (handPoints[q] > maxPoints)
                   {
                       maxPoints = handPoints[q];
                       roundWinner = q;
                   }
               }
           }
           else
           {
               if (human.round)
               {
                   if (handPoints[q] > maxPoints)
                   {
                       maxPoints = handPoints[q];
                       roundWinner = q;
                   }
               }
           }
       }
           //    std::cout << endl;
       if (roundWinner != 3)
       {
           if (roundWinner==0) ui->labelWinner->setText("Kirill");
           if (roundWinner ==1) ui->labelWinner->setText("Vladimir");
           if (roundWinner==2) ui->labelWinner->setText("Aleksandr");
           ui->labelPot->setText("wins $ "+QString::number(pot)+"!!! Yay C:");
           // std::cout << (comp[roundWinner]).name << " wins $" << pot << " with ";
       }
       else
       {
          ui->labelWinner->setText(name);
          ui->labelPot->setText("wins $ "+QString::number(pot)+"!!! Yay C:");
          // std::cout << (*human).name << " wins $" << pot << " with ";
       }
       if (maxPoints<30)
           ui->label_5->setText("HIGH CARD");
       else if (maxPoints<50)
           ui->label_5->setText("SINGLE PAIR");
       else if (maxPoints<70)
           ui->label_5->setText("TWO PAIRS");
       else if (maxPoints<90)
           ui->label_5->setText("THREE OF A KIND");
       else if (maxPoints<110)
           ui->label_5->setText("STRAIGHT");
       else if (maxPoints<130)
           ui->label_5->setText("FLUSH");
       else if (maxPoints<150)
           ui->label_5->setText("FULL HOUSE");
       else if (maxPoints<170)
           ui->label_5->setText("FOUR OF A KIND");
       else
           ui->label_5->setText("STRAIGHT FLUSH");


       if (roundWinner==3)
           human.money += pot;
       else
           comp[roundWinner].money += pot;

       i++;
    }
}
void Table::evaluateHands()
{

}

int Table::oneLeft()   //if left one return 1
{
    int count = 0;
    for (int k = 0; k<3; k++)
        if (comp.at(k).round)
            count++;
    if (human.round)
        count++;

    if (count == 1)
        return 1;
    else
        return 0;
}

int Table::getWinner()
{
    int winner;
    for (int k = 0; k<3; k++)
        if (comp.at(k).round)
            winner = k;
    if (human.round)
        winner = 3;
    return winner;
}
int compareCards(const void *card1, const void *card2)
{
    return (*(Card *)card1).rank - (*(Card *)card2).rank;
}

int Table::getScore(Card hand[])    //определяет очки комбинации
{
    qsort(hand, 5, sizeof(Card), compareCards);
    int straight, flush, three, four, full, pairs, high;
    int k;

    straight = flush = three = four = full = pairs = high = 0;
    k = 0;

    /*checks for flush*/
    while (k<4 && hand[k].suit == hand[k + 1].suit)
        k++;
    if (k == 4)
        flush = 1;

    /* checks for straight*/
    k = 0;
    while (k<4 && hand[k].rank == hand[k + 1].rank - 1)
        k++;
    if (k == 4)
        straight = 1;

    /* checks for fours */
    for (int i = 0; i<2; i++) {
        k = i;
        while (k<i + 3 && hand[k].rank == hand[k + 1].rank)
            k++;
        if (k == i + 3) {
            four = 1;
            high = hand[i].rank;
        }
    }

    /*checks for threes and fullhouse*/
    if (!four) {
        for (int i = 0; i<3; i++) {
            k = i;
            while (k<i + 2 && hand[k].rank == hand[k + 1].rank)
                k++;
            if (k == i + 2) {
                three = 1;
                high = hand[i].rank;
                if (i == 0) {
                    if (hand[3].rank == hand[4].rank)
                        full = 1;
                }
                else if (i == 1) {
                    if (hand[0].rank == hand[4].rank)
                        full = 1;
                }
                else {
                    if (hand[0].rank == hand[1].rank)
                        full = 1;
                }
            }
        }
    }

    if (straight&&flush)
        return 170 + hand[4].rank;
    else if (four)
        return 150 + high;
    else if (full)
        return 130 + high;
    else if (flush)
        return 110;
    else if (straight)
        return 90 + hand[4].rank;
    else if (three)
        return 70 + high;

    /* checks for pairs*/
    for (k = 0; k<4; k++)
        if (hand[k].rank == hand[k + 1].rank) {
            pairs++;
            if (hand[k].rank>high)
                high = hand[k].rank;
        }

    if (pairs == 2)
        return 50 + high;
    else if (pairs)
        return 30 + high;
    else
        return hand[4].rank;
}
void Table::on_FlopButton_clicked()
{
    action = 1;
}

void Table::on_CallButton_clicked()
{
    action = 3;
}

void Table::on_CheckButton_clicked()
{
    action = 2;
}

void Table::on_pushButton_clicked()
{
    bet = ui->betEdit->toPlainText().toInt();
}
