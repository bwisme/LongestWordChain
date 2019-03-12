#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Base/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseTest
{
    TEST_CLASS(CoreTest)
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
"aab",
"bac",
"cad",
"dae",
"eaa",
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
"kal",
"lam",
"man",
"nao",
"oap",
"paq",
"qag",
"gah",
"hai",
"iaj",
"jak",
"kal",
"lam",
"man",
"nao",
"oap",
"paq",
"qar",
"ras",
"sat",
"tau",
"uav",
"vaw",
"wax",
"xay",
"yaz",
"zar",
"raa",
"gar"

            };
            char* results[100];
            char* results2[100];
            int len = c.gen_chain_word(words, 44, results, 0, 'a', true);
            //int len2 = c.gen_chain_char(words, 44, results2, 0, 0, true);
            Assert::AreEqual(43, len);
            //Assert::AreEqual(129, len2);

        }




    };
}