#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
    TEST_CLASS(UnitTest2)
    {
    public:
        TEST_METHOD(TestExample1)
        {
            std::vector<int> coins = {10, 3, 40, 1};
            Assert::AreEqual(4, minBanknotes(130, coins));
        }

        TEST_METHOD(TestExample2)
        {
            std::vector<int> coins = {7, 5};
            Assert::AreEqual(16, minBanknotes(100, coins));
        }

        TEST_METHOD(TestExample3)
        {
            std::vector<int> coins = {1};
            Assert::AreEqual(1, minBanknotes(1, coins));
        }

        TEST_METHOD(TestImpossible)
        {
            std::vector<int> coins = {2};
            Assert::AreEqual(-1, minBanknotes(3, coins));
        }
    };
}
