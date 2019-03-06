#pragma once
#include "cxxopts.hpp"
#include <vector>
#include <cctype>


#define MAX_WORD 10010
#define MAX_WORD_LENGTH 2048


class base
{
public:
    base();
    ~base();

    char** read_file(std::string filename);

private:
    cxxopts::Options options = cxxopts::Options("LongestWordChain", "Find the longest word chain in a text file.");

    int parse_arguments(std::string* filename, char* head, char* tail, bool* enable_loop);
    


};
