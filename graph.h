#pragma once
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

#ifndef USING_HASH_TABLES
#define USING_HASH_TABLES 0
#endif

#if USING_HASH_TABLES
#   include <unordered_set>
#   include <unordered_map>
using graph_map = unordered_set<int>;
#else
#   include <set>
#   include <map>
using graph_map = set<int>;
#endif



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
    enum color {
        WHITE, GREY, BLACK
    };
    graph(size_t nodes, graph_representation grepr, bool is_ordered = false) {
        N = nodes;
        repr = grepr;
        unordered = !is_ordered;
        switch (repr) {
        case MATRIX: 
            neibs.resize(N, vector<bool>(N,false));
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
    void add_edge (int from, int to) {
        assert (from >= 0 && from < N);
        assert (to >= 0 && to < N);
        switch(repr) {
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
    
    // Perform BFS search.
    // Input: s - start node
    // Output: vector of distances 
    vector<int> bfs_array(int s) const { 
        assert (s >= 0 && s < N);
        assert (repr == ARRAY);
        vector<color> c(N, WHITE);
        vector<int>   d(N, -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        c[s] = GREY;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto z: adj[u]) {
                if (c[z] != WHITE) continue;
                d[z] = d[u] + 1;
                c[z] = GREY;
                q.push(z);
            }
            c[u] = BLACK;
        } 
        return d;
    }
    // Perform BFS search.
    // Input: s - start node
    // Output: vector of distances 
    vector<int> bfs_gmap(int s) const { 
        assert (s >= 0 && s < N);
        assert (repr == GMAP);
        vector<color> c(N, WHITE);
        vector<int>   d(N, -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        c[s] = GREY;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto z: gset[u]) {
                if (c[z] != WHITE) continue;
                d[z] = d[u] + 1;
                c[z] = GREY;
                q.push(z);
            }
            c[u] = BLACK;
        } 
        return d;
    }
    // Perform BFS search.
    // Input: s - start node
    // Output: vector of distances 
    vector<int> bfs_matrix(int s) const { 
        assert (s >= 0 && s < N);
        assert (repr == MATRIX);
        vector<color> c(N, WHITE);
        vector<int>   d(N, -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        c[s] = GREY;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (int z = 0; z < N;  z++) {
                if (neibs[u][z] == false || c[z] != WHITE) continue;
                d[z] = d[u] + 1;
                c[z] = GREY;
                q.push(z);
            }
            c[u] = BLACK;
        } 
        return d;
    }    
private:
    graph_representation repr;
    bool                 unordered;
    
    vector<vector<bool>>  neibs;
    vector<vector<int>>   adj;
    vector<graph_map>     gset;
    
    int                   N;
        
};