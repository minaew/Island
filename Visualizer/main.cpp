#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }

    QString filePath(argv[1]);

    QApplication a(argc, argv);
    MainWindow w(filePath);
    w.show();

    return a.exec();
}
