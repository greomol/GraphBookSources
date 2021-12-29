#include <iostream>
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

void main_bfs_array() {
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

void main_bfs_matrix() {
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

void main_bfs_map() {
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


void main_dfs_array() {
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

void main_dfs_array_norecursive() {
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

void main_junction() {
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

void main_toposort() {
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

void main_Dijkstra() {
    int n; // Vertices
    int m; // Edges
    cin >> n >> m;
    wgraph<int> g(n, wgraph<int>::ARRAY, true);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        g.add_edge(from, to, cost);
    }
    g.print();
    auto st = get_wall_clock();
    auto d = g.Dijkstra(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << q << ' ';
    }
    cout << '\n';
    print_clock("Dijkstra", st, en);
}

void main_Kruscal() {
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
    g.print();
    auto st = get_wall_clock();
    auto d = g.Kruscal();
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << "(" << q.first << "," << q.second << ") ";
    }
    cout << '\n';
    print_clock("Kruscal", st, en);
}

void main_Prim() {
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
    g.print();
    auto st = get_wall_clock();
    auto d = g.Prim(0);
    auto en = get_wall_clock();
    for (auto q: d) {
        cout << "(" << q.first << "," << q.second << ") ";
    }
    cout << '\n';
    print_clock("Prim", st, en);
}

////// End of problems /////////////

using problem_func = void (*)();

int main(int argc, char **argv) {
    std::map<std::string, problem_func> problems{
            {"bfs_array", main_bfs_array},
            {"bfs_matrix", main_bfs_matrix},
            {"bfs_map", main_bfs_map},
            {"dfs_array", main_dfs_array},
            {"dfs_array_norecursive", main_dfs_array_norecursive},
            {"junction", main_junction},
            {"toposort", main_toposort},
            {"dijkstra", main_Dijkstra},
            {"kruscal", main_Kruscal},
            {"prim", main_Prim}
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
    p->second();
    return 0;
}
