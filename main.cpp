#include "ProcessModelWithQt3D.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProcessModelWithQt3D w;
    w.show();
    return a.exec();
}
