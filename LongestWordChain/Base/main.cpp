#include <iostream>

#include "cxxopts.hpp"
#include "base.h"


int main(int argc, char* argv[])
{

    try
    {
        base base_instance(argc, argv);

		std::clock_t start;
		double duration;
		start = std::clock();

		base_instance.run();

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Time cost: " << duration << '\n';
		return 0;
        
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
		exit(1);
    }

    
}