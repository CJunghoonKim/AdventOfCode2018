#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// Part I
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

// modified claimFabric for Part II
void markFabric(int (&f)[1100][1100], int x, int y, int l, int w, map<int, int> &m, int n) {
  map<int, int>::iterator i = m.find(n);
  m[n] = i == m.end() ? 0 : m[n];
  for (int i = 0; i < w; i++) { // col
    for (int j = 0; j < l; j++) { // row
      // detect change
      if (f[y+i][x+j] != 0 && f[y+i][x+j] != n) {
        m[f[y+i][x+j]] = 1;
        m[n] = 1;
      }
      f[y+i][x+j] = n;
    }
  }
}

int main() {
  int fabric[1100][1100];
  int overlap = 0;
  fstream file("input.txt");
  string line;
  int x, y, l, w, n;
  map<int, int> claims; // Part II
  map<int, int>::iterator i;
  while (file.is_open() && getline(file, line)) {
    // format: #n @ xxx,yyy: llxww
    x = stoi(line.substr(line.find("@")+2, line.find(",")-(line.find("@")+2)));
    y = stoi(line.substr(line.find(",")+1, line.find(":")-line.find(",")-1));
    l = stoi(line.substr(line.find(":")+2, line.find("x")-(line.find(":")+2)));
    w = stoi(line.substr(line.find("x")+1));
    n = stoi(line.substr(1, line.find("@"-2)));  // Part II Claim ID
    // claimFabric(fabric, x, y, l, w, overlap); // Part I
    markFabric(fabric, x, y, l, w, claims, n);   // Part II
  }
  cout << overlap << endl; // Part I
  // search for lone claim
  for (i = claims.begin(); i != claims.end(); i++) {
    if (i->second == 0) {
      cout << i->first << endl; // Part II
      break;
    }
  }
  file.close();
  return 0;
}
