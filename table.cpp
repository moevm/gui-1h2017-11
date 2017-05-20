#include "table.h"
#include "ui_table.h"
#include <QStyle>
#include "human.h"
#include "computer.h"

Table::Table(QWidget *parent):
    QWidget(parent), ui(new Ui::Table) {

    Computer c;
    c.money = 1000;
    c.goodToGo= 0;
    c.playing = 1;
    Card car;
    car.rank=0;
    car.suit=0;
    c.playerCards.push_back(car);
    c.playerCards.push_back(car);
    for (int i=0; i<3; i++)
        comp.push_back(c);
    human.money=1000;
    human.goodToGo =0;
    human.playing=1;
    human.setCards(car, car);
    pot =20;


    ui->setupUi(this);
    ui->BankLabel->setText(QString::number(pot));
    gameover=new GameOver(parent);

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
 void Table::getBet()
 {
     bet = ui->betEdit->toPlainText().toInt();
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


int Table::takeBets()
{
    betOn = 0;
    for (int k = 0; k<3; k++)
        comp[k].goodToGo = 0;
    human.goodToGo = 0;

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
                if (betOn)
                {
                    ui->FlopButton->setEnabled(true);
                    ui->CallButton->setEnabled(true);
                }
                else
                {
                    ui->FlopButton->setEnabled(true);
                    ui->CheckButton->setEnabled(true);
                    ui->CallButton->setEnabled(true);

                }
                if (action == 1)
                {
                    human.round = 0;
                }
                else
                {
                    if (action == 2)
                        continue;
                    else
                    {
                        if (betOn)
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
    if (betOn&& playersToBet())
    {
        for (int k = bind + 1; k<bind + 5; k++)
        {
            if (k % 4 == 3)
            {
                if (human.round&&human.goodToGo == 0)
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
            else
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
    ui->CheckButton->setEnabled(false);
    ui->FlopButton->setEnabled(false);
    ui->CallButton->setEnabled(false);
    ui->pushButton->setEnabled(false);


    int i = 0;
  //  while (this->playersLeft()>1)
   // {
        bind = i % 4;
        /* starting default values*/
        for (int z = 0; z<3; z++)
        {
            if (comp.at(z).money<1)
            {
               /* Computer c;
                c.playing=0;
                c.round = 0;
                c.money = comp.at(z).money;
                c.goodToGo = comp.at(z).goodToGo;
                c.playerCards = comp.at(z).playerCards;

                comp.value(z, c);*/
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
            if (z!=3)
            {
                if (comp.at(z).playing)
                {
                   /* Computer c ;
                    c.goodToGo = comp.at(z).goodToGo;
                    c.money = comp.at(z).money;
                    c.playerCards = comp.at(z).playerCards;
                    c.playing = comp.at(z).playing;
                    c.round = 1;

                    comp.value(z,c);*/
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
                /*Computer c ;

                c.goodToGo = comp.at(bind).goodToGo;
                c.money = comp.at(bind).money;
                c.money -= 20;
                c.playerCards = comp.at(bind).playerCards;
                c.playing = comp.at(bind).playing;
                c.round = comp.at(bind).round;

                comp.value(bind,c);*/
                comp[bind].money-=20;
            }
            else
            {
               /* Computer c ;

                c.goodToGo = comp.at(bind).goodToGo;
                c.money = comp.at(bind).money;
                c.playerCards = comp.at(bind).playerCards;
                c.playing = 0;
                c.round = comp.at(bind).round;

                comp.value(bind,c);*/
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


  //      i++;
   // }



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
