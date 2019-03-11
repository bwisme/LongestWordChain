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

        }


    };
}