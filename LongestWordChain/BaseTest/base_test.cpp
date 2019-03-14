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
			
				int argc = 4;
				char* argv[] = { "base.exe", "-w", "-r", "a.txt" };
				base b(argc, argv);
				std::string filename;
				int mode;
				char head, tail;
				bool enable_loop;
				b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
				Assert::AreEqual(filename, std::string("a.txt"));
				Assert::AreEqual(enable_loop, true);
			
		}

		TEST_METHOD(NormalTest2)
		{
			int argc = 4;
			char* argv[] = { "base.exe", "-c", "-r", "a.txt"};
			base b(argc, argv);
			std::string filename;
			int mode;
			char head, tail;
			bool enable_loop;
			b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
			Assert::IsTrue(enable_loop);
			Assert::AreEqual(filename, std::string("a.txt"));
		}
		TEST_METHOD(NormalTest3)
		{
			int argc = 6;
			char* argv[] = { "base.exe", "-c", "-r", "-h", "a", "a.txt" };
			base b(argc, argv);
			std::string filename;
			int mode;
			char head, tail;
			bool enable_loop;
			b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
			Assert::IsTrue(enable_loop);
			Assert::AreEqual(filename, std::string("a.txt"));
			Assert::AreEqual(head, 'a');
		}
		TEST_METHOD(NormalTest4)
		{
			int argc = 6;
			char* argv[] = { "base.exe", "-c", "-r", "-t", "a", "a.txt" };
			base b(argc, argv);
			std::string filename;
			int mode;
			char head, tail;
			bool enable_loop;
			b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
			Assert::IsTrue(enable_loop);
			Assert::AreEqual(filename, std::string("a.txt"));
			Assert::AreEqual(tail, 'a');
		}
		TEST_METHOD(NormalTest5)
		{
			int argc = 8;
			char* argv[] = { "base.exe", "-c", "-r", "-h", "a", "-t", "b", "a.txt" };
			base b(argc, argv);
			std::string filename;
			int mode;
			char head, tail;
			bool enable_loop;
			b.parse_arguments(&filename, &mode, &head, &tail, &enable_loop);
			Assert::IsTrue(enable_loop);
			Assert::AreEqual(filename, std::string("a.txt"));
			Assert::AreEqual(head, 'a');
			Assert::AreEqual(tail, 'b');
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
				Assert::AreEqual("parse_arguments: No filename detected", e.what());
			}

		}
		TEST_METHOD(ExceptionTest3)
		{
			try
			{
				int argc = 2;
				char* argv[] = { "WordList.exe","a.txt" };
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
				Assert::AreEqual("parse_arguments: No -w and -c appeared", e.what());
			}

		}
		TEST_METHOD(ExceptionTest4)
		{
			try
			{
				int argc = 4;
				char* argv[] = { "WordList.exe","-w", "-c", "a.txt" };
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
				Assert::AreEqual("parse_arguments: -w and -c can't be set at the same time", e.what());
			}

		}
		TEST_METHOD(ExceptionTest5)
		{
			try
			{
				int argc = 4;
				char* argv[] = { "WordList.exe","-c", "-c", "a.txt" };
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
				Assert::AreEqual("parse_arguments: Too much -c appeared", e.what());
			}
		}
		TEST_METHOD(ExceptionTest6)
		{
			try
			{
				int argc = 7;
				char* argv[] = { "WordList.exe","-c", "-h","a","-h","b", "a.txt" };
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
				Assert::AreEqual("parse_arguments: Too much -h appeared", e.what());
			}
		}
		TEST_METHOD(ExceptionTest7)
		{
			try
			{
				int argc = 7;
				char* argv[] = { "WordList.exe","-c", "-t","t","-t","f", "a.txt" };
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
				Assert::AreEqual("parse_arguments: Too much -t appeared", e.what());
			}
		}
		TEST_METHOD(ExceptionTest8)
		{
			try
			{
				int argc = 5;
				char* argv[] = { "WordList.exe","-c", "a.txt", "-r","-r" };
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
				Assert::AreEqual("parse_arguments: Too much -r appeared", e.what());
			}
		}

	
	};
}