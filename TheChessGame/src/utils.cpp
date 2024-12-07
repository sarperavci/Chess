#include <utility>

// Function to convert an integer to 2D array indexes
std::pair<int, int> intTo2DIndexes(int index)
{
    int row = index / 8;
    int col = index % 8;
    return {row, col};
}

// Function to convert 2D array indexes to an integer
int indexes2DToInt(int row, int col)
{
    return row * 8 + col;
}
