#include "theapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    theapp w;
    w.show();
    return a.exec();
}
