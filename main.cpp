#include "mainwindow.h"
#include "model.h"

#include <QApplication>

///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
/// Main entry point for the SimonGame
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
