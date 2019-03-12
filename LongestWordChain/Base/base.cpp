#include "base.h"
base::base()
{

}

base::~base()
{
}

base::base(core * core_instance, int argc, char** argv)
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
        ;
    options.parse_positional({ "filename" });

    
    this->core_instance = core_instance;
    this->argc = argc;
    this->argv = argv;
}

int base::parse_arguments(std::string * filename, int * mode, char * head, char * tail, bool * enable_loop)
{
    try
    {
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

        //filename
        *filename = result["filename"].as<std::string>();
        return 0;
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

int base::run()
{
    parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
    read_file(filename);
    if (mode == WORD_MODE)
        core_instance->gen_chain_word(inputs.data(), inputs.size(), outputs, head, tail, enable_loop);
    else
        core_instance->gen_chain_char(inputs.data(), inputs.size(), outputs, head, tail, enable_loop);
    return 0;
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
