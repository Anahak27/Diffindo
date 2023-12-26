//
//  main.cpp
//  test
//
//  Created by Ethan Kahana on 12/22/23.
//

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

double sum (const vector<double> &data) {
  double total = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    total += data[i];
  }
  return total;
}

int main() {
  vector<double> data;
  // Version A1 Start
  cout << "version A1" << endl;
  data.push_back(10);
  data.push_back(20);
  // Version A1 End
    
  cout << "middle code" << endl;
    
  // Version B1 Start
  cout << "Version B1" << endl;
  data.push_back(3);
  data.push_back(5);
  // Version B1 End
  cout << "sum(data) = " << sum(data) << endl;
  
  // Version A2 Start
  cout << "version A2" << endl;
  // Version A2 End
    
  cout << "middle code 2" << endl;
    
  // Version B2 Start
  cout << "version B2" << endl;
  // Version B2 End
    
  cout << "common code END" << endl;
  return 0;
}
