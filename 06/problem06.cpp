#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

void partOne(string filename);
void partTwo(string filename);

int distance(int x1, int y1, int x2, int y2); // Manhattan distance between two points
int max(vector<int> &v);                 // find maximum
void clearGrid(int (&g)[][], int &size); // clear grid
void radialExpansion(int (&g)[][], int &size, vector<int> &x, vector<int> &y); // perform expansion

int main() {
  partOne("input.txt");
  // partTwo("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;
  vector<int> inputX;
  vector<int> inputY;

  while (file.is_good() && getline(file, line)) {
    // store input for pre-processing to determine grid parameters
    inputX.push_back(atoi(line.substr(0, line.find(','))));
    inputY.push_back(atoi(line.substr(line.find(','))));
  }
  file.close(); // close file

  int grid[max(inputX)][max(inputY)];
  int mark = 0; // incrementing grid markers
  int slots;    // number of free slots left in grid

  // set initial grid state
  for (int i = 0; i < inputX.size(); i++) {
    grid[inputX[i]][inputY[i]] = mark;
    mark++;
  }
  slots = max(inputX)*max(inputY) - inputX.size();
  clearGrid(grid, max(inputX));
  
  // populate grid
  while (slots > 0) {
    radialExpansion(grid, inputX, inputY);
  }
}

int distance(int x1, int y1, int x2, int y2) {
  return abs(x2-x1) + abs(y2-y1);
}

int max(vector<int> &v) {
  int res = v[0];
  for (int i = 1; i < v.size(); i++) {
    if (v[i] > res) {
      res = v[i];
    }
  }
  return res;
}

void clearGrid(int (&g)[][], int &size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      g[i][j] = 0; // unclaimed
    }
  }
}

void radialExpansion(int (&g)[][], int &size, vector<int> &x, vector<int> &y) {

}
