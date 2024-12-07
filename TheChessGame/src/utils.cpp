#include <utility>

// Function to convert an integer to 2D array indexes
std::pair<int, int> intTo2DIndexes(int index) {
    int row = 7 - (index / 8);
    int col = index % 8;
    return std::make_pair(row, col);
}

// Function to convert 2D array indexes to an integer
int indexes2DToInt(int row, int col) {
    return (7 - row) * 8 + col;
}