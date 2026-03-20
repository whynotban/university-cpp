#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
TEST_CLASS(UnitTest1)
{
public:

TEST_METHOD(Test_Simpson_N10)
{
    double result = simpson(2.0, 7.0, 10);
    double expected = 1220.0 / 3.0;
    double epsilon = 1.0;
    Assert::AreEqual(expected, result, epsilon, L"N=10: значения совпали с точностью.");
}

TEST_METHOD(Test_Simpson_N100)
{
    double result = simpson(2.0, 7.0, 100);
    double expected = 1220.0 / 3.0;
    double epsilon = 0.01;
    Assert::AreEqual(expected, result, epsilon, L"N=100: значения совпали с точностью.");
}

TEST_METHOD(Test_Simpson_N1000)
{
    double result = simpson(2.0, 7.0, 1000);
    double expected = 1220.0 / 3.0;
    double epsilon = 0.0001;
    Assert::AreEqual(expected, result, epsilon, L"N=1000: значения совпали с точностью.");
}
};
}
