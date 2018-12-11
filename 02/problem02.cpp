#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void twosAndThrees(string &s, int &twos, int &threes) {
  map<char, int> counts;
  map<char, int>::iterator j;
  bool updateTwos = false;
  bool updateThrees = false;
  // populate count map
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    j = counts.find(c);
    if (j != counts.end()) {
      counts[c]++;
    } else {
      counts[c] = 1;
    }
  }
  // see if any characters appear twice or thrice
  for (j = counts.begin(); j != counts.end(); j++) {
    if (j->second == 2) {
      updateTwos = true;
    }
    if (j->second == 3) {
      updateThrees = true;
    }
  }
  // update
  if (updateTwos) {
    twos++;
  }
  if (updateThrees) {
    threes++;
  }
}

int main() {
  ifstream file("input.txt");
  string read;
  int twos = 0;
  int threes = 0;
  while (file.is_open() && getline(file, read)) {
    twosAndThrees(read, twos, threes);
  }
  cout << twos * threes << endl;
  // close file
  file.close();
  return 0;
}
