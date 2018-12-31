#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// forward declarations
void partOne(string filename); // Part I
int getMonth(string line);  // month
int getDay(string line);    // day
int getHour(string line);   // hour
int getMinute(string line); // minute
bool compareTimestamp(string t1, string t2); // comparator for sort

int main() {
  partOne("input.txt");
  return 0;
}

void partOne(string filename) {
  fstream file(filename);
  string line;          // line-by-line input
  vector<string> input;     // to be sorted after populating...
  map<int, int> sleepTimes; // guards and respective sleep times
  map<int, vector<int>*> sleepRanges; // guards and respective sleep ranges
  int guard;            // guard whom sleeps the most

  while (file.is_open() && getline(file, line)) {
    // line : [yyyy-MM-dd hh:mm] <action>
    input.push_back(line);
  }
  // sort using our comparator
  sort(input.begin(), input.end(), compareTimestamp);

  // first step is to figure out which guard sleeps the most
  int g, f, w; // g: ID, f: falls asleep, w: wakes up
  for (string i : input) {
    /* three possible actions:
          1. [...] Guard #### begins shift
          2. [...] falls asleep
          3. [...] wakes up
    */
    if (i[i.find("]")+2] == 'G') {
      // set current ID
      g = stoi(i.substr(i.find("#")+1, i.find("b")-1 - (i.find("#")+1)));
      // ensure ID is initialized within maps
      map<int, int>::iterator t = sleepTimes.find(g);
      sleepTimes[g] = t == sleepTimes.end() ? 0 : sleepTimes[g];
      map<int, vector<int>*>::iterator r = sleepRanges.find(g);
      // avoid call of vector::equals
      if (r == sleepRanges.end()) {
        sleepRanges[g] = new vector<int>();
      }
    }
    else if (i[i.find("]")+2] == 'f') {
      f = getMinute(i);
    }
    else {
      w = getMinute(i);
      // update sleep time
      sleepTimes[g] += w - f;
      // update sleep sleep ranges
      for (int j = f; j < w; j++) {
        sleepRanges[g]->push_back(j);
      }
    }
  }
  // find guard who sleeps the most and the most probable minute

  // free dynamically-allocated memory

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

// strict comparator
bool compareTimestamp(string t1, string t2) {
  // compare by order of: month, day, hour, minute
  if (getMonth(t2) == getMonth(t1)) {
    if (getDay(t2) == getDay(t1)) {
      if (getHour(t2) == getHour(t1)) {
        return getMinute(t2) > getMinute(t1);
      }
      return getHour(t2) > getHour(t1);
    }
    return getDay(t2) > getDay(t1);
  }
  return getMonth(t2) > getMonth(t1);
}
