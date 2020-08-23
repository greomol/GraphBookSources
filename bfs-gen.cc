#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;


int main(int argc, char **argv) {
  int v = argc > 1 ? atoi(argv[1]) : 10;
  int e = argc > 2 ? atoi(argv[2]) : 20;
  set<pair<int,int>> s;
  while (s.size() < e) {
    int f = rand() % v;
    int t = rand() % v;
    if (f == t) continue;
    if (f > t) swap(f,t);
    s.insert({f,t});
  }
  printf("%d %d\n", v, e);
  for (auto z: s) {
    printf("%d %d\n", z.first, z.second);
  }
}

