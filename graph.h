#pragma once

#include <cassert>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#ifndef USING_HASH_TABLES
#define USING_HASH_TABLES 0
#endif

#if USING_HASH_TABLES
#  include <unordered_set>
#  include <unordered_map>
using graph_map = unordered_set<int>;
#else

#  include <set>
#  include <map>

using graph_map = set<int>;
#endif

template<typename T>
class fast_queue {
private:
    T *body;
    T *begin;
    T *end;
    T *body_end;
public:
    fast_queue(size_t size) {
        body = new T[size];
        begin = end = body;
        body_end = body + size;
    }

    ~fast_queue() {
        delete[] body;
    }

    void enqueue(T const &el) {
        *end++ = el;
    }

    bool empty() const {
        return begin == end;
    }

    T dequeue() {
        return *begin++;
    }
};


// unweighted graph
class graph {
public:
    enum graph_representation {
        MATRIX, // Matrix N*N
        ARRAY,  // Each node has an array of adjacents
        GMAP,   // Each node has an map of neibs
        LIST,   // List of edges
    };
    struct link {
        int from = -1;
        int to = -1;
    };
    enum color_t {
        WHITE, GREY, BLACK
    };

    graph(size_t nodes, graph_representation grepr, bool is_ordered = false) {
        N = nodes;
        repr = grepr;
        unordered = !is_ordered;
        switch (repr) {
            case MATRIX:
                neibs.resize(N, vector<bool>(N, false));
                break;
            case ARRAY:
                adj.resize(N);
                break;
            case GMAP:
                gset.resize(N);
                break;
            case LIST:
            default:
                assert(0);
        }
    }

    void add_edge(int from, int to) {
        assert (from >= 0 && from < N);
        assert (to >= 0 && to < N);
        switch (repr) {
            case MATRIX:
                neibs[from][to] = true;
                if (unordered) {
                    neibs[to][from] = true;
                }
                break;
            case ARRAY:
                adj[from].push_back(to);
                if (unordered) {
                    adj[to].push_back(from);
                }
                break;
            case GMAP:
                gset[from].insert(to);
                if (unordered) {
                    gset[to].insert(from);
                }
                break;
            case LIST:
                assert(0);
        }
    }


    void print() const {
        switch (repr) {
            case ARRAY:
                for (int u = 0; u < N; u++) {
                    cout << u << ": ";
                    for (auto v: adj[u]) {
                        cout << v << " ";
                    }
                    cout << "\n";
                }
                break;
            case GMAP:
                for (int u = 0; u < N; u++) {
                    cout << u << ": ";
                    for (auto v: gset[u]) {
                        cout << v << " ";
                    }
                    cout << "\n";
                }
                break;
            default:
                assert(0);
        }
    }

    // Input: start node
    // Output: vector of distances
    vector<int> bfs_array(int start) const {
        assert (start >= 0 && start < N);
        assert (repr == ARRAY);
        vector<color_t> color(N, WHITE);
        vector<int> dist(N, -1);
        fast_queue<int> que(N + 1);
        que.enqueue(start);
        dist[start] = 0;
        color[start] = GREY;
        while (!que.empty()) {
            auto u = que.dequeue();
            for (auto v: adj[u]) {
                if (color[v] != WHITE) continue;
                dist[v] = dist[u] + 1;
                // If we need a predecessor, pi[u] = v;
                color[v] = GREY;
                que.enqueue(v);
            }
            color[u] = BLACK;
        }
        return dist;
    }


    // Perform BFS search.
    // Input: start - start node
    // Output: vector of distances
    vector<int> bfs_gmap(int start) const {
        assert (start >= 0 && start < N);
        assert (repr == GMAP);
        vector<color_t> color(N, WHITE);
        vector<int> dist(N, -1);
        queue<int> que;
        que.push(start);
        dist[start] = 0;
        color[start] = GREY;
        while (!que.empty()) {
            auto u = que.front();
            que.pop();
            for (auto v: gset[u]) {
                if (color[v] != WHITE) continue;
                dist[v] = dist[u] + 1;
                color[v] = GREY;
                que.push(v);
            }
            color[u] = BLACK;
        }
        return dist;
    }

    // Perform BFS search.
    // Input: s - start node
    // Output: vector of distances
    vector<int> bfs_matrix(int s) const {
        assert (s >= 0 && s < N);
        assert (repr == MATRIX);
        vector<color_t> c(N, WHITE);
        vector<int> d(N, -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        c[s] = GREY;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (int z = 0; z < N; z++) {
                if (neibs[u][z] == false || c[z] != WHITE) continue;
                d[z] = d[u] + 1;
                c[z] = GREY;
                q.push(z);
            }
            c[u] = BLACK;
        }
        return d;
    }

