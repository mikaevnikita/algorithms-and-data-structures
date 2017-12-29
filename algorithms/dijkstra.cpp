#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void printVector(const vector<int>& v){
    for(int x:v)
        cout << x << " ";
    cout << endl;
}


vector<int> getWay(vector<int>& parents, int from, int to){
    vector<int> path;
    for (int v=to; v!=from; v=parents[v])
        path.push_back(v);//Добавляем родителя текущей вершины
    path.push_back(from);
    reverse(path.begin(), path.end());
    return path;
}

pair<vector<int>,vector<int>> dijkstra(vector < vector < pair<int,int> > > &graph, int start_node){
    const int INF = 1000000000;
    int n = graph.size();

    vector<int> distances(n, INF);
    vector<int> parents(n);
    distances[start_node] = 0;
    vector<char> visited(n);
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!visited[j] and (v == -1 or distances[j] < distances[v]))
                v = j;
        if (distances[v] == INF)
            break;
        visited[v] = true;

        for (int j=0; j<graph[v].size(); ++j) {
            int to = graph[v][j].first;
            int len = graph[v][j].second;
            if (distances[v] + len < distances[to]) {
                distances[to] = distances[v] + len;
                parents[to] = v;
            }
        }
    }

    return make_pair(parents,distances);
}

int main() {
    //Задаем граф списком смежности
    int n = 4;
    vector < vector < pair<int,int> > > graph(n);
    graph[0]={make_pair(1,2),make_pair(2,5)};
    graph[1]={make_pair(2,2),make_pair(3,3)};
    graph[2]={make_pair(3,1)};
    graph[3]={};

    pair<vector<int>,vector<int>> result = dijkstra(graph,0);

    int from = 0;
    int to = 3;

    vector<int> way = getWay(result.first,from,to);
    int len_of_way = result.second[to];
    cout << "Путь : " << endl;
    printVector(way);
    cout << "Длина пути: " << len_of_way << endl;

}
