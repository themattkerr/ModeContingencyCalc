#include "maincontingencywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainContingencyWindow w;
    w.show();

    return a.exec();
}
