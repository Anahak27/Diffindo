#ifndef COORDINATES_H
#define COORDINATES_H

/**
 * coordinates.h
 *
 * EECS 183
 * Lab 8: File IO
 *
 */

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_GRID_SIZE = 8;

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects:  Returns val if val is in range [0,MAX_GRID_SIZE),
 *           otherwise returns the closest of 0 and MAX_GRID_SIZE - 1 to val.
 *
 * Example: check_range(-10) would return 0
 */
int check_range(int val);

/**
 * Requires: is stream in good state.
 * Modifies: is, row, col.
 * Effects:  Reads position in format rowcol, e.g., "1A". If it is not in
 *           that format or the operation fails, it will try to read
 *           position using format (row,col), e.g., "(1,A)"
 *           col is NOT case senstive, so reading should work for,
 *           e.g., "(1,a)" or "1a" or "(1,A)" or "1A".
 *
 * Hint:     Take advantage of the fail-state flag in an input stream.
 *
 * Example:  An input of (1,A) should result in row being 0 and col being 0.
 *           An input of 1A should result in row being 0 and col being 0.
 *
 * Note:     You will need to implement the function
 *           check_range() before implementing this one.
 */
void read(istream& is, int& row, int& col);

/**
 * Requires: os is in good state.
 *           row, col in range of [0,MAX_GRID_SIZE)
 * Modifies: os.
 * Effects:  Writes position in form (row,col) where row is in range [1, 8]
 *           and col should be an uppercase letter in range [A, H].
 */
void write(ostream& os, int row, int col);

#endif
