#include "MainWindow.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), game(new Game())
{
    QWidget *centralWidget = new QWidget(this);
    QWidget *rightMenu = new QWidget(this);
    QVBoxLayout *rightMenuLayout = new QVBoxLayout(rightMenu);

    boardLayout = new QGridLayout();
    game->get_game_board()->initiate_board();
    initializeBoard();

    turnLabel = new QLabel(this);
    resetButton = new QPushButton("Reset Game", this);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    rightMenuLayout->addWidget(turnLabel);
    rightMenuLayout->addWidget(resetButton);
    rightMenu->setLayout(rightMenuLayout);
    rightMenu->setFixedWidth(200);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(boardLayout);
    mainLayout->addWidget(rightMenu);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    updateTurnLabel();
}

MainWindow::~MainWindow()
{
    delete game;
}

void MainWindow::initializeBoard()
{
    for (int i = 0; i < 64; ++i)
    {
        QPushButton *button = new QPushButton(this);
        button->setFixedSize(80, 80);
        squares.append(button);
        connect(button, &QPushButton::clicked, this, &MainWindow::handleSquareClick);

        int row = 7 - (i / 8);
        int col = i % 8;
        boardLayout->addWidget(button, row, col);
    }

    updateBoard();
}

void MainWindow::updateBoard()
{
    GameBoard *gameBoard = game->get_game_board();

    for (int i = 0; i < 64; ++i)
    {
        int row = i / 8;
        int col = i % 8;
        Piece *piece = gameBoard->get_piece(row, col);

        QString pieceImagePath;
        if (piece != nullptr)
        {
            switch (piece->get_piece_type())
            {
            case PieceType::PAWN: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_pawn.svg" : ":/resources/images/black_pawn.svg"; break;
            case PieceType::ROOK: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_rook.svg" : ":/resources/images/black_rook.svg"; break;
            case PieceType::KNIGHT: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_knight.svg" : ":/resources/images/black_knight.svg"; break;
            case PieceType::BISHOP: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_bishop.svg" : ":/resources/images/black_bishop.svg"; break;
            case PieceType::QUEEN: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_queen.svg" : ":/resources/images/black_queen.svg"; break;
            case PieceType::KING: pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_king.svg" : ":/resources/images/black_king.svg"; break;
            default: pieceImagePath = ""; break;
            }
        }
        else
        {
            pieceImagePath = "";
        }

        if (!pieceImagePath.isEmpty())
        {
            QSvgRenderer renderer(pieceImagePath);
            QPixmap pixmap(80, 80);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            renderer.render(&painter);
            squares[i]->setIcon(QIcon(pixmap));
            squares[i]->setIconSize(QSize(80, 80));
        }
        else
        {
            squares[i]->setIcon(QIcon());
        }
    }
}

void MainWindow::handleSquareClick()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int index = squares.indexOf(clickedButton);

    static int src = -1; // To track source square
    if (src == -1)
    {
        src = index; // First click (source)
        int row = src / 8;
        int col = src % 8;
        Piece *piece = game->get_game_board()->get_piece(row, col);
        if (piece == nullptr || piece->get_color() != game->get_current_turn())
        {
            src = -1; // Reset source if no piece is selected or if the piece is of the opposite color
            return;
        }
    }
    else
    {
        int dest = index; // Second click (destination)
        int src_1d = src / 8 * 8 + src % 8;
        int dest_1d = dest / 8 * 8 + dest % 8;

        if (game->handle_move(src_1d, dest_1d))
        {
            updateBoard();
            updateTurnLabel();

            if (game->is_checkmate(game->get_current_turn()))
            {
                QMessageBox::information(this, "Game Over", "Checkmate!");
            }
            else if (game->is_stalemate())
            {
                QMessageBox::information(this, "Game Over", "Stalemate!");
            }
            else if (game->is_draw())
            {
                QMessageBox::information(this, "Game Over", "Draw!");
            }
            else if (game->is_check())
            {
                QMessageBox::information(this, "Check", "Check!");
            }

            checkPawnPromotion();
        }
        src = -1; // Reset source square
    }
}

void MainWindow::resetGame()
{
    game->get_game_board()->initiate_board();
    game->set_current_turn(Color::WHITE);
    updateBoard();
    updateTurnLabel();
}

void MainWindow::updateTurnLabel()
{
    turnLabel->setText(QString("Current turn: %1").arg(game->get_current_turn() == Color::WHITE ? "White" : "Black"));
}

void MainWindow::checkPawnPromotion()
{
    GameBoard *gameBoard = game->get_game_board();
    const int whitePawnRow = 0;
    const int blackPawnRow = 7;

    for (int col = 0; col < 8; ++col)
    {
        Piece *whitePawn = gameBoard->get_piece(whitePawnRow, col);
        if (whitePawn && whitePawn->get_piece_type() == PieceType::PAWN)
        {
            showPromotionMenu(whitePawnRow, col, Color::BLACK);
            return;
        }

        Piece *blackPawn = gameBoard->get_piece(blackPawnRow, col);
        if (blackPawn && blackPawn->get_piece_type() == PieceType::PAWN)
        {
            showPromotionMenu(blackPawnRow, col, Color::WHITE);
            return;
        }
    }
}

void MainWindow::showPromotionMenu(int row, int col, Color color)
{
    QString colorStr = (color == Color::WHITE) ? "white" : "black";
    int position = row * 8 + col;
    
    QDialog dialog(this);
    QHBoxLayout layout(&dialog);

    QPushButton *queenButton = new QPushButton(this);
    QPushButton *rookButton = new QPushButton(this);
    QPushButton *bishopButton = new QPushButton(this);
    QPushButton *knightButton = new QPushButton(this);

    queenButton->setIcon(QIcon(QString(":/resources/images/%1_queen.svg").arg(colorStr)));
    queenButton->setIconSize(QSize(80, 80));
    rookButton->setIcon(QIcon(QString(":/resources/images/%1_rook.svg").arg(colorStr)));
    rookButton->setIconSize(QSize(80, 80));
    bishopButton->setIcon(QIcon(QString(":/resources/images/%1_bishop.svg").arg(colorStr)));
    bishopButton->setIconSize(QSize(80, 80));
    knightButton->setIcon(QIcon(QString(":/resources/images/%1_knight.svg").arg(colorStr)));
    knightButton->setIconSize(QSize(80, 80));

    connect(queenButton, &QPushButton::clicked, [=, &dialog]() { handlePromotion(position, PieceType::QUEEN); dialog.accept(); });
    connect(rookButton, &QPushButton::clicked, [=, &dialog]() { handlePromotion(position, PieceType::ROOK); dialog.accept(); });
    connect(bishopButton, &QPushButton::clicked, [=, &dialog]() { handlePromotion(position, PieceType::BISHOP); dialog.accept(); });
    connect(knightButton, &QPushButton::clicked, [=, &dialog]() { handlePromotion(position, PieceType::KNIGHT); dialog.accept(); });

    layout.addWidget(queenButton);
    layout.addWidget(rookButton);
    layout.addWidget(bishopButton);
    layout.addWidget(knightButton);

    dialog.setLayout(&layout);
    dialog.exec();
}

void MainWindow::handlePromotion(int position, PieceType pieceType)
{
    GameBoard *gameBoard = game->get_game_board();
    gameBoard->promote_pawn(position, gameBoard->get_piece(position), pieceType);
    updateBoard();
}