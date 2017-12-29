from collections import deque

def readAdjacencyMatrix(fname):
    f = open(fname,'r')
    adjacency_matrix = []
    i = 0
    for line in f:
        adjacency_matrix.append([])
        for el in line:
            if(el.isdigit()):
                adjacency_matrix[i].append(int(el))
        i += 1
    f.close()
    return adjacency_matrix

class DFS():
    nodes_statuses = []
    adjacency_matrix = []

    def visit(self,node,func):
        self.nodes_statuses[node] = 1
        if(func != None):
            func(node)
        for i in range(len(self.adjacency_matrix[node])):
            has_path = self.adjacency_matrix[node][i]
            if(has_path):
                neightbour = i
                if(self.nodes_statuses[neightbour] == 0):
                    self.visit(neightbour,func)
        self.nodes_statuses[node] = 2;

    def dfs(self,start_node,func):
        print('Начало DFS алгоритма:')
        self.nodes_statuses = [0 for x in range(len(self.adjacency_matrix))]
        self.visit(start_node, func)

    def setAdjacencyMatrix(self,adjacency_matrix):
        self.adjacency_matrix = adjacency_matrix

    def countOfConnectivityComponents(self):
        self.nodes_statuses = [0 for x in range(len(self.adjacency_matrix))]
        k=0
        for i in range(len(self.adjacency_matrix)):
            if(self.nodes_statuses[i] == 0):
                k+=1
                self.visit(i,None)
        return k

    def countOfEdges(self):
        size = len(self.adjacency_matrix)
        count_of_edges = 0
        for i in range(size):
            for j in range(size - i):
                count_of_edges += self.adjacency_matrix[i][i+j]
        return count_of_edges

    def countOfVertexes(self):
        return len(self.adjacency_matrix)

    def circuitRank(self):
        return self.countOfEdges() - self.countOfVertexes() + self.countOfConnectivityComponents()

    def rankOfCuts(self):
        return self.countOfVertexes() - self.countOfConnectivityComponents();

class BFS():
    nodes_statuses = []
    adjacency_matrix = []
    queue = None

    def setAdjacencyMatrix(self,adjacency_matrix):
        self.adjacency_matrix = adjacency_matrix


    def bfs(self,start_node,func):
        print('Начало BFS алгоритма:')
        self.nodes_statuses = [0 for x in range(len(self.adjacency_matrix))]
        self.nodes_statuses[start_node] = 1
        queue = deque()
        queue.append(start_node)

        while queue:
            parent_v = queue.popleft()
            if(func != None):
                func(parent_v)
            for i in range(len(self.adjacency_matrix)):
                has_path = self.adjacency_matrix[parent_v][i]
                if(has_path and not self.nodes_statuses[i]):
                    self.nodes_statuses[i] = 1
                    queue.append(i)

adjacency_matrix = readAdjacencyMatrix('adjacency_matrix.txt')
dfs = DFS()
dfs.setAdjacencyMatrix(adjacency_matrix)
dfs.dfs(2, lambda x:print('Вершина ', x))

bfs = BFS()
bfs.setAdjacencyMatrix(adjacency_matrix)
bfs.bfs(1, lambda x:print('Вершина ', x))

print('Число компонент связности: ', dfs.countOfConnectivityComponents())
print('Число ребер в графе: ', dfs.countOfEdges())
print('Циклический ранг(цикломатическое число) графа: ', dfs.circuitRank())
print('Ранг разрезов(коциклическое число) графа: ', dfs.rankOfCuts())