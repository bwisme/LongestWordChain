#pragma once

#include <vector>
#define MAX_EDGE 10010
#define MAX_NODE 36


class graph
{
public:
    graph();
    ~graph();

    graph(char* words[]);

    int head[MAX_NODE];
    int next[MAX_EDGE];
    edge edges[MAX_EDGE];

    std::vector<int> topo_result;

private:

    int edge_count = 0;


    void add_edges();

    int topological_sort();




};

typedef struct edge 
{
    int from;
    int to;
    int weight; 
} edge;

graph::graph()
{
}

graph::~graph()
{
}
