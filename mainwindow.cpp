#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <QTimer>

///
/// \brief MainWindow::MainWindow
/// \param model
/// \param parent
///
/// Implements the methods outlined in mainwindow.h
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
///
MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // hide everything that's not needed
    onRedemption(true);
    onGameStart(false);

    //---- view -> model

    connect(ui->startButton,
        &QPushButton::clicked,
        &model,
        &Model::onGameStart);

    // simon buttons
    connect(ui->blueButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.buttonPressed("blue"); });

    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.buttonPressed("red"); });

    // loss screen buttons
    connect(ui->yButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('y'); });

    connect(ui->oButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('o'); });

    connect(ui->uButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('u'); });

    connect(ui->lButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('l'); });

    connect(ui->oButton2,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('q'); });

    connect(ui->sButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('s'); });

    connect(ui->eButton,
            &QPushButton::clicked,
            &model,
            [&model]{ model.lossButtonPressed('e'); });

    //---- model -> view

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

    // loss screen buttons
    connect(&model,
            &Model::doRedemption,
            this,
            &MainWindow::onRedemption);

    connect(&model,
            &Model::displayLossLetter,
            this,
            &MainWindow::onLossLetterRecieved);

    connect(&model,
            &Model::disableLossLetters,
            this,
            &MainWindow::onDisableLossLetters);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRedemption(bool hidden) {
    // changes all the loss letters to appear or hide and the colored buttons to do the inverse
    ui->yButton->setVisible(!hidden);
    ui->oButton->setVisible(!hidden);
    ui->uButton->setVisible(!hidden);
    ui->lButton->setVisible(!hidden);
    ui->oButton2->setVisible(!hidden);
    ui->sButton->setVisible(!hidden);
    ui->eButton->setVisible(!hidden);
    ui->redButton->setVisible(hidden);
    ui->blueButton->setVisible(hidden);
}

void MainWindow::onGameStart(bool hasGameStarted)
{
    // changes the visibility of the colored buttons and the progress bar, along with the start screen to the inverse
    ui->redButton->setVisible(hasGameStarted);
    ui->blueButton->setVisible(hasGameStarted);
    ui->progressBar->setVisible(hasGameStarted);
    ui->startButton->setVisible(!hasGameStarted);
    ui->startLabel->setVisible(!hasGameStarted);
}

void MainWindow::onColorReceived(QString color) {
    // selects the correct color and button reference
    QString newColor;
    QPushButton *button;
    if (color == "blue") {
        newColor = "rgb(0, 0, 255)";
        button = ui->blueButton;
    } else {
        newColor = "rgb(255, 0, 0)";
        button = ui->redButton;
    }

    // updates the button and color
    QString stylesheet = "QPushButton { background-color: " + newColor + "; color: white; }";
    QString oldStylesheet = button->styleSheet();
    button->setStyleSheet(stylesheet);

    // change it back
    QTimer::singleShot(150, this, [button, oldStylesheet]{ button->setStyleSheet(oldStylesheet); });
}

void MainWindow::onDisableColors(bool disabled) {
    ui->redButton->setEnabled(!disabled);
    ui->blueButton->setEnabled(!disabled);
}

void MainWindow::onProgressBarUpdate(int value, int maximum) {
    ui->progressBar->setValue(value);
    ui->progressBar->setMaximum(maximum);
}

void MainWindow::onLossLetterRecieved(char letter) {
    // gathers the correct button reference depending on the letter
    QPushButton *button;
    switch (letter) {
    case 'y':
        button = ui->yButton;
        break;
    case 'o':
        button = ui->oButton;
        break;
    case 'u':
        button = ui->uButton;
        break;
    case 'l':
        button = ui->lButton;
        break;
    case 'q':
        button = ui->oButton2;
        break;
    case 's':
        button = ui->sButton;
        break;
    case 'e':
        button = ui->eButton;
        break;
    default:
        button = ui->yButton;
    }

    // updates the color
    QString stylesheet = "QPushButton { background-color: rgb(171, 195, 237); color: white; }";
    QString oldStylesheet = button->styleSheet();
    button->setStyleSheet(stylesheet);

    // reverts it back
    QTimer::singleShot(150, this, [button, oldStylesheet]{ button->setStyleSheet(oldStylesheet); });
}

void MainWindow::onDisableLossLetters(bool disabled){
    ui->yButton->setEnabled(!disabled);
    ui->oButton->setEnabled(!disabled);
    ui->uButton->setEnabled(!disabled);
    ui->lButton->setEnabled(!disabled);
    ui->oButton2->setEnabled(!disabled);
    ui->sButton->setEnabled(!disabled);
    ui->eButton->setEnabled(!disabled);
}
