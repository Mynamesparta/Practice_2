#include <QtGui/QApplication>
#include "mainwindow.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Matrix m(3,8);
    w.show();

    return a.exec();
}
