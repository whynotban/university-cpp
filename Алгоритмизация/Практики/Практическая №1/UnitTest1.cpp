#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(Test_QueueSize_After_Push)
        {
            std::queue<int> q;
            for (int i = 0; i < 100; i++) {
                q.push(i);
            }
            Assert::AreEqual((int)q.size(), 100);
        }

        TEST_METHOD(Test_QueueFront_Element)
        {
            std::queue<int> q;
            q.push(42);
            q.push(99);
            Assert::AreEqual(q.front(), 42);
        }

        TEST_METHOD(Test_QueueBack_Element)
        {
            std::queue<int> q;
            q.push(42);
            q.push(99);
            Assert::AreEqual(q.back(), 99);
        }

        TEST_METHOD(Test_Queue_Empty)
        {
            std::queue<int> q;
            Assert::IsTrue(q.empty());
            q.push(1);
            Assert::IsFalse(q.empty());
        }

        TEST_METHOD(Test_Time_Grows_With_N)
        {
            double t1 = measure_queue_push(1000);
            double t2 = measure_queue_push(100000);
            Assert::IsTrue(t2 > t1);
        }

        TEST_METHOD(Test_Large_Push)
        {
            std::queue<int> q;
            for (int i = 0; i < 1000000; i++) {
                q.push(i);
            }
            Assert::AreEqual((int)q.size(), 1000000);
            Assert::AreEqual(q.front(), 0);
            Assert::AreEqual(q.back(), 999999);
        }
    };
}