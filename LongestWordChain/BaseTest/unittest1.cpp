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
			// TODO: �ڴ�������Դ���
            base b;
            int res = b.read_file("a.txt");
            Assert::AreEqual(res, 0);
		}

	};
}