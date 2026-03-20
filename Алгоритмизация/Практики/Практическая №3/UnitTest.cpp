#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
TEST_CLASS(UnitTest1)
{
public:

TEST_METHOD(Test_CombSort_Random)
{
    std::vector<int> arr = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    combSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_CombSort_Sorted)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    combSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_CombSort_Reverse)
{
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    combSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_ShellSort_Random)
{
    std::vector<int> arr = {12, 34, 54, 2, 3};
    std::vector<int> expected = {2, 3, 12, 34, 54};
    shellSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_ShellSort_Sorted)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    shellSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_ShellSort_Reverse)
{
    std::vector<int> arr = {9, 7, 5, 3, 1};
    std::vector<int> expected = {1, 3, 5, 7, 9};
    shellSort(arr);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_QuickSort_Random)
{
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    std::vector<int> expected = {1, 5, 7, 8, 9, 10};
    quickSort(arr, 0, arr.size() - 1);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_QuickSort_Sorted)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    quickSort(arr, 0, arr.size() - 1);
    Assert::IsTrue(arr == expected);
}

TEST_METHOD(Test_QuickSort_SingleElement)
{
    std::vector<int> arr = {42};
    std::vector<int> expected = {42};
    quickSort(arr, 0, arr.size() - 1);
    Assert::IsTrue(arr == expected);
}
};
}
