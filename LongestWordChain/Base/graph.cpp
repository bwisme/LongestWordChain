#include "graph.h"
graph::graph() {
    init();
}

graph::~graph() {}

void graph::init() {
    edge_count = 0;
    self_loop_edges = std::vector<std::vector<int>>(MAX_NODE, std::vector<int>());
    self_loop = false;
    memset(id, sizeof(id), 0);
    memset(vis_node, 0, sizeof(vis_node));
    memset(vis_edge, 0, sizeof(vis_edge));
    memset(head, 0, sizeof(head));
    memset(next, 0, sizeof(next));
    memset(edges, 0, sizeof(next));
    topo_result.clear();
}

int graph::char_to_int(char ch) {
    return ch - 'a';
}

void graph::add_edges(int from, int to, int w, char* word){
    if (from == to) {
        self_loop_edges[from].push_back(++ edge_count);
        if (self_loop_edges[from].size() > 1) self_loop = true;
    } else {
        next[++ edge_count] = head[from];
        head[from] = edge_count;
    }
    edges[edge_count] = {from, to, w, word};
    vis_node[from] = vis_node[to] = true;
}

bool graph::dfs(int u) {
    id[u] = -1;
    for(int j = head[u]; j; j = next[j]) {
        int v = edges[j].to;
        if(id[v]<0) return false;
        else if(!id[v]) dfs(v);
    }
    id[u] = 1; topo_result.push_back(u);
    return true;
}

bool graph::topological_sort(){
    if (self_loop) return false;
    
    for(int u = 0; u < MAX_NODE; u ++) if(vis[u] && !id[u])
        if(!dfs(u)) return false;
    reverse(topo_result.begin(), topo_result.end());
    return true;
}



int graph::force_dfs(char* result, int head, int tail) {
    
    
    return 0;
}

