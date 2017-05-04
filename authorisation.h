#ifndef AUTHORISATION_H
#define AUTHORISATION_H
#include <QWidget>

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


signals:
    void playClicked();
protected:
    Ui::Authorisation *ui;
};

#endif // AUTHORISATION_H
