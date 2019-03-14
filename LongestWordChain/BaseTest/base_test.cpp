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
            int res = b.read_file("../test_files/read_test_1.txt");
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
				int res = b.read_file("../test_files/word_too_long.txt");
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

		TEST_METHOD(ExceptionTest1)
		{
			try
			{
				int argc = 4;
				char* argv[] = { "WordList.exe","-w", "-w", "a.txt"};
				base b(argc, argv);
				std::string filename;
				int mode;
				char head, tail;
				bool enable_loop;
				b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
				Assert::Fail();
			}
			catch (const std::invalid_argument& e)
			{
				Assert::AreEqual("parse_arguments: Too much -w appeared", e.what());
			}

		}
		TEST_METHOD(ExceptionTest2)
		{
			try
			{
				int argc = 2;
				char* argv[] = { "WordList.exe","-w" };
				base b(argc, argv);
				std::string filename;
				int mode;
				char head, tail;
				bool enable_loop;
				b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
				Assert::Fail();
			}
			catch (const std::invalid_argument& e)
			{
				Assert::AreEqual("parse_arguments: Too much -w appeared", e.what());
			}

		}
	};
}