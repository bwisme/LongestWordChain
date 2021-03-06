#include "stdafx.h"
#include "core_dll.h"
#include <iostream>
#include <set>
#include <map>
core::core()
{
	init();
}

core::~core()
{
}

void core::init() {
    word_graph = new graph();
    memset(dp_next, 0, sizeof(dp_next));
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
        
        if (cal_mod == WORD_MODE) w = 1;
        else w = word_length;
        
        word_graph->add_edges(from, to, w, words[i]);
    }
    
}

void core::get_dp_result() {
    for (int i = (int) word_graph -> topo_result.size() - 1; i >= 0; i --) {
        int u = word_graph -> topo_result.at(i);
        for (int j = word_graph -> head[u]; j; j = word_graph -> next[j]) {
            int v = word_graph -> edges[j].to;
            int dp_result_v = dp_result[v] + word_graph -> edges[j].weight + get_first_self_loop_weight(v);
			int dp_result_u = dp_result[u];// + get_first_self_loop_weight(u);
            if (dp_result_v > dp_result_u) {
                dp_result[u] = dp_result_v;
                dp_next[u] = j;
            }
        }
    }
}

int core::get_first_self_loop_weight(int node)
{
    return word_graph->self_loop_edges[node].size() > 0 ? word_graph->edges[word_graph->self_loop_edges[node][0]].weight : 0;
}

int core::get_ans_loop(char* result[], int head, int tail) {
    return word_graph->force_dfs(result, head, tail);
}

int core::get_ans(char* result[], int head, int tail){
    get_dp_result();
    int ans = 0, from = -1;
    if (mod == ORD || mod == TAIL) {
        for (int i = 0; i < MAX_NODE; i ++) {
            int dp_result_i = dp_result[i] + get_first_self_loop_weight(i);
            if (dp_result_i > ans) {
                ans = dp_result_i;
                from = i;
            }
        }
    } else if (mod == HEAD || mod == HEAD_TAIL) {
        //from = char_to_int(mod); //bugfix: head -> mod
        from = head;
        ans = dp_result[from] + get_first_self_loop_weight(from);
    }
    
	if (from == -1)
		return 0; // not found
    int node = from, cnt = 0;
    while (dp_next[node]) {
        // if node has self loops, these words must be included
        // TODO >= 1 or == 1 ??
        if (word_graph->self_loop_edges[node].size() >= 1)
        {
            for (auto self_loop : word_graph->self_loop_edges[node])
            {
                result[cnt++] = word_graph->edges[self_loop].word;
            }
        }
        // normal results
        result[cnt ++] = word_graph -> edges[dp_next[node]].word;
        node = word_graph -> edges[dp_next[node]].to;
    }
	if (word_graph->self_loop_edges[node].size() >= 1 && cnt > 0)
	{
		for (auto self_loop : word_graph->self_loop_edges[node])
		{
			result[cnt++] = word_graph->edges[self_loop].word;
		}
	}
    //return ans;
	return cnt;
}


int core::main_func(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int cal_mod) {
    
    this->head = head;
    this->tail = tail;
    make_graph(words, len, cal_mod);
    
	// judge head and tail
	if (head && !isalpha(head) || tail && !isalpha(tail))
		throw std::invalid_argument("Core: invalid head or tail");
	if (head) 
	{
		head = tolower(head);
		if (!word_graph->vis_node[char_to_int(head)])
		{
			return 0;
		}
	}
	if (tail) 
	{
		tail = tolower(tail);
		if (!word_graph->vis_node[char_to_int(tail)])
		{
			return 0;
		}
	}
	init_dp(head, tail, enable_loop);
    
    bool ok = word_graph -> topological_sort();
    int ans = 0;
    if (!ok) {
        if (enable_loop) {

            ans = get_ans_loop(result, char_to_int(head), char_to_int(tail));
        } else {
            //ans = error(HAS_LOOP);
			throw std::invalid_argument("Core: loop deteced in words, you need to use -r to parse.");
        }
    } else {
        ans = get_ans(result, char_to_int(head), char_to_int(tail));
    }
    
    return ans;
}


void core::delete_word_from_words(char* words[], int len, char* word) {
    int indx = -1;
    for (int i = 0; i < len; i ++) {
        if (!strcmp(words[i], word)) {
            indx = i; break;
        }
    }
    if (indx >= 0) {
        for (int j = indx; j < len - 1; j ++) {
            words[j] = words[j + 1];
        }
    }
    //add test
}

int core::delete_repeat_words(char* words[], int len) {
	this->orig_words = std::vector<char*>(words, words + len);
	std::sort(orig_words.begin(), orig_words.end(), [](const char* lhs, const char* rhs) {
		return strcmp(lhs, rhs) < 0;
	});
	orig_words.erase(std::unique(orig_words.begin(), orig_words.end(), [](const char* lhs, const char* rhs) {
		return strcmp(lhs, rhs) == 0;
	}), orig_words.end());
	for (auto& string : orig_words)
		this->non_repeat_words.push_back(string);
	return (int)orig_words.size();

}

int core::common_interface(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int mod) {
	
	
	len = delete_repeat_words(words, len);
	words = this->non_repeat_words.data();
    int ans =  main_func(words, len, result, head, tail, enable_loop, mod);
    while (ans == 1 && len > 1) {
        init();
        delete_word_from_words(words, len, result[0]);
        ans = main_func(words, len - 1, result, head, tail, enable_loop, mod);
		len --;
    }
    
	if (ans <= 1)
		return 0;
	//else
	return ans;
    //NO_LOOP defination at "core.h": -2
}



int core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    return common_interface(words, len, result, head, tail, enable_loop, WORD_MODE);
}

int core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    return common_interface(words, len, result, head, tail, enable_loop, CHAR_MODE);
}
