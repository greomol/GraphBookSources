#include <iostream>
#include <iomanip>
#include <time.h>
#define USING_HASH_TABLES 1
#include "graph.h"

int main() {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::ARRAY, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    clock_t st = clock();
    auto d = g.dfs_array(0);
    clock_t en = clock();
    for (auto q: d) {
        cout << q.first << '/' << q.second << ' ';
    }
    cout << '\n';
    cerr << fixed << setprecision(6) << (en - st) * 1.0 / CLOCKS_PER_SEC << endl;
}

