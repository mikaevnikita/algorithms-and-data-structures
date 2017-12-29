#include <iostream>
#include <vector>
#include <functional>
using namespace std;


class DFS{
private:
    function<void(int)>* func;
    vector< vector<int> >* graph;

    enum NodeStatus {NoVisited, Active, Visited};
    vector<NodeStatus> nodes_statuses;
    vector<int> parents;

    void dfs_visit(const int& node){
        nodes_statuses[node] = NodeStatus::Active;
        (*func)(node);
        for(int i = 0; i < (*graph)[node].size(); i++){
            int neighbour = (*graph)[node][i];
            if(nodes_statuses[neighbour] == NodeStatus::NoVisited){
                parents[neighbour] = node;
                dfs_visit(neighbour);
            }
        }
        nodes_statuses[node] = NodeStatus::Visited;
    }

public:
    DFS(vector< vector<int> >& _graph, function<void(int)>& _func){
        graph = &_graph;
        func = &_func;
    }

    void setGraph(vector< vector<int> >& _graph){
        graph = &_graph;
    }

    void setFunction(function<void(int)>& _func){
        func = &_func;
    }

    vector<int> operator()(const int& start_node){
        nodes_statuses.clear();
        nodes_statuses.resize(graph->size());

        parents.clear();
        parents.resize(graph->size());

        for(int v=0;v<graph->size();v++){
            nodes_statuses[v] = NodeStatus::NoVisited;
        }


        dfs_visit(start_node);

        return parents;
    }
};

int main(int argc, char *argv[])
{
    //Задаем граф списком смежности
    int n = 7;
    vector < vector<int> > graph(n);
    graph[0]={1,2};
    graph[1]={3,4};
    graph[2]={5,6};
    graph[3]={};
    graph[4]={};
    graph[5]={};
    graph[6]={};

    function<void(int)> f = [](int node){
        cout << node << endl;
    };

    DFS dfs(graph, f);

    dfs(0);

    return 0;
}
