#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QString>
#include <random>

///
/// \brief The Model class
/// Represents the model for the SimonGame
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
class Model : public QObject
{
    Q_OBJECT

    std::default_random_engine rng;
    std::uniform_real_distribution<int> dist;

    // game screen
    QVector<QString> colors;
    bool colorsBeingDisplayed = false;
    int colorIndex;
    int userColorIndex;

    int buttonDisplayDelay;

    ///
    /// \brief Model::generateColor
    /// Generates red or blue randomly
    /// \return
    /// red or blue as a string
    ///
    QString generateColor();

    ///
    /// \brief Model::provideColors
    /// Displays each color with a .5 second delay.
    ///
    void provideColors();

    // loss screen
    QVector<char> lossLetters;
    int lossLetterIndex;

    ///
    /// \brief Model::redemptionScreen
    /// Displays a redemption screen with a random list of letters.
    ///
    void redemptionScreen();

    ///
    /// \brief provideLossScreenLetters
    ///
    void provideLossScreenLetters();

public:
    ///
    /// \brief Model::Model
    /// Main model for the game.
    /// \param parent
    ///
    explicit Model(QObject *parent = nullptr);

signals:
    ///
    /// \brief startGame
    /// Signals onGameStart.
    /// \param gameHasStarted
    /// false if the game has ended, true if the game is beginning
    ///
    void startGame(bool gameHasStarted);

    // game screen

    ///
    /// \brief displayColor
    /// Signals onColorRecieved.
    /// \param color
    /// red or blue determines which button is lit
    ///
    void displayColor(QString color);

    ///
    /// \brief disableColors
    /// Signals onDisableColors.
    /// \param disabled
    /// true if you can't click, false if you can
    ///
    void disableColors(bool disabled);

    ///
    /// \brief updateProgressBar
    /// Signals onProgressBarUpdate.
    /// \param value
    /// Current value of the progress bar
    /// \param maximum
    /// Maximum value of the progress bar
    ///
    void updateProgressBar(int value, int maximum);

    // loss screen

    ///
    /// \brief displayLossLetter
    /// Signals onLossLetterRecieved
    /// \param letter
    /// letter to be displayed
    ///
    void displayLossLetter(char letter);

    ///
    /// \brief disableLossLetters
    /// Signals onDisableLossLetters.
    /// \param disabled
    /// true if letters are being disabled, false if not
    void disableLossLetters(bool disabled);

    ///
    /// \brief doRedemption
    /// Signals onRedemption.
    /// \param hidden
    /// true if the redemption buttons are hidden, false if they are visible
    ///
    void doRedemption(bool hidden);

public slots:
    ///
    /// \brief Model::onGameStart
    /// Starts the game and proceeds to the first level
    ///
    void onGameStart();

    // game screen

    ///
    /// \brief Model::nextLevel
    /// Proceeds to the next level by adding another color and redisplaying the colors.
    ///
    void nextLevel();

    ///
    /// \brief Model::buttonPressed
    /// Handles a color button being pressed.
    /// \param color
    /// Color of the button being pressed.
    ///
    void buttonPressed(QString color);

    // loss screen
    void lossButtonPressed(char letter);
};

#endif // MODEL_H
