#include "screencontroller.h"

#include "table.h"  //экран стола
#include "authorisation.h"   //экран авторизации
#include <QGridLayout>

ScreenController::ScreenController(QWidget *parent): QWidget(parent),
    auth(new Authorisation(this)), table(new Table(this))
{
     QGridLayout *layout(new QGridLayout(this));
    //this->setFixedSize(400, 250);
    //this->setSizePolicy(300, 250);
    layout->addWidget(table, 0, 0, 1, 1);
    layout->addWidget(auth, 0, 0, 1, 1);
    table->hide();
    auth->show();

    connect(auth, SIGNAL(playClicked()), SLOT(on2game()));
   setStyleSheet(

            "*{background-color: rgba(0,128,0, 50);}"
            );
}



void ScreenController::on2game()
{
    auth->hide();
    table->show();
}
