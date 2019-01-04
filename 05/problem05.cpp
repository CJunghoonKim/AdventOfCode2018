#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// forward declarations
void partOne(string filename);
void partTwo(string filename);

void reduce(string &l, int &i); // reduction of input through recursion

int main() {
  partOne("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;
  int size;  // input length
  int i = 0; // input iterator

  getline(file, line); // input is 1 line
  size = line.size();  // assign size
  file.close(); // close file
  /*
    1. dabA[cC]aCBAcCcaDA   i = 4
    2. dab[Aa]CBAcCcaDA     i = 3
    3. dabCBA[cC]caDA       i = 6
    4. dabCBAcaDA           i = END
    --> string length may change every iteration of while-loop
  */
  while (i < line.size()-1) {
    reduce(line, i);
    i++;
  }
  cout << "Part I: " << line.size() << endl;
}

void reduce(string &l, int &i) {
  // may assume only valid position i will be inputted...
  // base case
  if (abs(l[i]-l[i-1]) != 32 || i == l.size()-1) {
    return;
  }
  // recursive case at i = 0
  if (i == 0) {
    l = l.substr(2, l.size()-2);
    i = 2;
    reduce(l, i);
  }
  // terminating case at i == size-2
  else if (i == l.size()-2) {
    l = l.substr(0, l.size()-2);
    i = l.size()-1;
    return;
  }
  // general recursive case
  l = l.substr(0, i-1) + l.substr(i+1);
  i -= 1;
  reduce(l, i);
}
