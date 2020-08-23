all:	bfs dfs

runs: $(RUNS)
	
RUNS  = $(BFS) $(DFS)
	
	
clean:  
		rm $(RUNS)
			
CXXFLAGS = -std=c++11 -O -g
	
BFS = 01-bfs

DFS =

.phony: graph.h
	
bfs:	$(BFS) graph.h

dfs:	$(DFS) graph.h

.cc.: 
	c++ $(CXXFLAGS) -o $@ $<

