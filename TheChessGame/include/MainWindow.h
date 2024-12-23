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

/**
 * @brief The MainWindow class represents the main window of the chess application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot to handle square click events.
     */
    void handleSquareClick();

    /**
     * @brief Slot to reset the game.
     */
    void resetGame();

    /**
     * @brief Slot to handle pawn promotion.
     * @param position The position of the pawn.
     * @param pieceType The type of piece to promote to.
     */
    void handlePromotion(int position, PieceType pieceType);

private:
    Game *game; ///< Pointer to the game instance
    QGridLayout *boardLayout; ///< Layout for the chess board
    QVector<QPushButton *> squares; ///< Vector of buttons representing the squares on the board
    QLabel *turnLabel; ///< Label to display the current turn
    QPushButton *resetButton; ///< Button to reset the game
    QPushButton *rewindButton; ///< Button to rewind the last move
    QPushButton *changeButton; ///< Button to change the color scheme
    QComboBox *colorComboBox; ///< Combo box to select colors
    QString color1 = "Blue"; ///< Primary color for the board
    QString color2 = "Grey"; ///< Secondary color for the board

    /**
     * @brief Initialize the chess board.
     */
    void initializeBoard();

    /**
     * @brief Update the chess board.
     */
    void updateBoard();

    /**
     * @brief Reset the colors of the board squares.
     */
    void resetBoardColors();

    /**
     * @brief Update the turn label.
     */
    void updateTurnLabel();

    /**
     * @brief Check if a pawn needs to be promoted.
     */
    void checkPawnPromotion();

    /**
     * @brief Show the promotion menu.
     * @param row The row of the pawn.
     * @param col The column of the pawn.
     * @param color The color of the pawn.
     */
    void showPromotionMenu(int row, int col, Color color);

    /**
     * @brief Highlight valid moves and eatable moves.
     * @param valid_moves Vector of valid move positions.
     * @param eatable_moves Vector of valid eatable move positions.
     */
    void highlight_valid_moves(const std::vector<int>& valid_moves, const std::vector<int>& eatable_moves);

    /**
     * @brief Rewind the last move.
     */
    void rewind_move();

    /**
     * @brief Show the color selection dropdown.
     */
    void showColorDropdown();

    /**
     * @brief Change the color scheme of the board.
     */
    void changeColor();

    /**
     * @brief Set the color scheme of the board.
     * @param color1 The primary color.
     * @param color2 The secondary color.
     */
    void setColorScheme(const QString &color1, const QString &color2);

    /**
     * @brief End the game and declare the winner.
     * @param winner The color of the winning player.
     */
    void end_game(Color winner);

    /**
     * @brief End the game in a draw.
     */
    void end_game();
};

#endif