#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
    TEST_CLASS(UnitTest4)
    {
    public:
        TEST_METHOD(TestExample1)
        {
            std::vector<std::vector<int>> graph = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}
            };
            std::vector<int> color(3, 0);
            Assert::IsTrue(graphColoring(graph, 3, color, 3));
            Assert::AreEqual(1, color[0]);
            Assert::AreEqual(2, color[1]);
            Assert::AreEqual(3, color[2]);
        }

        TEST_METHOD(TestImpossible)
        {
            std::vector<std::vector<int>> graph = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}
            };
            std::vector<int> color(3, 0);
            Assert::IsFalse(graphColoring(graph, 2, color, 3));
        }
    };
}
