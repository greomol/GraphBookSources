#pragma once
#include <cassert>

// unweighted graph
template<typename T> // Types of links
class graph {
public:
    enum graph_representation {
        MATRIX, // Matrix N*N 
        ARRAY,  // Each node has an array of adjacents
        OMAP,   // Each node has an ordered map of neibs  
        UMAP,   // Each node has an unordered map of neibs
    };
    enum graph_mode {
        ORDERED,
        UNORDERED
    };
    graph(size_t nodes, graph_representation grepr, graph_mode gmode) {
        N = nodes;
        repr = grepr;
        mode = gmode;
    }
    void add_edge (int from, int to) {
        assert (from >= 0 && from < N);
        assert (to >= 0 && to < N);
    }
    
    void print() const {
        
    }
private:
    graph_representation repr;
    graph_mode           mode;
    int                  N;
        
};