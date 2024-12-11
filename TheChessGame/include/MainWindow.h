#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
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
    Game *game;
    QGridLayout *boardLayout;
    QVector<QPushButton *> squares;
    QLabel *turnLabel;
    QPushButton *resetButton;

    void initializeBoard();
    void updateBoard();
    void resetBoardColors();
    void updateTurnLabel();
    void checkPawnPromotion();
    void showPromotionMenu(int row, int col, Color color);
    void highlight_valid_moves(const std::vector<int>& valid_moves, const std::vector<int>& eatable_moves);
};

#endif // MAINWINDOW_H