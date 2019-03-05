#include <iostream>

#include "cxxopts.hpp"




int main(int argc, char* argv[])
{
    
    // Use cxxopts library for argument parsing, this is a lightweight header file library
    // repo: https://github.com/jarro2783/cxxopts
    
    cxxopts::Options options("LongestWordChain", "Find the longest word chain in a text file.");
    options.add_options()
        ("w,by-word", "By maximum words")
        ("c,by-char", "By maximum chars")
        ("h,head", "Specify head character", cxxopts::value<char>())
        ("t,tail", "Specify tail character", cxxopts::value<char>())
        ("r,ring", "Permit word ring")
        ("filename", "Filename as-is", cxxopts::value<std::string>())
        ;
    options.parse_positional({ "file-name" });

    //parse arguments
    auto result = options.parse(argc, argv);

    //example of retriving results
    // TODO handle exceptions
   
    std::cout << result.count("w") << std::endl;
    std::cout << result["w"].as<bool>() << std::endl;
    std::cout << result["c"].as<bool>() << std::endl;
    //std::cout << result["h"].as<char>() << std::endl;
    std::cout << result.count("file-name") << std::endl;
    std::cout << result["file-name"].as<std::string>() << std::endl;

    /*
        异常包括：
        1. 参数多次出现，每个参数最多只能出现一次
        2. w和c重复出现，或都没有出现
        3. h和t没有后跟参数
        4. w、c和r有参数
        5. h和t的参数不是单个字符，或不是字母（a-z A-Z)
        6. 最终没有输入文件名，或输入了多个文件名
    */

    return 0;
}