#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

///
/// \brief The MainWindow class
/// Represents the view for the SimonGame
///
/// By Walker Hall and Zak Holt
/// March 14, 2024
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model& model, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    ///
    /// \brief onGameStart
    /// Changes the visibility of the start and color buttons to start/end the game.
    /// Connected to the startGame signal.
    /// \param gameHasStarted
    /// false if the game has ended, true if the game is beginning
    ///
    void onGameStart(bool hasGameStarted);

    // game screen

    ///
    /// \brief onColorReceived
    /// Lights up the button of the given color.
    /// Connected to the displayColor signal.
    /// \param color
    /// red or blue determines which button is lit
    ///
    void onColorReceived(QString color);

    ///
    /// \brief onDisableColors
    /// Disables clickability of the color buttons.
    /// Connected to the disableColors signal.
    /// \param disabled
    /// true if you can't click, false if you can
    ///
    void onDisableColors(bool disabled);

    ///
    /// \brief onProgressBarUpdate
    /// Updates the progress bar with the given values.
    /// Connected to the updateProgressBar signal.
    /// \param value
    /// Current value of the progress bar
    /// \param maximum
    /// Maximum value of the progress bar
    ///
    void onProgressBarUpdate(int value, int maximum);

    // loss screen

    ///
    /// \brief onLossLetterRecieved
    /// Lights up button of the given letter on the redemption screen.
    /// Connected to the displayLossLetter signal.
    /// \param letter
    /// letter to be displayed
    void onLossLetterRecieved(char letter);

    ///
    /// \brief onDisableLossLetters
    /// Disables or enables the loss letters being clicked.
    /// Connected to the disableLossLetters signal.
    /// \param disabled
    /// true if letters are being disabled, false if not
    ///
    void onDisableLossLetters(bool disabled);

    ///
    /// \brief onRedemption
    /// Changes the visibility of the redemption buttons and allows for the player to redeem themself.
    /// Connected to the doRedemption signal.
    /// \param hidden
    /// true if the redemption buttons are hidden, false if they are visible
    ///
    void onRedemption(bool hidden);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
