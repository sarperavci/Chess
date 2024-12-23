#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

/**
 * @brief Class representing a Knight chess piece.
 */
class Knight : public Piece
{
public:
    /**
     * @brief Constructor for the Knight class.
     * @param position Initial position of the Knight.
     * @param color Color of the Knight.
     */
    Knight(int position, Color color);

    /**
     * @brief Get the current position of the Knight.
     * @return The position of the Knight.
     */
    int get_position() override;

    /**
     * @brief Get the color of the Knight.
     * @return The color of the Knight.
     */
    Color get_color() override;

    /**
     * @brief Move the Knight to a new position.
     * @param destination The new position of the Knight.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (Knight).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the Knight.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the Knight.
     * @return A vector of valid eatable move positions.
     */
    std::vector<int> get_eatable_moves() override;

    /**
     * @brief Check if a move is blocked.
     * @param destination The destination position.
     * @param is_eat True if the move involves capturing an enemy piece, false otherwise.
     * @param board The current state of the board.
     * @return True if the move is blocked, false otherwise.
     */
    bool is_move_blocked(int destination, bool is_eat, Piece **board) override;
};

#endif