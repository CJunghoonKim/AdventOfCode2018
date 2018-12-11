#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool duplicate(map<int, int> &m, int n) {
  map<int, int>::iterator i = m.find(n);
  if (i != m.end()) {
    m[n]++;
    if (m[n] > 1) {
      cout << n << endl;
      return true;
    }
  } else {
    m[n] = 1;
  }
  return false;
}

int main() {
  ifstream file("input.txt");
  int freq = 0;
  string read;
  map<int, int> freqs;
  vector<string> input;
  int n;
  bool found = false;
  // loop through input
  while(file.is_open() && getline(file, read)) {
    input.push_back(read); // record input for later search
    n = atoi(read.substr(1,read.length()-1).c_str());
    freq += read[0] == '+' ? n : -1 * n;
    if (duplicate(freqs, freq)) {
      break;
    }
  }
  // cout << freq << endl; PART I
  // close
  file.close();
  
  // find duplicates
  while(!found) {
    for (int i = 0; i < input.size(); i++) {
      n = atoi(input[i].substr(1,input[i].length()-1).c_str());
      freq += input[i][0] == '+' ? n : -1 * n;
      if (duplicate(freqs, freq)) {
        found = true;
        break;
      }
    }
  }
  return 0;
}
