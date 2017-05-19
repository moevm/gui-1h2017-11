#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent):
    QWidget(parent), ui(new Ui::Table) {

    ui->setupUi(this);


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

void Table::startGame()
{

}
void Table::evaluateHands()
{

}
