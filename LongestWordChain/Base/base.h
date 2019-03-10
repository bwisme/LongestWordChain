#pragma once
#include "cxxopts.hpp"
#include <vector>
#include <cctype>
#include <cstdio>

//#include "core.h"


#define MAX_WORD 10010
#define MAX_WORD_LENGTH 2048


class base
{
public:
    base();
    ~base();
    
    //base(core* core_instance);

    std::vector<char*> inputs; //input words, pass input.data() as char**
    std::vector<char*> outputs; //results

    //core* core_instance; // call core apis

    int read_file(std::string filename); //read words into inputs

private:
    cxxopts::Options options = cxxopts::Options("LongestWordChain", "Find the longest word chain in a text file.");

    int parse_arguments(std::string* filename, char* head, char* tail, bool* enable_loop);
    


};
