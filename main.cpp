#include <QApplication>
#include <controller.h>
#include <QGraphicsView>
#include "mainwindow.h"
#include <scene.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
