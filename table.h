#ifndef TABLE_H
#define TABLE_H
#include <QWidget>

namespace Ui {
  class Table;
}
class Table : public QWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent=0);
    ~Table();
    QString name="player";
    void sayHello(QString name);


private:
  Ui::Table *ui;
};

#endif // TABLE_H
