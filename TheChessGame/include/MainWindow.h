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
    Game *game;
    QGridLayout *boardLayout;
    QVector<QPushButton *> squares;
    QLabel *turnLabel;
    QPushButton *resetButton;
    QPushButton *rewindButton;
    QPushButton *changeButton;
    QComboBox *colorComboBox;
    QString color1 = "Blue";
    QString color2 = "Grey";

    void initializeBoard();
    void updateBoard();
    void resetBoardColors();
    void updateTurnLabel();
    void checkPawnPromotion();
    void showPromotionMenu(int row, int col, Color color);
    void highlight_valid_moves(const std::vector<int>& valid_moves, const std::vector<int>& eatable_moves);
    void rewind_move();
    void showColorDropdown();
    void changeColor();
    void setColorScheme(const QString &color1, const QString &color2);
};

#endif // MAINWINDOW_H