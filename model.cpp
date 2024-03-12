#include "model.h"
#include <cstdlib>
#include <QTimer>
#include <iostream>

Model::Model(QObject *parent)
    : QObject{parent}
{
    srand(time(NULL)+rand());
    colors = std::vector<std::string>();
}

std::string generateColor() {

    if(std::rand() % 2 == 0)
        return "red";
    else
        return "blue";
}

void Model::onGameStart()
{
    emit startGame(true);
    QTimer::singleShot(1000, this, &Model::nextLevel);
}

void Model::drawColors(){
    colorIndex++;
    emit displayColor(colors[colorIndex]);

    if (colorIndex + 1 >= (int)colors.size()) {
        colorsBeingDisplayed = false;
        emit disableColors(false);
        colorIndex = -1;
        return;
    }

    // timer call back to display color
    QTimer::singleShot(500, this, &Model::drawColors);
}

void Model::nextLevel(){
    colors.push_back(generateColor());

    emit updateProgressBar(0, colors.size());
    userColorIndex = 0;
    colorsBeingDisplayed = true;
    emit disableColors(true);
    drawColors();
}

void Model::buttonPressed(std::string color) {
    userColorIndex++;
    if (color != colors[userColorIndex - 1]) {
        // you lose
        colors.clear();
        userColorIndex = 0;
        emit updateProgressBar(0, 0);
        emit startGame(false);
        return;
    }

    emit updateProgressBar(userColorIndex, colors.size());

    if (userColorIndex == (int)colors.size())
        QTimer::singleShot(1000, this, &Model::nextLevel);
}

void Model::blueButtonPressed() {
    buttonPressed("blue");
}

void Model::redButtonPressed() {
    buttonPressed("red");
}
