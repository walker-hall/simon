#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <QTimer>

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // view -> model

    connect(ui->startButton,
        &QPushButton::clicked,
        &model,
        &Model::onGameStart);

    connect(ui->blueButton,
            &QPushButton::clicked,
            &model,
            &Model::blueButtonPressed);

    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &Model::redButtonPressed);

    // model -> view

    connect(&model,
            &Model::startGame,
            this,
            &MainWindow::onGameStart);

    connect(&model,
            &Model::displayColor,
            this,
            &MainWindow::onColorReceived);

    connect(&model,
            &Model::disableColors,
            this,
            &MainWindow::onDisableColors);

    connect(&model,
            &Model::updateProgressBar,
            this,
            &MainWindow::onProgressBarUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGameStart(bool hasGameStarted)
{
    ui->startButton->setEnabled(!hasGameStarted);
    ui->redButton->setEnabled(hasGameStarted);
    ui->blueButton->setEnabled(hasGameStarted);
}

void MainWindow::onColorReceived(std::string color) {
    QString newColor;
    QPushButton *button;
    if (color == "blue") {
        newColor = "rgb(0, 0, 255)";
        button = ui->blueButton;
    } else {
        newColor = "rgb(255, 0, 0)";
        button = ui->redButton;
    }
    QString stylesheet = "QPushButton { background-color: " + newColor + "; color: white; }";
    QString oldStylesheet = button->styleSheet();
    button->setStyleSheet(stylesheet);

    QTimer::singleShot(150, this, [button, oldStylesheet]{ button->setStyleSheet(oldStylesheet); });
}

void MainWindow::onDisableColors(bool disabled){

    ui->redButton->setEnabled(!disabled);
    ui->blueButton->setEnabled(!disabled);
}

void MainWindow::onProgressBarUpdate(int value, int maximum){

    ui->progressBar->setValue(value);
    ui->progressBar->setMaximum(maximum);
}
