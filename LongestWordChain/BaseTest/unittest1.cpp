#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseTest
{		
	TEST_CLASS(BaseTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
            base b;
            char** words = b.read_file("a.txt");
            Assert::IsNull(words);
		}

	};
}