#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Base/base.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseTest
{		
	TEST_CLASS(ReadFileTest)
	{
	public:
		
		TEST_METHOD(ReadFileTest1)
		{
            // test file exist
			try
			{
				base b;
				int res = b.read_file("file_not_exist.txt");
				Assert::Fail();
			}
			catch (const std::invalid_argument& e)
			{
				Assert::AreEqual("read_file: File open failed", e.what());
			}
            
		}

        TEST_METHOD(ReadFileTest2)
        {
            // test simple read
			// including Capital letter conversion and special letter removal
            base b;
            int res = b.read_file("read_test_1.txt");
            Assert::AreEqual(res, 0);
            Assert::AreEqual(b.inputs[0], "first");
            Assert::AreEqual(b.inputs[1], "second");
            Assert::AreEqual(b.inputs[2], "third");
        }

		TEST_METHOD(ReadFileTest3)
		{
			// word is too long
			try
			{
				base b;
				int res = b.read_file("word_too_long.txt");
				Assert::Fail();

			}
			catch (const std::invalid_argument& e)
			{
				Assert::AreEqual("read_file: Exceed maximum word length: 2048", e.what());
			}

		}

	};

	TEST_CLASS(ParseArgumentsTest)
	{
	public:

		TEST_METHOD(NormalTest1)
		{

		}
	};
}