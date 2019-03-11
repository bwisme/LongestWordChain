#include "base.h"
base::base()
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
    options.parse_positional({ "file-name" });

}

base::~base()
{
}

int base::parse_arguments(std::string * filename, char * head, char * tail, bool * enable_loop)
{
    try
    {
        if (filename == nullptr)
        {
            return -1;
        }
        else
        {
            return 0;
        }


    }
    catch (...)
    {

    }
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
                word_buffer[char_count] = ch;
                char_count++;
            }
        } while (!feof(file));

        // transfer strings(vector) to words(char**)

        for (const auto& string : this->strings)
            this->inputs.push_back(string.c_str());

        

        return 0;
    }
    else {
        // FILE reading error
        return err;
    }
}
