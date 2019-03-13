#include <iostream>

#include "cxxopts.hpp"
#include "base.h"


int main(int argc, char* argv[])
{
    


    ////parse arguments
    //auto result = options.parse(argc, argv);

    ////example of retriving results
    //// TODO handle exceptions
   
    //std::cout << result.count("w") << std::endl;
    //std::cout << result["w"].as<bool>() << std::endl;
    //std::cout << result["c"].as<bool>() << std::endl;
    //std::cout << result["h"].as<char>() << std::endl;
    //std::cout << result.count("file-name") << std::endl;
    //std::cout << result["file-name"].as<std::string>() << std::endl;

    /*
        异常包括：
        1. 参数多次出现，每个参数最多只能出现一次
        2. w和c重复出现，或都没有出现
        3. h和t没有后跟参数
        4. w、c和r有参数
        5. h和t的参数不是单个字符，或不是字母（a-z A-Z)
        6. 最终没有输入文件名，或输入了多个文件名
    */

    //TODO pass processed arguments to Core and wait for results :)
    try
    {
        //core core_instance = core();
        base base_instance(argc, argv);
		std::clock_t start;
		double duration;

		start = std::clock();

		base_instance.run();

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		std::cout << "Time cost: " << duration << '\n';
        
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}