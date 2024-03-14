#include "model.h"
#include <cstdlib>
#include <QTimer>
#include <iostream>
#include <algorithm>

///
/// \brief Model::Model
/// \param parent
///
/// Implements the methods outlined in model.h
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
Model::Model(QObject *parent)
    : QObject{parent} {
    colors = QVector<QString>();
    lossLetters = QVector<char>();

    colorIndex = -1;
    userColorIndex = 0;
    lossLetterIndex = -1;
    buttonDisplayDelay = 500;

    rng = std::default_random_engine{};
    rng.seed(time(NULL));
    dist = std::uniform_real_distribution<int>(0, 999);
}

QString Model::generateColor() {
    // dist(rng) is a random int from 0-999
    if(dist(rng) % 2 == 0)
        return "red";
    else
        return "blue";
}

void Model::onGameStart() {
    emit startGame(true);
    QTimer::singleShot(1000, this, &Model::nextLevel);
}

void Model::provideColors() {
    // display the current color
    colorIndex++;
    emit displayColor(colors[colorIndex]);

    // no more colors to be provided
    if (colorIndex + 1 >= (int)colors.size()) {
        colorsBeingDisplayed = false;
        emit disableColors(false);
        colorIndex = -1;
        return;
    }

    // timer call back to display color
    QTimer::singleShot(buttonDisplayDelay, this, &Model::provideColors);
}

void Model::nextLevel() {
    // generate a new color
    colors.push_back(generateColor());

    buttonDisplayDelay -= 20;
    if (buttonDisplayDelay <= 100)
        buttonDisplayDelay = 100;

    // update state and progress bar for next level
    emit updateProgressBar(0, colors.size());
    userColorIndex = 0;
    colorsBeingDisplayed = true;
    provideColors();
}

void Model::buttonPressed(QString color) {
    // checks if the button pressed matches
    userColorIndex++;
    if (color != colors[userColorIndex - 1]) {
        // you lose
        redemptionScreen();
        return;
    }

    emit updateProgressBar(userColorIndex, colors.size());

    // user has reached the end of the current pattern, then proceed to the next level
    if (userColorIndex == (int)colors.size()) {
        emit disableColors(true);
        QTimer::singleShot(1000, this, &Model::nextLevel);
    }
}

void Model::redemptionScreen() {
    // generate random letter pattern
    QVector<char> letterList{'y', 'o', 'u', 'l', 'q', 's', 'e'};
    QVector<char> currentLetters = letterList;
    std::shuffle(std::begin(currentLetters), std::end(currentLetters), rng);

    for (int i = 0; i < 3; i++) {
        lossLetters.push_back(currentLetters[currentLetters.size() - 1]);
        currentLetters.pop_back();
    }

    // displays the new pattern
    lossLetterIndex = -1;
    emit disableLossLetters(true); // make them unable to click
    emit doRedemption(false); // makes the redemption letters visible
    QTimer::singleShot(1000, this, &Model::provideLossScreenLetters);
}

void Model::provideLossScreenLetters(){
    // display the current letter
    lossLetterIndex++;
    emit displayLossLetter(lossLetters[lossLetterIndex]);

    // no more letters to be displayed
    if (lossLetterIndex + 1 >= (int)lossLetters.size()) {
        emit disableLossLetters(false);
        lossLetterIndex = -1;
        return;
    }

    // timer call back to display color
    QTimer::singleShot(500, this, &Model::provideLossScreenLetters);
}

void Model::lossButtonPressed(char letter) {
    lossLetterIndex++;
    if (letter != lossLetters[lossLetterIndex]) {
        // user has failed to match the redemption pattern given
        emit doRedemption(true); // hide the letter buttons
        emit startGame(false); // show the start screen
        // reset state
        colors.clear();
        lossLetters.clear();
        userColorIndex = 0;
        emit updateProgressBar(0, 0);
        return;
    }

    emit updateProgressBar(lossLetterIndex + 1, lossLetters.size());

    // user has reached the end of the current pattern, they have redeemed themself
    if (lossLetterIndex + 1 == (int)lossLetters.size()){
        emit doRedemption(true);
        QTimer::singleShot(1000, this, &Model::nextLevel);
    }
}
