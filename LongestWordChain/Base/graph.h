#pragma once

#include <cstring>
#include <vector>
#define MAX_EDGE 10010
#define MAX_NODE 36

typedef struct edge
{
    int from;
    int to;
    int weight;
    char* word;
} edge;


class graph
{
public:
    graph();
    ~graph();


    int head[MAX_NODE];
    int next[MAX_EDGE];
    edge edges[MAX_EDGE];

    std::vector<int> loop_result; //有环的情况才会用到 一个全局变量，存储的是当前最长路径（边
    int loop_ans;//有环的情况才会用到 一个全局变量，存储的是当前最长路径的值
    
    bool self_loop; //是否有自环
    //记录的是从每个点出发的所有自环中的边
    std::vector< std::vector<int> > self_loop_edges;
    
    std::vector<int> topo_result;

    int edge_count;

    void init();

    void add_edges(int from, int to, int w, char* word);

    bool dfs(int u);

    bool topological_sort();

    int id[MAX_NODE];

    bool vis_node[MAX_NODE];
    
    bool vis_edge[MAX_EDGE];

    int char_to_int(char ch);
    
    void search_longest_path(std::vector<int> edge_record, int u, int ans, int tail);

    int force_dfs(char* result, int head, int tail);
    
    bool is_node(int u);

private:


    


};



