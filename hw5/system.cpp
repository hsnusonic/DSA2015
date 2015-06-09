#include <iostream>
#include <string>
#include "binomial_heap.h"

using namespace std;

struct task {
  int id;
  int p;  // priority

  task(int _id, int _p): id(_id), p(_p) {}

  bool operator>(const task &T2) {
    if (p == T2.p)
      return id < T2.id;
    else
      return p > T2.p;
  }

  task& operator=(const task &T2) {
    id = T2.id;
    p = T2.p;
    return *this;
  }
};

typedef struct task Task;
typedef BinomialHeap<Task> BH;

void Assign(BH* cms, const int& cm, const int& id, const int& p) {
  Task job(id, p);
  cms[cm].insert(job);
  /* Output message */
  cout << "There are " << cms[cm].size() << " tasks on computer " << cm << "." << endl;

}

void Execute(BH* cms, const int& cm) {
  try {
  Task First = cms[cm].pop();
  cout << "Computer " << cm << " executed task " << First.id << "." << endl;

  Task Second = cms[cm].max();
  while (Second.p == First.p) {
    Task n = cms[cm].pop();
    cout << "Computer " << cm << " executed task " << n.id << "." << endl;
    Second = cms[cm].max();
  }}
  catch (EmptyHeap& EH) {}
}

void Merge(BH* cms, const int &cm1, const int &cm2, const int &w) {
  if (cms[cm2].size() >= w) {
    cms[cm1].merge(cms[cm2]);
    cout << "The largest priority number is now " << cms[cm1].max().p <<  " on " << cm1 << "." << endl;
  } else
    cout << "Merging request failed." << endl;
}

int main(void) {
  int c, w;
  cin >> c >> w;
  BH *cms = new BH[c];

  string line;
  while (getline(cin, line)) {
    size_t pos = line.find(' ');
    string command = line.substr(0, pos);
    line.erase(0, pos+1);

    if (command == "assign") {
      int parameter[3];
      for (int i=0; i<3; ++i) {
        pos = line.find(' ');
        parameter[i] = stoi(line.substr(0, pos));
        line.erase(0, pos+1);
      }
      Assign(cms, parameter[0], parameter[1], parameter[2]);
    } else if (command == "execute") {
      int cm = stoi(line);
      Execute(cms, cm);
    } else if (command == "merge") {
      int parameter[2];
      for (int i=0; i<2; ++i) {
        pos = line.find(' ');
        parameter[i] = stoi(line.substr(0, pos));
        line.erase(0, pos+1);
      }
      Merge(cms, parameter[0], parameter[1], w);
    }
  }

  return 0;
}
