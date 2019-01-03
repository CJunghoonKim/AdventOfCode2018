#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// forward declarations
void partOne(string filename); // Part I
void partTwo(string filename); // Part II

int getMonth(string line);  // month
int getDay(string line);    // day
int getHour(string line);   // hour
int getMinute(string line); // minute
bool compareTimestamp(string t1, string t2); // comparator for sort
int mostFrequent(vector<int> *v);       // returns most frequently occuring element
int mostFrequentCount(vector<int> *v, int &c);  // returns the count of the most frequent element

int main() {
  partOne("input.txt");
  partTwo("input.txt");
  return 0;
}

// Part I
void partOne(string filename) {
  fstream file(filename);
  string line;              // line-by-line input
  vector<string> input;     // to be sorted after populating...
  map<int, int> sleepTimes; // guards and respective sleep times
  map<int, vector<int>*> sleepRanges; // guards and respective sleep ranges
  int guard;                // guard whom sleeps the most

  while (file.is_open() && getline(file, line)) {
    // line : [yyyy-MM-dd hh:mm] <action>
    input.push_back(line);
  }
  // sort using our comparator
  sort(input.begin(), input.end(), compareTimestamp);

  // pre-process sorted input
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
  guard = sleepTimes.begin()->first;
  for (map<int, int>::iterator i = sleepTimes.begin(); i != sleepTimes.end(); i++) {
    if (i->second > sleepTimes[guard]) {
      guard = i->first; // assign max
    }
  }
  // result
  cout << "Part I: " << guard * mostFrequent(sleepRanges[guard]) << endl;
  // free dynamically-allocated memory
  for (map<int, vector<int>*>::iterator i = sleepRanges.begin(); i != sleepRanges.end(); i++) {
    delete i->second;
  }
  // close file
  file.close();
}

// Part II
void partTwo(string filename) {
  fstream file(filename);
  string line;          // line-by-line input
  vector<string> input;     // to be sorted after populating...
  map<int, int> sleepTimes; // guards and respective sleep times
  map<int, vector<int>*> sleepRanges; // guards and respective sleep ranges
  int guard;            // guard whom sleeps the most on the same minute
  int minute;           // most frequent minute

  while (file.is_open() && getline(file, line)) {
    // line : [yyyy-MM-dd hh:mm] <action>
    input.push_back(line);
  }
  // sort using our comparator
  sort(input.begin(), input.end(), compareTimestamp);

  // pre-process sorted input
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
  // this time, determine guard ID whom most frequently sleeps on the same minute
  int count;
  guard = sleepRanges.begin()->first;                    // initial guard ID
  minute = mostFrequentCount(sleepRanges[guard], count); // initial minute (count via second param)
  for (map<int, vector<int>*>::iterator i = sleepRanges.begin(); i != sleepRanges.end(); i++) {
    int c; // frequency of minute
    int temp;  // temp storage for candidate minute
    temp = mostFrequentCount(i->second, c);
    if (c > count) {
      guard = i->first;
      minute = temp;
      count = c;
    }
  }
  // print result
  cout << "Part II: " << guard * minute << endl;
  // free dynamically-allocated memory
  for (map<int, vector<int>*>::iterator i = sleepRanges.begin(); i != sleepRanges.end(); i++) {
    delete i->second;
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

// simple naive implementation (dealing with small vectors)
int mostFrequent(vector<int> *v) {
  vector<int> &r = *v;
  int res = r[0];
  int countRes = 1;
  for (int i = 0; i < r.size(); i++) {
    int count = 0;
    for (int j = 0; j < r.size(); j++) {
      if (r[j] == r[i]) {
        count++;
      }
      if (j == r.size() - 1 && count > countRes) {
        res = r[i];
        countRes = count;
      }
    }
  }
  return res;
}

// similar task done by mostFrequent, but this time count is saved
int mostFrequentCount(vector<int> *v, int &c) {
  vector<int> &r = *v;
  // ensure vector has elements
  if (r.size() < 1) {
    c = -1;
    return -1;
  }
  int res = r[0];
  int countRes = 1;
  for (int i = 0; i < r.size(); i++) {
    int count = 0;
    for (int j = 0; j < r.size(); j++) {
      if (r[j] == r[i]) {
        count++;
      }
      if (j == r.size() - 1 && count > countRes) {
        res = r[i];
        countRes = count;
      }
    }
  }
  // set second param
  c = countRes;
  return res;
}
