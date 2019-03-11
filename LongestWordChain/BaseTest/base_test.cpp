#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Base/base.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseTest
{		
	TEST_CLASS(BaseTest1)
	{
	public:
		
		TEST_METHOD(ReadFileTest1)
		{
            // test file exist
            base b;
            int res = b.read_file("file_not_exist.txt");
            Assert::AreNotEqual(res, 0);
		}

        TEST_METHOD(ReadFileTest2)
        {
            // test simple read
            base b;
            int res = b.read_file("a.txt");
            Assert::AreEqual(res, 0);
            Assert::AreEqual(b.inputs[0], "first");
            Assert::AreEqual(b.inputs[1], "second");
            Assert::AreEqual(b.inputs[2], "third");
        }


	};
}