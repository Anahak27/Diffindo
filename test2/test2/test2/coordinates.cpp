/**
 * coordinates.cpp
 *
 * EECS 183
 * Lab 8: File IO
 *
 * Ethan
 * ekahana
 *
 * <#Description#>
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "coordinates.h"
using namespace std;

// to do - complete all functions in coordinates.h
// check_range, read, write

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects:  Returns val if val is in range [0,MAX_GRID_SIZE),
 *           otherwise returns the closest of 0 and MAX_GRID_SIZE - 1 to val.
 *
 * Example: check_range(-10) would return 0
 */
int check_range(int val) {
    //TODO
    
    if (val < MAX_GRID_SIZE && val >= 0) {
        return val;
    }
    else if (val < 0){
        val = 0;
        return val;
    }
    else {
        val = MAX_GRID_SIZE - 1;
        return val;
    }
}


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
void read(istream& is, int& row, int& col) {
    //TODO
    
    int coordinate1 = 0;
    char coordinate2 = ' ';
    int newCol = 0;
    char junk = ' ';
    //first assume that they entered in number and letter
    //side by side (i.e. 3F)
    is >> coordinate1 >> coordinate2;
    
    //check if it is in a fail state. This would mean that coordinates are
    //enetered in via the second format, i.e. (3, F)
    if(is.fail()) {
        //clear fail state
        is.clear();
        
        //Read other way of inputting coordinates: i.e. (3, F)
        is >> junk >> coordinate1 >> junk >> coordinate2 >> junk;
        
    }
    
    //make all lower case upper case for consistancy
    coordinate2 = static_cast<char>(toupper(coordinate2));
    
    // Check range of row value, assign this value to row
    if (check_range(coordinate1) > 0 && check_range(coordinate1) < 7)
        row = check_range(coordinate1) - 1;
    else
        row = check_range(coordinate1);
    
    newCol = static_cast<int>(coordinate2) - 65;
    col = check_range(newCol);
    
    
    return;
}


/**
 * Requires: os is in good state.
 *           row, col in range of [0,MAX_GRID_SIZE)
 * Modifies: os.
 * Effects:  Writes position in form (row,col) where row is in range [1, 8]
 *           and col should be an uppercase letter in range [A, H].
 */
void write(ostream& os, int row, int col) {
    //TODO
    char letter = ' ';
    if(!os.fail()) {
        row = row + 1;
        col = col + 65;
        letter = static_cast<char>(col);
        os << "(" << row << ", " << letter << ")" << endl;
    }
    
    return;
}
