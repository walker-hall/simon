#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model& model, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onGameStart(bool);
    void onColorReceived(std::string);
    void onDisableColors(bool);
    void onProgressBarUpdate(int value, int maximum);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
