#include "authorisation.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Authorisation w;
    w.show();

    return a.exec();
}
