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
               "*{color: rgba(255,240,10, 100);}"
               "*{width: 250px;}"
               "*{height: 100px;}"

            "*{background-color: rgba(0,128,0, 50);}"
               "QPushButton { "
               "  background-color: rgba(255, 153, 102, 200); "
               "  border-style: outset;"
               "  border-width: 2px;"
               "  border-radius: 10px;"
               "  border-color: beige;"
               "  font: bold 14px;"
               "  width: 3em;"
               "  padding: 6px;"
               "}"
               "QPushButton:hover {"
                 "background-color: rgba(255, 102, 0, 200);"
               "}"
               "QPushButton:pressed {"
                 "background-color: rgba(255, 0, 0, 200);"
               "}"
               "QPushButton:disabled {"
                 "background-color: rgba(204, 153, 102, 200);"
               "}"
               "QTextEdit {"
                 "background-color: rgba(102, 204, 102, 200);"
                 "  border-style: outset;"
                 "  border-width: 0px;"
                 "  border-radius: 10px;"
                 "  border-color: black;"
                 "  width: 3em;"
                 "  padding: 6px;"
               "}"
               "QLabel {"
               "background-color: rgba(102, 204, 102, 200);"
               "}"
            );
}



void ScreenController::on2game()
{
    auth->hide();
    table->show();
    table->name = auth->n;
}
