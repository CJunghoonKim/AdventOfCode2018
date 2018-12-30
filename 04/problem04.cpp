#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// forward declarations
void partOne(string filename); // Part I
int getMonth(string line);  // month
int getDay(string line);    // day
int getHour(string line);   // hour
int getMinute(string line); // minute

int main() {
  partOne("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;

  while (file.is_open() && getline(file, line) {
    // line : [yyyy-MM-dd hh:mm] <action>
    cout << getMonth(line) << endl;
  }
  // close file
  file.close();
}

int getMonth(string line) {
  // assumes valid input
  return stoi(line.substr(6, 2));
}

int getDay(string line) {
  // assumes valid input
  return stoi(line.substr(9, 2));
}

int getHour(string line) {
  // assumes valid input
  return stoi(line.substr(12, 2));
}

int getMinute(string line) {
  // assumes valid input
  return stoi(line.substr(15, 2));
}
