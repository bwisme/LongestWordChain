#pragma once
#include "graph.h"

class core
{
public:
    core();
    ~core();
    
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

private:

    int dp_result[MAX_NODE];
    int dp_pre[MAX_EDGE];
    void init_dp(char head, char tail, bool enable_loop);
    graph* word_graph;


    
};

