#pragma once
#include "graph.h"
const int INF = (int)1e9;

const int ORD = 0; //没有指定起点和终点 普通模式
const int HEAD = 1; //指定起点
const int TAIL = 2; //指定终点
const int HEAD_TAIL = 3; //指定起点和终点

const int WORD = 0;
const int CHAR = 1;


#define HAS_LOOP -1
//错误种类 都是负数


class core
{
public:
    core();
    ~core();
    
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

private:
    int mod; //计算采用哪种模式 可选有：ORD HEAD TAIL HEAD_TAIL
    graph* word_graph;
    int dp_result[MAX_NODE]; //dp的结果
    int dp_next[MAX_EDGE]; //dp过程中记录的每个点的下一条边
    void init_dp(char head, char tail, bool enable_loop); //计算前进行初始化
    void make_graph(char* words[], len, int mod);
    int char_to_int(char ch);
    void get_dp_result();
    int get_ans(char* result[]);
    int main_func(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int cal_mod);
    int error(int err_no);
    
};

