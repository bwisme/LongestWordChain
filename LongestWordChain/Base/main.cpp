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
        �쳣������
        1. ������γ��֣�ÿ���������ֻ�ܳ���һ��
        2. w��c�ظ����֣���û�г���
        3. h��tû�к������
        4. w��c��r�в���
        5. h��t�Ĳ������ǵ����ַ���������ĸ��a-z A-Z)
        6. ����û�������ļ������������˶���ļ���
    */

    return 0;
}