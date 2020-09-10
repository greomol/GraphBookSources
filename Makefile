all:	bfs dfs

runs: $(RUNS)
	
RUNS  = $(BFS) $(DFS)
	
	
clean:  
		rm $(RUNS)
			
CXXFLAGS = -std=c++11 -O -g
	
BFS = 01-bfs

DFS = 01-dfs

.phony: graph.h
	
bfs:	$(BFS) graph.h

dfs:	$(DFS) graph.h

01-bfs: 01-bfs.cc graph.h
		c++ $(CXXFLAGS) -o $@ 01-bfs.cc
	
01-dfs: 01-dfs.cc 
		c++ $(CXXFLAGS) -o $@ 01-dfs.cc

.cc.: 
	c++ $(CXXFLAGS) -o $@ $<

