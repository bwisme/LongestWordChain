#include "stdafx.h"
#include "graph.h"

graph::graph() {
    edge_count = 0;
    self_loop_edges = std::vector<std::vector<int>>(MAX_NODE, std::vector<int>());
    self_loop = false;
    memset(id, sizeof(id), 0);
    memset(vis_node, 0, sizeof(vis_node));
    memset(vis_edge, 0, sizeof(vis_edge));
    memset(vis_self_loop, 0, sizeof(vis_self_loop));
    memset(head, 0, sizeof(head));
    memset(next, 0, sizeof(next));
    memset(edges, 0, sizeof(next));
    loop_ans = 0;
	loop_len = 0;
	memset(loop_result, 0, sizeof(loop_result));
    topo_result.clear();
}

graph::~graph() {}

//void graph::init() {
//
//}

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
		else if (!id[v]) {
			bool ret = dfs(v);
			if (!ret) return false;
		}
    }
    id[u] = 1; topo_result.push_back(u);
    return true;
}

bool graph::topological_sort(){
    if (self_loop) return false;
    
    for(int u = 0; u < MAX_NODE; u ++) if(vis_node[u] && !id[u])
        if(!dfs(u)) return false;
    reverse(topo_result.begin(), topo_result.end());
    return true;
}

bool graph::is_node(int u) {
    return u >= 0 && u < 26;
}

void graph::search_longest_path(int u, int ans, int tail) {
    if (!vis_self_loop[u] && self_loop_edges[u].size() > 0) {
        for (int indx = 0; indx < (int)self_loop_edges[u].size(); indx ++) {
            ans += edges[self_loop_edges[u][indx]].weight;
            path[path_len ++] = self_loop_edges[u][indx];
        }
        vis_self_loop[u] = true;
    }
    if (u == tail) { //指定了结尾且当前就为结尾节点
        if (ans > loop_ans && path_len > 1) {
            // edge_record 需要有两个以上的边
            loop_ans = ans;
			loop_len = path_len;
            for (int i = 0; i < path_len; i ++) 
				loop_result[i] =  path[i];
        }
    }
    //继续进行搜索
    bool flag = false;
    for (int j = head[u]; j; j = next[j]) if (!vis_edge[j]){
        flag = true;
        vis_edge[j] = true;
		path[path_len ++] = j;
        search_longest_path(edges[j].to, ans + edges[j].weight, tail);
		path_len--;
        vis_edge[j] = false;
    }
    if (!is_node(tail) && !flag) { //没有指定终点且没边可走
        if (ans > loop_ans && path_len > 1) {
            loop_ans = ans;
			loop_len = path_len;
			for (int i = 0; i < path_len; i++)
				loop_result[i] = path[i];
        }
    }
    if (vis_self_loop[u] && self_loop_edges[u].size() > 0) {
        for (int indx = 0; indx < (int)self_loop_edges[u].size(); indx++) {
            ans -= edges[self_loop_edges[u][indx]].weight;
			path_len --;
        }
        vis_self_loop[u] = false;
    }
    //if (!flag && !edge_record.empty()) edge_record.pop_back();
}

int graph::force_dfs(char* result[], int head, int tail) {
    if (is_node(head)) {
		path_len = 0; loop_ans = 0; loop_len = 0;
        search_longest_path(head, 0, tail);
    } else {
        for (int u = 0; u < MAX_NODE; u ++) if (vis_node[u]) {
			path_len = 0; //loop_ans = 0; loop_len = 0;
            memset(vis_edge, 0, sizeof(vis_edge));
            search_longest_path(u, 0, tail);
        }
    }
    for (int i = 0; i < loop_len; i ++)
        result[i] = edges[loop_result[i]].word;
    //return loop_ans;
	return loop_len;
}

