#include <vector>

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Convert a 1D index to 2D indexes (row, column).
 * @param index The 1D index.
 * @return A pair of integers representing the row and column.
 */
std::pair<int, int> intTo2DIndexes(int index);

/**
 * @brief Convert 2D indexes (row, column) to a 1D index.
 * @param row The row index.
 * @param col The column index.
 * @return The 1D index.
 */
int indexes2DToInt(int row, int col);

#endif