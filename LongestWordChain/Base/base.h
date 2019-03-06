#pragma once
#include "cxxopts.hpp"


class base
{
public:
    base();
    ~base();



private:
    cxxopts::Options options = cxxopts::Options("LongestWordChain", "Find the longest word chain in a text file.");

    int parse_arguments(std::string* filename, char* head, char* tail, bool* enable_loop);
    char** read_file(std::string filename);


};
