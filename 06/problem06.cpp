#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

void partOne(string filename);
void partTwo(string filename);

int max(vector<int> &v); // find maximum
void printGrid(vector<vector<int>> &g); // print grid (debugging purposes)
void radialExpansion(vector<vector<int>> &g, int &slots, vector<int> &x, vector<int> &y, map<string, int> &rad); // perform expansion

int main() {
  partOne("test.txt");
  // partTwo("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;
  vector<int> inputX;
  vector<int> inputY;

  while (file.is_open() && getline(file, line)) {
    // store input for pre-processing to determine grid parameters
    inputX.push_back(atoi(line.substr(0, line.find(',')).c_str()));
    inputY.push_back(atoi(line.substr(line.find(',')+1).c_str()));
  }
  file.close(); // close file

  int size = max(inputX) > max(inputY) ? max(inputX)+1 : max(inputY)+1;
  vector<vector<int>> grid(size, vector<int>(size, 0)); // size x size vector initialized with zeroes
  map<string, int> rad; // source point radii
  int mark = 1; // incrementing grid markers
  int slots;    // number of free slots left in grid

  // initialize source point radii
  for (int i = 0; i < inputX.size(); i++) {
    rad[to_string(inputX[i]) + ", " + to_string(inputY[i])] = 1;
  }
  // set initial grid state
  for (int i = 0; i < inputX.size(); i++) {
    grid[inputX[i]][inputY[i]] = mark;
    mark++;
  }
  slots = size*size - inputX.size();

  // populate grid
  while (slots > 0) {
    radialExpansion(grid, slots, inputX, inputY, rad);
  }
  printGrid(grid);
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

void printGrid(vector<vector<int>> &g) {
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g[0].size(); j++) {
      if (g[i][j] == -1) {
        cout << ". ";
      } else {
        cout << g[i][j] << " ";
      }
    }
    cout << endl;
  }
}

void radialExpansion(vector<vector<int>> &g, int &slots, vector<int> &x, vector<int> &y, map<string, int> &rad) {
  int a, b; // corner points
  vector<string> contest; // contested points
  /* source points will expand radially w.r.t Manhattan distance in counterclockwise fashion...
     o . . . A . . . +   --> A-B: f(x, y) = (x--, y++)
     . . . a x d . . .       B-C: f(x, y) = (x++, y++)
     . . a x x x d . .       C-D: f(x, y) = (x++, y--)
     . B x x X x x D .       D-A: f(x, y) = (x--, y--)
     . . b x x x c . .   special cases arise when corner points A, B, C, D have:
     . . . b x c . . .       - reached the edge of the grid
     + . . . C . . . .       - or meet an already-claimed area
  */
  for (int i = 0; i < x.size(); i++) {
    string pair = to_string(x[i]) + ", " + to_string(y[i]);
    int mark = g[x[i]][y[i]]; // current marker to use
    // A -> B: x--, y++
    a = x[i];
    b = y[i] - rad[pair];
    for (int j = 0; j < rad[pair]; j++) {
      if (a-j >= 0 && b+j < g.size() && a-j < g.size() && b+j >= 0) {
        if (g[a-j][b+j] == 0) { // marks a
          g[a-j][b+j] = mark;
        }
        else if (g[a-j][b+j] == -1) { // neutral ground
          continue;
        }
        // TODO: HANDLE CONTESTED POINTS
        slots--;
      }
    }
    // B -> C: x++, y++
    a = x[i] - rad[pair];
    b = y[i];
    for (int j = 0; j < rad[pair]; j++) {
      if (a+j < g.size() && b+j < g.size() && a+j >= 0 && b+j >= 0) {
        if (g[a+j][b+j] == 0) { // marks b
          g[a+j][b+j] = mark;
        }
        else if (g[a+j][b+j] == -1) { // neutral ground
          continue;
        }
        slots--;
      }
    }
    // C -> D: x++, y--
    a = x[i];
    b = y[i] + rad[pair];
    for (int j = 0; j < rad[pair]; j++) {
      if (a+j < g.size() && b-j >= 0 && a+j >= 0 && b-j < g.size()) {
        if (g[a+j][b-j] == 0) {// marks c
          g[a+j][b-j] = mark;
        }
        else if (g[a+j][b-j] == -1) { // neutral ground
          continue;
        }
        slots--;
      }
    }
    // D -> A: x--, y--
    a = x[i] + rad[pair];
    b = y[i];
    for (int j = 0; j < rad[pair]; j++) {
      if (a-j >= 0 && b-j >= 0 && a-j < g.size() && b-j < g.size()) {
        if (g[a-j][b-j] == 0) { // marks d
          g[a-j][b-j] = mark;
        }
        else if (g[a-j][b-j] == -1) { // neutral ground
          continue;
        }
        slots--;
      }
    }
    // update radius
    rad[pair]++;
  }
}
