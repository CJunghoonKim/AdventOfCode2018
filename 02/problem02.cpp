#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Part 1
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

int findDifference(string &a, string &b) {
  //must have same length to count
  if (a.length() - b.length() != 0) {
    return -1; // -1 is a trivial result in this case
  }
  int diff = 0;
  int index = -1;
  for (int i = 0; i < a.length(); i++) {
    diff += a[i] == b[i] ? 0 : 1;
    if (a[i] != b[i]) {
      index = i;
    }
  }
  // only return index upon finding non-trivial value (i.e. diff = 1)
  return diff == 1 ? index : -1;
}

// Part 2
string commonIDs(vector<string> &v) {
  string res, a, b; // assume there exists a result
  int k;
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      k = findDifference(v[i], v[j]);
      // if k holds a non-trivial value, solution has been found...
      if (k != 0 && k != -1) {
        a = v[i];
        b = v[j];
        goto endLoop;
      }
    }
  }
endLoop:
  // construct result with only similar characters
  res = a.substr(0, k) + b.substr(k+1, b.length()-(k+1));
  return res;
}

int main() {
  ifstream file("input.txt");
  string read;
  // Part 1
  int twos = 0;
  int threes = 0;
  // Part 2
  vector<string> input;
  while (file.is_open() && getline(file, read)) {
    // twosAndThrees(read, twos, threes); // Part 1
    input.push_back(read);
  }
  // cout << twos * threes << endl; // Part 1
  cout  << commonIDs(input) << endl; // Part 2
  // close file
  file.close();
  return 0;
}
