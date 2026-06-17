#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestSingleNode)
        {
            Solution sol;
            TreeNode* root = new TreeNode(10);
            Assert::AreEqual(10, sol.maxPathSum(root));
            delete root;
        }

        TEST_METHOD(TestExample1)
        {
            Solution sol;
            TreeNode* root = new TreeNode(1);
            root->left = new TreeNode(1);
            root->right = new TreeNode(2);
            Assert::AreEqual(4, sol.maxPathSum(root));
            delete root->left;
            delete root->right;
            delete root;
        }

        TEST_METHOD(TestExample2)
        {
            Solution sol;
            TreeNode* root = new TreeNode(-5);
            root->left = new TreeNode(1);
            root->right = new TreeNode(7);
            root->right->left = new TreeNode(2);
            root->right->right = new TreeNode(3);
            Assert::AreEqual(12, sol.maxPathSum(root));
            delete root->left;
            delete root->right->left;
            delete root->right->right;
            delete root->right;
            delete root;
        }
    };
}
