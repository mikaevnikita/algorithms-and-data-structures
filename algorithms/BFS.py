from collections import deque


def print_way(parents,vertex_to):
    if parents[vertex_to] != vertex_to:
        print_way(parents,parents[vertex_to])
    print(vertex_to)

def bfs(adjacency_list, vertex_from):
    visited={}
    bfs_queue = deque()
    parents={}
    distances={}

    bfs_queue.append(vertex_from)
    distances[vertex_from] = 0

    print("Обход начался: ")
    while bfs_queue:
        parent_vertex = bfs_queue.popleft()
        print(parent_vertex)
        for current_vertex in adjacency_list[parent_vertex]:
            visited_status = visited.get(current_vertex,False)
            if not visited_status:
                visited[current_vertex] = True
                parents[current_vertex] = parent_vertex
                distances[current_vertex] = distances[parent_vertex] + 1
                bfs_queue.append(current_vertex)

    parents[vertex_from]=vertex_from

    for current_vertex in adjacency_list.keys():
        if(distances.get(current_vertex,False)):
            print('\n')
            print('Путь до ' + current_vertex)
            print_way(parents,current_vertex)
            print('Конец пути, его длина : ' + str(distances[current_vertex]))

adjacency_list = dict()
adjacency_list["alice"] = ["claire","bob"]
adjacency_list["claire"] = ["a","b"]
adjacency_list["bob"]=["c","d"]
adjacency_list["c"]=["b"]
adjacency_list["a"]=[]
adjacency_list["b"]=[]
adjacency_list["d"]=[]

bfs(adjacency_list,"bob")
