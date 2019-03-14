#include "base.h"
base::base()
{

}

base::~base()
{
	solution.close();
}

base::base(int argc, char** argv)
{
    // Use cxxopts library for argument parsing, this is a lightweight header file library
    // repo: https://github.com/jarro2783/cxxopts
    //cxxopts::Options options("LongestWordChain", "Find the longest word chain in a text file.");
    options.add_options()
        ("w,by-word", "By maximum words")
        ("c,by-char", "By maximum chars")
        ("h,head", "Specify head character", cxxopts::value<char>())
        ("t,tail", "Specify tail character", cxxopts::value<char>())
        ("r,ring", "Permit word ring")
        ("filename", "Filename as-is", cxxopts::value<std::string>())
		("could-not-exist", "for debugging", cxxopts::value<std::vector<std::string>>())
        ;
    options.parse_positional({ "filename", "could-not-exist" });

    this->argc = argc;
    this->argv = argv;
	solution.open("solution.txt", std::ios::out);
}

int base::parse_arguments(std::string * filename, int * mode, char * head, char * tail, bool * enable_loop)
{
    //try
    //{
	auto result = this->options.parse(this->argc, this->argv);

	// parse
	bool mode_selected = false;
	if (result.count("w"))
	{
		if (result.count("w") > 1)
			throw std::invalid_argument("parse_arguments: Too much -w appeared");
		else
		{
			mode_selected = true;
			*mode = WORD_MODE;
		}
	}
	if (result.count("c"))
	{
		if (mode_selected)
			throw std::invalid_argument("parse_arguments: -w and -c can't be set at the same time");
		if (result.count("c") > 1)
			throw std::invalid_argument("parse_arguments: Too much -c appeared");
		else
		{
			mode_selected = true;
			*mode = CHAR_MODE;
		}
	}
	if (!mode_selected)
	{
		throw std::invalid_argument("parse_arguments: No -w and -c appeared");
	}

	if (result.count("h"))
	{
		if (result.count("h") > 1)
			throw std::invalid_argument("parse_arguments: Too much -h appeared");
		else
		{
			*head = result["h"].as<char>();
		}
	}
	else
	{
		*head = 0;
	}
	if (result.count("t"))
	{
		if (result.count("t") > 1)
			throw std::invalid_argument("parse_arguments: Too much -t appeared");
		else
		{
			*tail = result["t"].as<char>();
		}
	}
	else
	{
		*tail = 0;
	}
	if (result.count("r"))
	{
		if (result.count("r") > 1)
			throw std::invalid_argument("parse_arguments: Too much -r appeared");
		else
		{
			*enable_loop = true;
		}
	}
	else
	{
		*enable_loop = false;
	}
	if (result.count("could-not-exist"))
	{
		std::cout << "You seem to input more than one filename, those files would not be parsed" << std::endl;
	}
	//filename
	if (result.count("filename"))
		*filename = result["filename"].as<std::string>();
	else
		throw std::invalid_argument("parse_arguments: No filename detected");
	return 0;
    //}
    //catch (const cxxopts::OptionException& e)
    //{
    //    std::cout << "Error parsing options: " << e.what() << std::endl;
    //    exit(1);
    //}
}

int base::run()
{
	HINSTANCE hCoreDLL = LoadLibrary("Core.dll");

	if (!hCoreDLL) {
		std::cout << "could not load the dynamic library" << std::endl;
		return EXIT_FAILURE;
	}
	
	parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
    read_file(filename);
	int len = 0;
	core_func_ptr core_func;
	if (mode == WORD_MODE)
	{
		core_func = (core_func_ptr)GetProcAddress(hCoreDLL, "get_chain_word");
		if (!core_func) {
			std::cout << "could not locate the function: get_chain_word" << std::endl;
			return EXIT_FAILURE;
		}
	}
	else 
	{
		core_func = (core_func_ptr)GetProcAddress(hCoreDLL, "get_chain_char");
		if (!core_func) {
			std::cout << "could not locate the function: get_chain_char" << std::endl;
			return EXIT_FAILURE;
		}
	}

	len = core_func(inputs.data(), inputs.size(), outputs, head, tail, enable_loop);

	std::cout << "start output, len is " << len << std::endl;
	if (len == 0)
		std::cout << "no valid answer found!" << std::endl;
	for (int i = 0; i < len; i++)
	{
		solution << std::string(outputs[i]) << std::endl;
	}
	
	return EXIT_SUCCESS;
}


int base::read_file(std::string filename)
{
    std::vector<std::string> strings;

    //char* words[MAX_WORD];
    char word_buffer[MAX_WORD_LENGTH];
    FILE* file;
    errno_t err;
    if ((err = fopen_s(&file, filename.c_str(), "r")) == 0) {
        // opened, split words into a vector<string>
        char ch;
        int char_count = 0;
		if (!file)
		{
			throw std::invalid_argument("read_file: File open failed");
		}
        do 
        {
            ch = fgetc(file);
            if (!isalpha((int)ch))
            {
                if (char_count > 0)
                {
                    word_buffer[char_count] = '\0';
                    std::string str(word_buffer);
                    this->strings.push_back(str);
                    char_count = 0;
                }
                else
                    continue;
            }
            else
            {
                word_buffer[char_count] = tolower((int)ch);
                char_count++;
                if (char_count >= MAX_WORD_LENGTH)
                    throw std::invalid_argument("read_file: Exceed maximum word length: 2048");

            }
        } while (!feof(file));

        // transfer strings(vector) to words(char**)

        for (auto& string : this->strings)
            this->inputs.push_back(&string.front());

        return 0;
    }
    else {
        // FILE reading error
        //return err;
        throw std::invalid_argument("read_file: File open failed");
    }
}
