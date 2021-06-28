from collections import defaultdict, deque


class Graph:
    def __init__(self, n):
        self.adj_list = defaultdict(list)   # it is possible to use defaultdict(list)
        self.n = n
        self.ret = []
        self.color = []
        self.time = 0
    
    def add_edge(self, ii, jj):
        self.adj_list[ii] += [jj]
        self.adj_list[jj] += [ii]

    def num_edges(self):
        return sum([len(j) for _, j in self.adj_list.items()])//2

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

    def dfs_visit(self, u):
        self.color[u] = 1
        self.time += 1
        self.d[u] = (self.time, self.d[u][1])
        for v in self.adj_list[u]:
            if self.color[v] == 0:
                self.dfs_visit(v)
        self.time += 1
        self.d[u] = (self.d[u][0], self.time)
        self.color[u] = 2
        
    def dfs(self):
        self.d = [(-1, -1)]*self.n
        self.color = [0]*self.n
        self.time = 0
        for u in range(self.n):
            if self.color[u] == 0:
                self.dfs_visit(u)
        return self.d
        
    def dfs_norecursive(self): 
        color = [0]*self.n
        mark = 100000000
        d = [(-1, -1)]*self.n
        time: int = 0
        queue = []
        for s in range(self.n):
            if color[s] == 0:
                queue.append(s + mark)
                color[s] = 1
                while queue:
                    u = queue.pop()
                    if (u >= mark):
                        u -= mark
                        time += 1
                        d[u] = (time, d[u][1])
                        queue.append(u)
                        for v in self.adj_list[u]:
                            if color[v] == 0:
                                color[v] = 1
                                queue.append(v + mark)
                    else: 
                        time += 1
                        d[u] = (d[u][0],time)
                        color[u] = 2
        return d

    def junction_point_visit(self, node, par, ans):
        self.color[node] = 1
        self.time += 1
        self.d[node] = self.l[node] = self.time
        children = 0
        for child in self.adj_list[node]:
            if child == par: 
                continue
            if self.color[child] == 1:
                self.l[node] = min(self.l[node], self.d[child])
            else:
                self.junction_point_visit(child, node, ans)
                self.l[node] = min(self.l[node], self.l[child])
                if par != -1 and self.l[child] >= self.d[node]:
                    ans.append(node)
                children += 1

        if par == -1 and children > 1: 
            ans.append(node)

    def junction_point(self):
        self.l = [-1]*self.n
        self.d = [-1]*self.n
        self.color = [0]*self.n
        self.time = 0
        ans = []
        for u in range(self.n):
            if self.color[u] == 0:
                self.junction_point_visit(u, -1, ans)
        return ans

import time

import sys
sys.setrecursionlimit(10**6)

N,M = map(int, input().split())
t = Graph(N)
for i in range(M):
    fr, to = map(int, input().split())
    t.add_edge(fr, to)


t1 = time.time()
#q = t.bfs(0)
#q = t.dfs()
#q = t.dfs_norecursive()
q = t.junction_point()
print(q)
t2 = time.time()
print(t2-t1)
           
