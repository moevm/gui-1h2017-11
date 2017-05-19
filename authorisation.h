#ifndef AUTHORISATION_H
#define AUTHORISATION_H
#include <QWidget>
#include "table.h"

namespace Ui {
class Authorisation;
}

class Authorisation : public QWidget
{
    Q_OBJECT
private:

public:
    Authorisation(QWidget* parent = 0);
    ~Authorisation();
    QString n;

private slots:
    void on_playClicked();


    void on_PlayButton_clicked();

signals:
    void playClicked();
protected:
    Ui::Authorisation *ui;
    Table *table;
};

#endif // AUTHORISATION_H
