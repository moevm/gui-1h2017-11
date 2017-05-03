#include "authorisation.h"
#include "ui_authorisation.h"

Authorisation::Authorisation(QWidget *parent):
    QWidget(parent), ui(new Ui::Authorisation)
{
    ui->setupUi(this);

    connect(ui->PlayButton, SIGNAL(clicked()), SLOT(on_playClicked()));
    //connect(ui->helpButton, SIGNAL(clicked()), SLOT(on_helpClicked()));


}

Authorisation::~Authorisation(){
    delete ui;
}
void Authorisation::on_playClicked() {
  emit playClicked();
}
