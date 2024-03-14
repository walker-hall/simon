#include "mainwindow.h"
#include "model.h"

#include <QApplication>

///
/// Main entry point for the SimonGame
///
/// github usernames: @frostyio , @walker-hall
///
/// https://github.com/UofU-CS3505/cs3505-assignment6-frostyio
///
/// Our special feature was adding a redemption screen so that when you die,
/// you have a chance to redeem yourself by completeing a pattern that gets significantly more
/// difficult each time you die.
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
