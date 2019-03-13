#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Core/core_dll.h"
#include "../Core/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace exception_test
{
	void invalid_char_test()
	{
		char* words[] =
		{
			"a12345",
			"avdc",
			"fewt"
		};
		char* results[100];
		int len = get_chain_word(words, 3, results, 0, 0, true);
	}
}

namespace CoreTest
{
	TEST_CLASS(GetChainWordTest)
	{
	public:
		TEST_METHOD(Example1)
		{
			// test file exist

			char* words[] =
			{
				"algebra",
				"apple",
				"zoo",
				"elephant",
				"under",
				"fox",
				"dog",
				"moon",
				"leaf",
				"trick",
				"pseudopseudohypoparathyroidism"
			};
			char* results[100];
			get_chain_word(words, 11, results, 0, 0, false);
			Assert::AreEqual(results[0], "algebra");
			Assert::AreEqual(results[1], "apple");
			Assert::AreEqual(results[2], "elephant");
			Assert::AreEqual(results[3], "trick");

		}



		TEST_METHOD(GetChainWordTest5)
		{
			// test file exist

			char* words[] =
			{
				"aba",
				"atb"

			};
			char* results[100];
			int len = get_chain_word(words, 2, results, 0, 0, false);
			Assert::AreEqual(2, len);
		}
		TEST_METHOD(GetChainWordTest6)
		{
			// test file exist

			char* words[] =
			{
				"axb",
				"bya",
				"axb"
			};
			char* results[100];
			int len = get_chain_word(words, 3, results, 0, 0, true);
			Assert::AreEqual(2, len);
		}

		TEST_METHOD(HeadTailTest1)
		{

			char* words[] =
			{
				"aab",
				"bbc",
				"cce",
				"eee",
				"fgg",
				"ghh",
				"hii",
				"ion",
				"nom"

			};
			char* results[100];
			int len = get_chain_word(words, 9, results, 'a', 'e', false);
			Assert::AreEqual(4, len);
			Assert::AreEqual(results[0], "aab");
			Assert::AreEqual(results[1], "bbc");
			Assert::AreEqual(results[2], "cce");
			Assert::AreEqual(results[3], "eee");
		}



	};
	TEST_CLASS(GetChainCharTest) {};
	TEST_CLASS(RingTest) 
	{
	public:
		TEST_METHOD(ExampleWithRing)
		{
			// test file exist
			char* words[] =
			{
				"element",
				"heaven",
				"table",
				"teach",
				"talk"
			};
			char* results[100];
			get_chain_word(words, 5, results, 0, 0, true);
			Assert::AreEqual(results[0], "table");
			Assert::AreEqual(results[1], "element");
			Assert::AreEqual(results[2], "teach");
			Assert::AreEqual(results[3], "heaven");

		}
		TEST_METHOD(GetChainWordTest3)
		{
			// test file exist
			char* words[] =
			{
				"element",
				"heaven",
				"hahahah",
				"hoh",
				"table",
				"teach",
				"talk"
			};
			char* results[100];
			get_chain_word(words, 7, results, 0, 0, true);
			Assert::AreEqual(results[0], "table");
			Assert::AreEqual(results[1], "element");
			Assert::AreEqual(results[2], "teach");
			Assert::AreEqual(results[5], "heaven");

		}
		TEST_METHOD(GetChainWordTest4)
		{
			// test file exist

			char* words[] =
			{
				"aab",
				"bac",
				"cad",
				"dae",
				"eaf",
				"fag",
				"gah",
				"hai",
				"iaj",
				"jak",
				"kaa",
				"oar",
				"rat",
				"qaz"
			};
			char* results[100];
			int len = get_chain_word(words, 14, results, 0, 0, true);
			Assert::AreEqual(11, len);

		}
	};

	TEST_CLASS(ExceptionTest)
	{
	public:
		TEST_METHOD(WordsException1)
		{

			char* words[] =
			{
				"aaB",
				"bac",
				"caD",
				"dae",
				"eaf",
				"fag",
				"gah",
				"hai",
				"iAj",
				"jak",
				"kaa",
				"oar",
				"rat",
				"qaz"
			};
			char* results[100];
			int len = get_chain_word(words, 14, results, 0, 0, true);
			Assert::AreEqual(11, len);
			Assert::AreEqual(results[0], "aab");
			Assert::AreEqual(results[1], "bac");
			Assert::AreEqual(results[2], "cad");
			Assert::AreEqual(results[3], "dae");
			Assert::AreEqual(results[4], "eaf");
			Assert::AreEqual(results[5], "fag");
			Assert::AreEqual(results[6], "gah");
			Assert::AreEqual(results[7], "hai");
			Assert::AreEqual(results[8], "iaj");
			Assert::AreEqual(results[9], "jak");
			Assert::AreEqual(results[10], "kaa");
		}

		TEST_METHOD(WordsException3)
		{

			char* words[] =
			{
				"aaB",
				"fac",
				"defg",
				"hijk"
			};
			char* results[100];
			int len;
			len = get_chain_word(words, 4, results, 0, 'z', false);
			Assert::AreEqual(0, len);
			len = get_chain_char(words, 4, results, 0, 'z', false);
			Assert::AreEqual(0, len);
			len = get_chain_word(words, 4, results, 'z', 0, false);
			Assert::AreEqual(0, len);
			len = get_chain_char(words, 4, results, 'z', 0, false);
			Assert::AreEqual(0, len);
			len = get_chain_word(words, 4, results, 'r', 'z', false);
			Assert::AreEqual(0, len);
			len = get_chain_char(words, 4, results, 'r', 'z', false);
			Assert::AreEqual(0, len);

		}






		TEST_METHOD(WordsException2)
		{
			Assert::ExpectException<std::invalid_argument>([&] {exception_test::invalid_char_test(); });
			try
			{
				exception_test::invalid_char_test();
			}
			catch (const std::exception& e)
			{
				Assert::AreEqual("Core: invalid char in words", e.what());
			}
		}



	};
}