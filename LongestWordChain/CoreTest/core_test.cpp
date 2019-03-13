#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Core/core_dll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(GetChainWordTest)
	{
	public:
		TEST_METHOD(Example1)
		{
			// test file exist
			core c;
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
			c.gen_chain_word(words, 11, results, 0, 0, false);
			Assert::AreEqual(results[0], "algebra");
			Assert::AreEqual(results[1], "apple");
			Assert::AreEqual(results[2], "elephant");
			Assert::AreEqual(results[3], "trick");

		}



		TEST_METHOD(GetChainWordTest5)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"aba",
				"atb"

			};
			char* results[100];
			int len = c.gen_chain_word(words, 2, results, 0, 0, false);
			Assert::AreEqual(2, len);
		}
		TEST_METHOD(GetChainWordTest6)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"axb",
				"bya",
				"axb"
			};
			char* results[100];
			int len = c.gen_chain_word(words, 3, results, 0, 0, true);
			Assert::AreEqual(2, len);
		}

		TEST_METHOD(GetChainWordTest9)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"aaaaaaaaaaab",
			    "cd",
                "de"
			};
			char* results[100];
			int len = c.gen_chain_word(words, 3, results, 0, 0, true);
			Assert::AreEqual(2, len);
		}

		TEST_METHOD(GetChainWordTest8)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"aaaaaaaaaaab",
				"cd",
				"de"
			};
			char* results[100];
			int len = c.gen_chain_word(words, 3, results, 'a', 0, true);
			Assert::AreEqual(0, len);
		}

		TEST_METHOD(GetChainWordTest7)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"aaaaaaaaaaab",
				"cd",
				"de"
			};
			char* results[100];
			int len = c.gen_chain_word(words, 3, results, 0, 'e', true);
			Assert::AreEqual(2, len);
		}

		TEST_METHOD(GetChainWordTest10)
		{
			// test file exist
			core c;
			char* words[] =
			{
				"aaaaaaaaaaab",
				"cc",
				"cc", 
				"ce"
			};
			char* results[100];
			int len = c.gen_chain_char(words, 4, results, 0, 0, true);
			Assert::AreEqual(2, len);
		}

		TEST_METHOD(HeadTailTest1)
		{
			core c;
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
			int len = c.gen_chain_word(words, 9, results, 'a', 'e', false);
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
			core c;
			char* words[] =
			{
				"element",
				"heaven",
				"table",
				"teach",
				"talk"
			};
			char* results[100];
			c.gen_chain_word(words, 5, results, 0, 0, true);
			Assert::AreEqual(results[0], "table");
			Assert::AreEqual(results[1], "element");
			Assert::AreEqual(results[2], "teach");
			Assert::AreEqual(results[3], "heaven");

		}
		TEST_METHOD(GetChainWordTest3)
		{
			// test file exist
			core c;
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
			c.gen_chain_word(words, 7, results, 0, 0, true);
			Assert::AreEqual(results[0], "table");
			Assert::AreEqual(results[1], "element");
			Assert::AreEqual(results[2], "teach");
			Assert::AreEqual(results[5], "heaven");

		}
		TEST_METHOD(GetChainWordTest4)
		{
			// test file exist
			core c;
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
			int len = c.gen_chain_word(words, 14, results, 0, 0, true);
			Assert::AreEqual(11, len);

		}
	};

	TEST_CLASS(ExceptionTest)
	{
	public:
		TEST_METHOD(WordsException1)
		{
			core c;
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
			int len = c.gen_chain_word(words, 14, results, 'a', 0, true);
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
	};
}