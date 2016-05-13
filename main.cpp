////////////////////////////////////////////////////////////
///     Cat Fortman
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#include "Controller/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
