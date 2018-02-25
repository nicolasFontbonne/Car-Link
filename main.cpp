#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    const QIcon appIcon =  QIcon(":/images/icone.png");
    a.setWindowIcon(appIcon);
    w.show();

    return a.exec();
}
