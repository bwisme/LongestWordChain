#pragma once

#include <cstring>
#include <vector>
#define MAX_EDGE 10010
#define MAX_NODE 36


class graph
{
public:
    graph();
    ~graph();


    int head[MAX_NODE];
    int next[MAX_EDGE];
    edge edges[MAX_EDGE];

    bool self_loop; //是否有自环
    //记录的是从每个点出发的所有自环中的边
    std::vector< std::vector<int> > self_loop_edges;
    
    std::vector<int> topo_result;

private:

    int edge_count;
    
    void init();
    
    void add_edges(int from, int to, int w, char* word);

    bool dfs(int u);
    
    bool topological_sort();
    
    int id[MAX_NODE];
    
    bool vis[MAX_NODE];

    int char_to_int(char ch);

    


};

typedef struct edge 
{
    int from;
    int to;
    int weight;
    char* word;
} edge;

graph::graph()
{
}

graph::~graph()
{
}
