#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void claimFabric(int (&f)[1100][1100], int x, int y, int l, int w, int &o) {
  for (int i = 0; i < w; i++) { // col
    for (int j = 0; j < l; j++) { // row
      f[y+i][x+j]++;
      if (f[y+i][x+j] == 2) {
        o++;
      }
    }
  }
}

int main() {
  int fabric[1100][1100];
  int overlap = 0;
  fstream file("input.txt");
  string line;
  int x, y, l, w;

  while (file.is_open() && getline(file, line)) {
    // format: #n @ xxx,yyy: llxww
    x = stoi(line.substr(line.find("@")+2, line.find(",")-(line.find("@")+2)));
    y = stoi(line.substr(line.find(",")+1, line.find(":")-line.find(",")-1));
    l = stoi(line.substr(line.find(":")+2, line.find("x")-(line.find(":")+2)));
    w = stoi(line.substr(line.find("x")+1));
    claimFabric(fabric, x, y, l, w, overlap);
  }
  cout << overlap << endl;
  file.close();
  return 0;
}
