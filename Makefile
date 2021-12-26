all:	main main_hash
	
.phony: graph.h	
	
tests: bfs_tests dfs_tests junction_tests
	
bfs_tests: main main_hash
	@echo "BFS-array.01: " | tr -d '\n' ; ./main bfs_array < tests/01-bfs.01 > /dev/null
	@echo "BFS-array.02: " | tr -d '\n' ; ./main bfs_array < tests/01-bfs.02 > /dev/null
	@echo "BFS-array.03: " | tr -d '\n' ; ./main bfs_array < tests/01-bfs.03 > /dev/null
	@echo "BFS-omap.01: " | tr -d '\n' ; ./main bfs_map < tests/01-bfs.01 > /dev/null
	@echo "BFS-omap.02: " | tr -d '\n' ; ./main bfs_map < tests/01-bfs.02 > /dev/null
	@echo "BFS-omap.03: " | tr -d '\n' ; ./main bfs_map < tests/01-bfs.03 > /dev/null
	@echo "BFS-umap.01: " | tr -d '\n' ; ./main_hash bfs_map < tests/01-bfs.01 > /dev/null
	@echo "BFS-umap.02: " | tr -d '\n' ; ./main_hash bfs_map < tests/01-bfs.02 > /dev/null
	@echo "BFS-umap.03: " | tr -d '\n' ; ./main_hash bfs_map < tests/01-bfs.03 > /dev/null
	@echo "BFS-matrix.01: " | tr -d '\n' ; ./main bfs_matrix < tests/01-bfs.01 > /dev/null
	@echo "BFS-matrix.02: " | tr -d '\n' ; ./main bfs_matrix < tests/01-bfs.02 > /dev/null
	@echo "BFS-matrix.03: " | tr -d '\n' ; ./main bfs_matrix < tests/01-bfs.03 > /dev/null


dfs_tests: main
	@echo "DFS-array.01: " | tr -d '\n'  ; ./main dfs_array < tests/01-bfs.01 > /dev/null
	@echo "DFS-array.02: " | tr -d '\n'  ; ./main dfs_array < tests/01-bfs.02 > /dev/null
	@echo "DFS-array.03: " | tr -d '\n'  ; ./main dfs_array < tests/01-bfs.03 > /dev/null
	@echo "DFS-array-norecursive.01: " | tr -d '\n'  ; ./main dfs_array_norecursive < tests/01-bfs.01 > /dev/null
	@echo "DFS-array-norecursive.02: " | tr -d '\n'  ; ./main dfs_array_norecursive < tests/01-bfs.02 > /dev/null
	@echo "DFS-array-norecursive.03: " | tr -d '\n'  ; ./main dfs_array_norecursive < tests/01-bfs.03 > /dev/null

junction_tests: main
	@echo "junction.01: " | tr -d '\n'  ; ./main junction < tests/01-bfs.01 > /dev/null
	@echo "junction.02: " | tr -d '\n'  ; ./main junction < tests/01-bfs.02 > /dev/null
	@echo "junction.03: " | tr -d '\n'  ; ./main junction < tests/01-bfs.03 > /dev/null

CXXFLAGS = -std=c++17 -O2
	
main: main.cpp graph.h
	c++ $(CXXFLAGS) -o $@ main.cpp
	
main_hash: main.cpp graph.h
	c++ $(CXXFLAGS) -DUSING_HASH_TABLES=1 -o $@ main.cpp

