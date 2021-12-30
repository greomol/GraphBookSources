#include <iostream>
#include <iomanip>
#include <ctime>
#include <map>
#include <cstdio>
#include <string>
#include "graph.h"
using namespace std;

static double get_wall_clock() {
    return double(clock()) / double(CLOCKS_PER_SEC);
}

static void print_clock(std::string const &msg, double start, double end) {
    fprintf(stderr, "%s %.6lf sec\n", msg.c_str(), double(end - start));
}

void main_bfs_array(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::ARRAY, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.bfs_array(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("bfs_array", st, en);
}

void main_bfs_matrix(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::MATRIX, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.bfs_matrix(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("bfs_matrix", st, en);
}

void main_bfs_map(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::GMAP, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.bfs_gmap(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("bfs_map", st, en);
}


void main_dfs_array(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::ARRAY, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.dfs_array(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q.first << '/' << q.second << ' ';
    }
    cout << '\n';
    print_clock("dfs_array", st, en);
}

void main_dfs_array_norecursive(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::ARRAY, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.dfs_array_norecursive();
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q.first << '/' << q.second << ' ';
    }
    cout << '\n';
    print_clock("dfs_array_norecursive", st, en);
}

void main_junction(int arg) {
    int n, e;
    std::cin >> n >> e;
    graph g(n, graph::ARRAY, false);
    for (int i = 0; i < e; i++) {
        int from,to;
        std::cin >> from >> to;
        g.add_edge(from,to);
    }
    // g.print();
    auto st = get_wall_clock();
    auto d = g.junction_points_array();
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("dfs_array_junction", st, en);
}

void main_toposort(int arg) {
    int n, m;
    string tmp;
    getline(cin, tmp); n = stoi(tmp);
    getline(cin, tmp); m = stoi(tmp);
    graph g(n, graph::GMAP, true);
    string last;
    getline(cin, last);
    for (int i = 1; i < m; i++) {
        getline(cin, tmp);
        for (size_t j = 0; j < min(last.size(), tmp.size()); j++) {
            if (last[j] == tmp[j]) continue;
            g.add_edge(last[j] - 'A', tmp[j] - 'A');
            break;
        }
        last = tmp;
    }
    g.print();
    auto st = get_wall_clock();
    auto d = g.toposort_array();
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("dfs_toposort", st, en);
}

void main_Dijkstra(int arg) {
    int n; // Vertices
    int m; // Edges
    cin >> n >> m;
    wgraph<int> g(n, wgraph<int>::ARRAY, true);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        g.add_edge(from, to, cost);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.Dijkstra(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("Dijkstra", st, en);
}

void main_Kruscal(int arg) {
    int n; // Vertices
    int m; // Edges
    cin >> n >> m;
    wgraph<int> g(n, wgraph<int>::LIST, true);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        from--; to--;
        g.add_edge(from, to, cost);
    }
    //g.print();
    auto st = get_wall_clock();
    auto d = g.Kruscal();
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << "(" << q.first << "," << q.second << ") ";
    }
    cout << '\n';
    print_clock("Kruscal", st, en);
}

void main_Prim(int arg) {
    int n; // Vertices
    int m; // Edges
    cin >> n >> m;
    wgraph<int> g(n, wgraph<int>::ARRAY, false);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        from--; to--;
        g.add_edge(from, to, cost);
    }
    //g.print();
    vector<tuple<size_t, size_t, int>> d;
    auto st = get_wall_clock();
    switch (arg) {
        case 0: d = g.Prim_set(0); break;
        case 1: d = g.Prim_bool(0); break;
        case 2: d = g.Prim_edges(0); break;
        case 3: d = g.Prim(0); break;
    }
    auto en = get_wall_clock();
    sort(d.begin(), d.end());
    double tot = 0;
    for (auto q: d) {
        cout << "(" << get<0>(q) << "," << get<1>(q) << ") ";
        tot += get<2>(q);
    }
    cout << '\n';
    cout << "Total = " << (unsigned long long)tot << "\n";

    print_clock("Prim", st, en);
}

////// End of problems /////////////

using problem_func = void (*)(int);

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    std::map<std::string, pair<problem_func,int>> problems{
            {"bfs_array", {main_bfs_array, 0}},
            {"bfs_matrix", {main_bfs_matrix, 0}},
            {"bfs_map", {main_bfs_map, 0}},
            {"dfs_array", {main_dfs_array, 0}},
            {"dfs_array_norecursive", {main_dfs_array_norecursive, 0}},
            {"junction", {main_junction, 0}},
            {"toposort", {main_toposort, 0}},
            {"dijkstra", {main_Dijkstra, 0}},
            {"kruscal", {main_Kruscal, 0}},
            {"prim", {main_Prim, 3}},
            {"prim_set", {main_Prim, 0}},
            {"prim_edges", {main_Prim, 2}},
            {"prim_bool", {main_Prim, 1}}
    };
    auto print_problems = [&problems]() {
        for (auto const &p: problems) {
            std::cout << p.first << "\n";
        }
    };
    if (argc == 1) {
        std::cout << "usage: " << argv[0] << " problem\nWhere problem is one of:\n\n";
        print_problems();
        return 0;
    }
    auto const p = problems.find(argv[1]);
    if (p == problems.end()) {
        std::cout << "Sorry, given problem " << argv[1] << " is not one of:\n\n";
        print_problems();
        return 0;
    }
    p->second.first(p->second.second);
    return 0;
}
