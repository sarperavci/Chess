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

    rewindButton = new QPushButton("Rewind Move", this);
    connect(rewindButton, &QPushButton::clicked, this, &MainWindow::rewind_move);

    rightMenuLayout->addWidget(turnLabel);
    rightMenuLayout->addWidget(resetButton);
    rightMenuLayout->addWidget(rewindButton);
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
        if ((row + col) % 2 == 0)
            button->setStyleSheet("background-color: #ADD8E6;");
        else
            button->setStyleSheet("background-color: #D3D3D3;");

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
            case PieceType::PAWN:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_pawn.svg" : ":/resources/images/black_pawn.svg";
                break;
            case PieceType::ROOK:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_rook.svg" : ":/resources/images/black_rook.svg";
                break;
            case PieceType::KNIGHT:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_knight.svg" : ":/resources/images/black_knight.svg";
                break;
            case PieceType::BISHOP:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_bishop.svg" : ":/resources/images/black_bishop.svg";
                break;
            case PieceType::QUEEN:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_queen.svg" : ":/resources/images/black_queen.svg";
                break;
            case PieceType::KING:
                pieceImagePath = (piece->get_color() == Color::WHITE) ? ":/resources/images/white_king.svg" : ":/resources/images/black_king.svg";
                break;
            default:
                pieceImagePath = "";
                break;
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
        if (piece == nullptr)
        {
            src = -1;
            return;
        }
        std::pair<std::vector<int>, std::vector<int>> valid_moves = game->get_game_board()->get_valid_moves(index);
        if (valid_moves.first.empty() && valid_moves.second.empty())
        {
            src = -1;
            return;
        }
        if (piece == nullptr || piece->get_color() != game->get_current_turn())
        {
            src = -1; // Reset source if no piece is selected or if the piece is of the opposite color
            return;
        }

        highlight_valid_moves(valid_moves.first, valid_moves.second);
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
        resetBoardColors();
    }
}

void MainWindow::highlight_valid_moves(const std::vector<int> &valid_moves, const std::vector<int> &eatable_moves)
{
    if (valid_moves.empty() && eatable_moves.empty())
    {
        return;
    }
    // to make the board colorless after selecting pieces
    for (auto square : squares)
    {
        square->setStyleSheet("background-color: none;");
    }

    // red for squares that can be eaten
    for (int pos : eatable_moves)
    {
        squares[pos]->setStyleSheet("background-color: red;");
    }

    // green for empty squares where it can go
    for (int pos : valid_moves)
    {
        Piece *piece_at_dest = game->get_game_board()->get_piece(pos);
        if (!piece_at_dest)
        {
            squares[pos]->setStyleSheet("background-color: green;");
        }
    }
}

void MainWindow::rewind_move()
{
    resetBoardColors();

    // If there is no move to rewind, reset the board
    if (!game->get_game_board()->can_rewind_move(1) || game->get_game_board()->move_history.size() == 0)
    {
        game->get_game_board()->clear_board();
        game->get_game_board()->initiate_board();
        game->set_current_turn(Color::WHITE);
        return;
    }

    game->get_game_board()->rewind_move(1);
    game->set_current_turn(game->get_current_turn() == Color::WHITE ? Color::BLACK : Color::WHITE);

    updateBoard();
    updateTurnLabel();
}

void MainWindow::resetBoardColors()
{
    for (int i = 0; i < 64; ++i)
    {
        QPushButton *button = squares[i];
        int row = 7 - (i / 8);
        int col = i % 8;

        if ((row + col) % 2 == 0)
            button->setStyleSheet("background-color: #ADD8E6;");
        else
            button->setStyleSheet("background-color: #D3D3D3;");
    }
}

void MainWindow::resetGame()
{
    game->get_game_board()->initiate_board();
    game->get_game_board()->move_history.clear();
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

    connect(queenButton, &QPushButton::clicked, [=, &dialog]()
            { handlePromotion(position, PieceType::QUEEN); dialog.accept(); });
    connect(rookButton, &QPushButton::clicked, [=, &dialog]()
            { handlePromotion(position, PieceType::ROOK); dialog.accept(); });
    connect(bishopButton, &QPushButton::clicked, [=, &dialog]()
            { handlePromotion(position, PieceType::BISHOP); dialog.accept(); });
    connect(knightButton, &QPushButton::clicked, [=, &dialog]()
            { handlePromotion(position, PieceType::KNIGHT); dialog.accept(); });

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
    gameBoard->move_history.pop_back();
    gameBoard->save_move();

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
    updateBoard();
}
