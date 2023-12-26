/**
 * lab8.cpp
 *
 * EECS 183
 * Lab 8: File IO
 *
 * Note: you will *not* submit this file for grading
 */

#include <iostream>
#include <fstream>
#include <string>
#include "coordinates.h"
using namespace std;

int main() {
    string path = "/Users/ethankahana/Desktop/Diffindo/test2/test2/test2/";
    /*
    * open an input file for reading coordinates
    * see zyBooks Section 12.2 for an example
    * https://learn.zybooks.com/zybook/UMICHEECS183Winter2021/chapter/12/section/2
    */
     ifstream inFS;     // Input file stream
      // Try to open file
      cout << "Opening File grid_2.txt." << endl;

      inFS.open(path + "grid2.txt");
      //inFS.open(cwd / "grid2.txt");
      if (!inFS.is_open()) {
         cout << "Could not open file grid2.txt." << endl;
         return 1; // 1 indicates error
     }

    
    /*
    * open an output file for writing coordinates
    * see zyBooks Section 12.4 for an example
    * https://learn.zybooks.com/zybook/UMICHEECS183Winter2021/chapter/12/section/4
    */

    // to do - write your code here
    string output_file;
    
    cout << "middle code" << endl;
    
    // Version B1 Start
    output_file = "grid2_outputB.txt";
    // Version B1 End

    /*
    * for each coordinate in the input file, write to the output file
    * see zyBooks Section 12.3 for an example of reading until end of file
    * https://learn.zybooks.com/zybook/UMICHEECS183Winter2021/chapter/12/section/3
    * NOTE: use pass-by-refernce to read and write values
    *       do NOT call write inside the read function!
    */

    // to do - write your code here
    ofstream outFS;
    outFS.open(path + output_file);
    while (!inFS.fail()) {
        int row = 0;
        int col = 0;
        read(inFS, row, col);
        write(outFS, row, col);
    }
    
    inFS.close();
    outFS.close();
    
    
    cout << "middle 2" << endl;
    
    // Version B2 Start
    cout << "B2" << endl;
    // Version B2 End
    // Version B2 End

    return 0;
}
