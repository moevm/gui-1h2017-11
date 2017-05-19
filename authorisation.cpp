#include "authorisation.h"
#include "ui_authorisation.h"

Authorisation::Authorisation(QWidget *parent):
    QWidget(parent), ui(new Ui::Authorisation)
{
     ui->setupUi(this);
     table=new Table(parent);
}

Authorisation::~Authorisation(){
    delete ui;
}
void Authorisation::on_playClicked() {
    n=ui->textEdit->toPlainText();
    //ui->label_2->setText(n);

    emit playClicked();
}

void Authorisation::on_PlayButton_clicked()
{
    table->getName(ui->textEdit->toPlainText());
    table->show();
    this->hide();

}
