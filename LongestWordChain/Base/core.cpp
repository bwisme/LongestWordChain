#include "core.h"

core::core()
{
    word_graph = new graph();
    memset(dp_next, 0, sizeof(dp_next));
}

core::~core()
{
}

int core::char_to_int(char ch) {
    return ch - 'a';
}

void core::init_dp(char head, char tail, bool enable_loop) {
    mod = ORD;
    if (head && tail) mod = HEAD_TAIL;
    else if (head) mod = HEAD;
    else if (tail) mod = TAIL;
    
    if (mod == ORD || mod == HEAD) {
        memset(dp_result, 0, sizeof(dp_result));
    } else {
        for (int i = 0; i < MAX_NODE; i ++) dp_result[i] = -INF;
        dp_result[char_to_int(tail)] = 0;
    }
}

void core::make_graph(char* words[], int len, int cal_mod) {
    for (int i = 0; i < len; i ++) {
        int from, to, w, word_length;
        word_length = (int)strlen(words[i]);
        from = char_to_int(words[i][0]);
        to = char_to_int(words[i][word_length - 1]);
        
        if (cal_mod == WORD) w = 1;
        else w = word_length;
        
        word_graph->add_edges(from, to, w, words[i]);
    }
    
}

void core::get_dp_result() {
    for (int i = (int) word_graph -> topo_result.size() - 1; i >= 0; i --) {
        int u = word_graph -> topo_result.at(i);
        for (int j = word_graph -> head[u]; j; j = word_graph -> next[j]) {
            int v = word_graph -> edges[j].to;
            int tmp = dp_result[v] + word_graph -> edges[j].weight;
            if (tmp > dp_result[u]) {
                dp_result[u] = tmp;
                dp_next[u] = j;
            }
        }
    }
}

int core::get_ans(char* result[]){
    int ans = 0, from;
    if (mod == ORD || mod == TAIL) {
        for (int i = 0; i < MAX_NODE; i ++) if (dp_result[i] > ans) {
            ans = dp_result[i];
            from = i;
        }
    } else if (mod == HEAD || mod == HEAD_TAIL) {
        from = char_to_int(mod); //bugfix: head -> mod
        ans = dp_result[from];
    }
    
    int node = from, cnt = 0;
    while (dp_next[node]) {
        result[cnt ++] = word_graph -> edges[dp_next[node]].word;
        node = word_graph -> edges[dp_next[node]].to;
    }
    
    return ans;
}


int core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    make_graph(words, len, WORD);
    
    init_dp(head, tail, enable_loop);
    
    word_graph -> topological_sort();
    
    get_dp_result();
    
    int ans = get_ans(result);
    return ans;
}

int core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    make_graph(words, len, CHAR);
    
    init_dp(head, tail, enable_loop);
    
    word_graph -> topological_sort();
    
    get_dp_result();
    
    int ans = get_ans(result);
    return ans;
}
