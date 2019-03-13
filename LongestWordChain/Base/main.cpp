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
        �쳣������
        1. ������γ��֣�ÿ���������ֻ�ܳ���һ��
        2. w��c�ظ����֣���û�г���
        3. h��tû�к������
        4. w��c��r�в���
        5. h��t�Ĳ������ǵ����ַ���������ĸ��a-z A-Z)
        6. ����û�������ļ������������˶���ļ���
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