#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(liturgical_calendar);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
