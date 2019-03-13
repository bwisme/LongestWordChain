#pragma once
#include "cxxopts.hpp"
#include <vector>
#include <cctype>
#include <cstdio>

#include <stdexcept>
#include <iostream>
#include <fstream>
#include "windows.h"


#define MAX_WORD 10010
#define MAX_WORD_LENGTH 2048
#define WORD_MODE 1
#define CHAR_MODE 2

typedef int(*core_func_ptr)(char**, int, char**, char, char, bool);

class base
{
public:
    base();
    ~base();
    
    base(int argc, char** argv);



    int run();
    int read_file(std::string filename); //read words into inputs
    int parse_arguments(std::string* filename, int* mode, char* head, char* tail, bool* enable_loop);
	
	std::vector<char*> inputs; //input words, pass input.data() as char**
	std::vector<std::string> strings;
	//std::vector<char*> outputs; //results
	char* outputs[10010];

	//core* core_instance; // call core apis
	int argc;
	char** argv;
	std::string filename;
	int mode;
	char head;
	char tail;
	bool enable_loop;

private:
    cxxopts::Options options = cxxopts::Options("LongestWordChain", "Find the longest word chain in a text file.")
	std::ofstream solution;


};
