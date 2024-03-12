#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>
#include <string>

class Model : public QObject
{
    Q_OBJECT

    std::vector<std::string> colors;
    bool colorsBeingDisplayed = false;
    int colorIndex = -1;
    int userColorIndex = 0;

    void buttonPressed(std::string color);
public:
    explicit Model(QObject *parent = nullptr);

signals:
    void startGame(bool gameHasStarted);
    void displayColor(std::string color);
    void disableColors(bool disabled);
    void updateProgressBar(int value, int maximum);

public slots:
    void onGameStart();
    void drawColors();
    void nextLevel();
    void blueButtonPressed();
    void redButtonPressed();
};

#endif // MODEL_H
