#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
    TEST_CLASS(UnitTest3)
    {
    public:
        TEST_METHOD(TestExample1)
        {
            std::vector<int> nums = { 5, 7, 2, 4, 9, 6 };
            auto result = findMinMax(nums, 0, nums.size() - 1);
            Assert::AreEqual(2, result.first);
            Assert::AreEqual(9, result.second);
        }

        TEST_METHOD(TestSingleElement)
        {
            std::vector<int> nums = { 42 };
            auto result = findMinMax(nums, 0, nums.size() - 1);
            Assert::AreEqual(42, result.first);
            Assert::AreEqual(42, result.second);
        }

        TEST_METHOD(TestTwoElements)
        {
            std::vector<int> nums = { 10, -5 };
            auto result = findMinMax(nums, 0, nums.size() - 1);
            Assert::AreEqual(-5, result.first);
            Assert::AreEqual(10, result.second);
        }
    };
}
