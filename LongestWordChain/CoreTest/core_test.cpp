#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Core/core_dll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(GetChainWordTest)
	{
	public:

		TEST_METHOD(GetChainCharTest1)
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
		TEST_METHOD(GetChainCharTest2)
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
		TEST_METHOD(GetChainCharTest3)
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
		TEST_METHOD(GetChainCharTest4)
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
		TEST_METHOD(GetChainCharTest5)
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
		TEST_METHOD(GetChainCharTest6)
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




	};
	TEST_CLASS(GetChainCharTest) {};
	TEST_CLASS(RingTest) {};
}