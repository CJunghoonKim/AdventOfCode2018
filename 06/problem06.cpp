#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void partOne(string filename);
void partTwo(string filename);

int main() {
  partOne("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;
  int x, y;

  while (file.is_good() && getLine(file, line)) {

  }
  file.close();
}
