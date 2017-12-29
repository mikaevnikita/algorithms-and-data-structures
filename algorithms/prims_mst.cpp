#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;


const int INF = 1e9;

int getMinVertex(vector<vector<int>>& graph, vector<char>& mst, int from){
    int min_vertex = from;
    for(int i=0;i<graph.size();i++){
        if(mst[i])
            continue;
        int current_vertex = i;
        int current_vertex_weight = graph[from][i];
        int min_vertex_weight = graph[from][min_vertex];
        if(current_vertex_weight < min_vertex_weight)
            min_vertex = current_vertex;
    }
    return min_vertex;
}

pair<vector<int>,int> primsAlgorithm(vector<vector<int>>& graph, int start_node){
    vector<char> used(graph.size(),false);
    vector<int> mst;
    int mst_weight = 0;

    queue<int> q;
    q.push(start_node);

    while(!q.empty()){
        int current_vertex = q.front();
        q.pop();

        used[current_vertex] = true;

        int min_vertex = getMinVertex(graph,used,current_vertex);
        int current_weight = graph[current_vertex][min_vertex];

        mst.push_back(current_vertex);

        if(min_vertex == current_vertex)
            break;//Выделили остов

        q.push(min_vertex);
        mst_weight += current_weight;
    }

    return make_pair(mst,mst_weight);
}

void setSymmetricEdge(vector<vector<int>> &graph, int from, int to, int weight){
    from--;
    to--;
    graph[from][to]=weight;
    graph[to][from]=weight;
}


int main(int argc, char *argv[])
{
    int n = 8;
    vector<vector<int>> graph(n);
    for(int i=0;i<n;i++){
        graph[i] = vector<int>(n);
        for(int j=0;j<n;j++){
            if(i==j)
                graph[i][j]=0;
            graph[i][j]=INF;
        }
    }

    setSymmetricEdge(graph,1,2,1);
    setSymmetricEdge(graph,1,8,9);
    setSymmetricEdge(graph,2,3,3);
    setSymmetricEdge(graph,2,8,2);
    setSymmetricEdge(graph,2,6,8);
    setSymmetricEdge(graph,8,4,2);
    setSymmetricEdge(graph,3,7,7);
    setSymmetricEdge(graph,7,6,3);
    setSymmetricEdge(graph,6,5,2);
    setSymmetricEdge(graph,5,4,8);


    pair<vector<int>,int> result = primsAlgorithm(graph,0);
    vector<int> mst = result.first;
    int mst_weight = result.second;

    for(int v:mst){
        cout << v << "->";
    }
    cout << endl;

    cout << "MST Weight: " << mst_weight << endl;
    return 0;
}
