#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent):
    QWidget(parent), ui(new Ui::Table) {
    ui->setupUi(this);
    QPixmap blind(":/imgs/chips/small/chip_bigblind_flat.png");
    ui->labelEl->setPixmap(blind);

    sayHello(name);

}

Table::~Table() {
  delete ui;
}

void Table::sayHello(QString name)
{
    ui->label->setText("Hello, "+name);
}
