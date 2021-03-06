#pragma once
#include <cctype>
#include <algorithm>

#include "graph.h"

const int INF = (int)1e9;

const int ORD = 0; //没有指定起点和终点 普通模式
const int HEAD = 1; //指定起点
const int TAIL = 2; //指定终点
const int HEAD_TAIL = 3; //指定起点和终点

const int WORD_MODE = 0;
const int CHAR_MODE = 1;


#define HAS_LOOP -1
//错误种类 都是负数
#define NO_LOOP -2


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
    char head, tail;
    int dp_result[MAX_NODE]; //dp的结果
    int dp_next[MAX_EDGE]; //dp过程中记录的每个点的下一条边
	std::vector<char*> orig_words;
	std::vector<char*> non_repeat_words;
    void init_dp(char head, char tail, bool enable_loop); //计算前进行初始化
    void make_graph(char* words[], int len, int mod);
    int char_to_int(char ch);
    void get_dp_result();
    int get_first_self_loop_weight(int node);
    int get_ans(char* result[], int head, int tail);
    int get_ans_loop(char* result[], int head, int tail);
    int main_func(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int cal_mod);

    void init();
	int delete_repeat_words(char* words[], int len);
    void delete_word_from_words(char* words[], int len, char* word);
    int common_interface(char* words[], int len, char* result[], char head, char tail, bool enable_loop, int mod);

};

