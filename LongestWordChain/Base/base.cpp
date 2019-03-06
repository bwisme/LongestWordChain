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