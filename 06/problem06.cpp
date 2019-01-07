#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void partOne(string filename);
void partTwo(string filename);

int distance(int x1, int y1, int x2, int y2); // Manhattan distance between two points

int main() {
  partOne("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;
  int x, y;
  char mark = 'A'; // initial marker

  while (file.is_good() && getline(file, line)) {

  }
  file.close(); // close file
}

int distance(int x1, int y1, int x2, int y2) {
  return abs(x2-x1) + abs(y2-y1);
}
