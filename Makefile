all:	bfs dfs
	
runs: $(RUNS)
	
RUNS  = $(BFS) $(DFS)
	
.phony: graph.h	
	
clean:  
	rm $(RUNS)
	
tests: bfs_tests dfs_tests
	
bfs_tests: $(BFS)
	echo "BFS-array.01: " | tr -d '\n' ; ./main-bfs-array < tests/01-bfs.01 > /dev/null
	echo "BFS-array.02: " | tr -d '\n' ; ./main-bfs-array < tests/01-bfs.02 > /dev/null
	echo "BFS-array.03: " | tr -d '\n' ; ./main-bfs-array < tests/01-bfs.03 > /dev/null
	echo "BFS-omap.01: " | tr -d '\n' ; ./main-bfs-omap < tests/01-bfs.01 > /dev/null
	echo "BFS-omap.02: " | tr -d '\n' ; ./main-bfs-omap < tests/01-bfs.02 > /dev/null
	echo "BFS-omap.03: " | tr -d '\n' ; ./main-bfs-omap < tests/01-bfs.03 > /dev/null
	echo "BFS-umap.01: " | tr -d '\n' ; ./main-bfs-umap < tests/01-bfs.01 > /dev/null
	echo "BFS-umap.02: " | tr -d '\n' ; ./main-bfs-umap < tests/01-bfs.02 > /dev/null
	echo "BFS-umap.03: " | tr -d '\n' ; ./main-bfs-umap < tests/01-bfs.03 > /dev/null
	echo "BFS-matrix.01: " | tr -d '\n' ; ./main-bfs-matrix < tests/01-bfs.01 > /dev/null
	echo "BFS-matrix.02: " | tr -d '\n' ; ./main-bfs-matrix < tests/01-bfs.02 > /dev/null
	echo "BFS-matrix.03: " | tr -d '\n' ; ./main-bfs-matrix < tests/01-bfs.03 > /dev/null


dfs_tests: $(BFS)
	echo "DFS-array.01: " | tr -d '\n'  ; ./main-dfs-array < tests/01-bfs.01 > /dev/null
	echo "DFS-array.02: " | tr -d '\n'  ; ./main-dfs-array < tests/01-bfs.02 > /dev/null
	echo "DFS-array.03: " | tr -d '\n'  ; ./main-dfs-array < tests/01-bfs.03 > /dev/null
	echo "DFS-array-nonrecursive.01: " | tr -d '\n'  ; ./main-dfs-array-nonrecursive < tests/01-bfs.01 > /dev/null
	echo "DFS-array-nonrecursive.02: " | tr -d '\n'  ; ./main-dfs-array-nonrecursive < tests/01-bfs.02 > /dev/null
	echo "DFS-array-nonrecursive.03: " | tr -d '\n'  ; ./main-dfs-array-nonrecursive < tests/01-bfs.03 > /dev/null

			
CXXFLAGS = -std=c++11 -O2
	
bfs: main-bfs-array main-bfs-omap main-bfs-umap main-bfs-matrix 
		
BFS = main-bfs-array main-bfs-omap main-bfs-umap main-bfs-matrix 

dfs: main-dfs-array  main-dfs-array-nonrecursive
	
DFS = main-dfs-array  main-dfs-array-nonrecursive
	
main-bfs-array: main-bfs-array.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-bfs-array.cc
	
main-bfs-omap: main-bfs-omap.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-bfs-omap.cc

main-bfs-umap: main-bfs-umap.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-bfs-umap.cc

main-bfs-matrix: main-bfs-matrix.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-bfs-matrix.cc

main-dfs-array: main-dfs-array.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-dfs-array.cc
	
main-dfs-array-nonrecursive: main-dfs-array-nonrecursive.cc graph.h
	c++ $(CXXFLAGS) -o $@ main-dfs-array-nonrecursive.cc


