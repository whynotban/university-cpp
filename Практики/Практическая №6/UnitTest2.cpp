#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>
#include <stdexcept>
#include "../cpp-test1/main.cpp" 

#define UNIT_TESTING
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(Test_ValidData_S_Is_Max)
        {
            double x = 1.0;
            double y = 1.0;
            double R, S, C;

            calculate_values(x, y, R, S, C);

            double expected_R = 1.0;
            double expected_S = 2.0;
            double expected_C = 2.0;

            Assert::AreEqual(expected_R, R, 0.001);
            Assert::AreEqual(expected_S, S, 0.001);
            Assert::AreEqual(expected_C, C, 0.001);
        }

        TEST_METHOD(Test_ValidData_R_Is_Max)
        {
            double x = 0.5;
            double y = 1.0;
            double R, S, C;

            calculate_values(x, y, R, S, C);

            Assert::IsTrue(R > S);
            Assert::AreEqual(R, C, 0.001);
        }

        TEST_METHOD(Test_Invalid_Y_Zero)
        {
            double x = 1.0;
            double y = 0.0;
            double R, S, C;

            auto func = [x, y, &R, &S, &C] { calculate_values(x, y, R, S, C); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(Test_Invalid_Y_Negative)
        {
            double x = 1.0;
            double y = -5.0;
            double R, S, C;

            auto func = [x, y, &R, &S, &C] { calculate_values(x, y, R, S, C); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(Test_Invalid_X_Zero)
        {
            double x = 0.0;
            double y = 5.0;
            double R, S, C;

            auto func = [x, y, &R, &S, &C] { calculate_values(x, y, R, S, C); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(Test_Invalid_X_MultipleOfFour)
        {
            double x = 4.0;
            double y = 5.0;
            double R, S, C;

            auto func = [x, y, &R, &S, &C] { calculate_values(x, y, R, S, C); };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };
}
