#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
#include <QComboBox>
#include "Game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void handleSquareClick();

    void resetGame();

    void handlePromotion(int position, PieceType pieceType);

private:
    Game *game;                     ///< Pointer to the game instance
    QGridLayout *boardLayout;       ///< Layout for the chess board
    QVector<QPushButton *> squares; ///< Vector of buttons representing the squares on the board
    QLabel *turnLabel;              ///< Label to display the current turn
    QPushButton *resetButton;       ///< Button to reset the game
    QPushButton *rewindButton;      ///< Button to rewind the last move
    QPushButton *changeButton;      ///< Button to change the color scheme
    QComboBox *colorComboBox;       ///< Combo box to select colors
    QString color1 = "Blue";        ///< Primary color for the board
    QString color2 = "Grey";        ///< Secondary color for the board

    void initializeBoard();

    void updateBoard();

    void resetBoardColors();

    void updateTurnLabel();

    void checkPawnPromotion();

    void showPromotionMenu(int row, int col, Color color);

    void highlight_valid_moves(const std::vector<int> &valid_moves, const std::vector<int> &eatable_moves);

    void rewind_move();

    void showColorDropdown();

    void changeColor();

    void setColorScheme(const QString &color1, const QString &color2);

    void end_game(Color winner);

    void end_game();
};

#endif