#include "echequier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    echequier w;
    w.show();

    return a.exec();
}