    void dfs_visit_array(int u, vector<color_t> &c, vector<pair<int, int>> &d, int &time) const {
        c[u] = GREY;
        d[u].first = ++time;
        for (auto v: adj[u]) {
            if (c[v] == WHITE) dfs_visit_array(v, c, d, time);
        }
        d[u].second = ++time;
    }

// Perform DFS search.
// Input: s - start node
    vector<pair<int, int>> dfs_array(int s) const {
        assert (s >= 0 && s < N);
        assert (repr == ARRAY);
        vector<color_t> c(N, WHITE);
        vector<pair<int, int>> d(N, {-1, -1});
        int time = 0;
        dfs_visit_array(s, c, d, time);
        return d;
    }


    void print(stack<int> q) const {
        while (!q.empty()) {
            auto u = q.top();
            q.pop();
            printf("%d ", u & ~0x8000000);
        }
        printf("\n");
    }

    // Perform DFS search.
    // Input: s - start node
    vector<pair<int, int>> dfs_array_norecursive() const {
        assert (repr == ARRAY);
        //print();
        vector<color_t> color(N, WHITE);
        const int MARK = 0x8000000;
        vector<pair<int, int>> d(N, {-1, -1});
        int time = 0;
        stack<int> que;
        for (int s = 0; s < N; s++) {
            if (color[s] != WHITE) continue;
            que.push(s | MARK);
            color[s] = GREY;
            while (!que.empty()) {
                //print(que);
                //printf("color: "); for (auto q: color) printf("%d ", q); printf("\n");
                auto u = que.top();
                que.pop();
                //printf("u={%d,%d}\n", u.first, u.second);
                if (u & MARK) {
                    u &= ~MARK;
                    d[u].first = ++time;
                    //printf("%d[0] time = %d\n", u.first,time);
                    que.push(u);
                    for (auto v: adj[u]) {
                        //printf("v=[%d,%d]\n", v, color[v]);
                        if (color[v] == WHITE) {
                            color[v] = GREY;
                            que.push(v | MARK);
                        }
                    }
                } else {
                    d[u].second = ++time;
                    //printf("%d[1] time = %d\n", u.first, time);
                    color[u] = BLACK;
                }
            }
        }
        return d;
    }

    void junction_point_visit_array(int node, int par, vector<color_t> &color,
                                    vector<int> &d, vector<int> &l, int &time, vector<int> &ans) {
        color[node] = GREY;
        time++;
        d[node] = l[node] = time;
        int children = 0;
        for (auto child :adj[node]) {
            if (child == par) continue;
            if (color[child] == WHITE) {
                junction_point_visit_array(child, node, color, d, l, time, ans);
                l[node] = min(l[node], l[child]);
                if (par != -1 && l[child] >= d[node]) ans.push_back(node);
                children++;
            } else {
                l[node] = min(l[node], d[child]);
            }
            if (par == -1 && children > 1) ans.push_back(node);
        }
    }

    vector<int> junction_points_array() {
        vector<int> d(N, -1);
        vector<int> l(N, -1);
        vector<color_t> color(N, WHITE);
        int time = 0;
        vector<int> ans;
        for (int u = 0; u < N; u++) {
            if (color[u] == WHITE) {
                junction_point_visit_array(u, -1, color, d, l, time, ans);
            }
        }
        return ans;
    }

    void toposort_visit_array(int u, vector<color_t> &color, queue<int> &que) {
        color[u] = GREY;
        for (auto v: adj[u]) {
            if (color[v] == WHITE)
                toposort_visit_array(v, color, que);
        }
        que.push(u);
    }

    vector<int> toposort_array() {
        if (repr != ARRAY) {
            convert_to_array();
        }
        assert(repr == ARRAY);
        queue<int> que;
        vector<color_t> color(N, WHITE);
        for (int u = 0; u < N; u++) {
            if (color[u] == WHITE) {
                toposort_visit_array(u, color, que);
            }
        }
        vector<int> ret;
        while (!que.empty()) {
            ret.push_back(que.front());
            que.pop();
        }
        return ret;
    }

private:
    graph_representation repr;
    bool unordered;

    vector<vector<bool>> neibs;
    vector<vector<int>> adj;
    vector<graph_map> gset;

    int N;

    void convert_to_array() {
        switch (repr) {
            case GMAP:
                adj.resize(N, vector<int>());
                for (size_t u = 0; u < gset.size(); u++) {
                    for (auto const v: gset[u]) {
                        adj[u].push_back(v);
                    }
                }
                gset.clear();
                repr = ARRAY;
                break;
            default:
                assert(0);
        }
    }

};
