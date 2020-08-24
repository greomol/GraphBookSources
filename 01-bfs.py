from collections import defaultdict, deque

class Graph:
    def __init__(self,n):
        self.adj_list = defaultdict(list)   # it is possible to use defaultdict(list)
        self.n = n

    def add_edge(self,i,j):
        self.adj_list[i] += [j]
        self.adj_list[j] += [i]

    def num_edges(self):
        return sum([len(j) for _,j in self.adj_list.items()])//2

    def bfs(self, start):
        queue = deque([start])
        dist = [-1]*self.n
        dist[start] = 0

        while queue:
            last = queue.popleft()
            for neib in self.adj_list[last]:
                if dist[neib] == -1:
                    dist[neib] = dist[last] + 1
                    queue.append(neib)

        return dist
        
import time
        
N,M = map(int,input().split())
t = Graph(N)
for i in range(M):
    fr,to = map(int,input().split())
    t.add_edge(fr,to) 
    
    
t1 = time.time()
q = t.bfs(0)
t2 = time.time()
print(t2-t1)
           