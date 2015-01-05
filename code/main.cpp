#include "mainwindow.h"
#include <time.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(DanceGrades);
    QApplication a(argc, argv);
    qsrand((uint)time(NULL));
    MainWindow w;
    w.show();

    return a.exec();
}
