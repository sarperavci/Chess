#ifndef GAME_h
#define GAME_h

#include "GameBoard.h"

/**
 * @brief Class representing a chess game.
 */
class Game
{
private:
    GameBoard *game_board; ///< Pointer to the game board
    Color current_turn; ///< Current turn color

public:
    /**
     * @brief Constructor for the Game class.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Change the turn to the other player.
     */
    void change_turn();

    /**
     * @brief Handle a move given the row and column of the source and the destination.
     * @param row Row of the source position.
     * @param col Column of the source position.
     * @param dest Destination position.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int handle_move(int row, int col, int dest);

    /**
     * @brief Handle a move given the source and destination positions.
     * @param src Source position.
     * @param dest Destination position.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int handle_move(int src, int dest);

    /**
     * @brief Start the game.
     */
    void start_game();

    /**
     * @brief Check if the current player is in checkmate.
     * @param current_color The color of the current player.
     * @return True if the current player is in checkmate, false otherwise.
     */
    bool is_checkmate(Color current_color);

    /**
     * @brief Check if the game is in stalemate.
     * @return True if the game is in stalemate, false otherwise.
     */
    bool is_stalemate();

    /**
     * @brief Check if the current player is in check.
     * @return True if the current player is in check, false otherwise.
     */
    bool is_check();

    /**
     * @brief Update the game status.
     */
    void update_game_status();

    /**
     * @brief Get the game board.
     * @return Pointer to the game board.
     */
    GameBoard *get_game_board();

    /**
     * @brief Get the current turn color.
     * @return The color of the current turn.
     */
    Color get_current_turn();

    /**
     * @brief Set the current turn color.
     * @param color The new color for the current turn.
     */
    void set_current_turn(Color color);
};

#endif