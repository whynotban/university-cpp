class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def max_path_sum(self, root: TreeNode) -> int:
        self.max_sum = float('-inf')

        def max_gain(node):
            if not node:
                return 0
            left_gain = max(max_gain(node.left), 0)
            right_gain = max(max_gain(node.right), 0)
            price_new_path = node.val + left_gain + right_gain
            self.max_sum = max(self.max_sum, price_new_path)
            return node.val + max(left_gain, right_gain)

        max_gain(root)
        return self.max_sum

if __name__ == "__main__":
    root = TreeNode(-5)
    root.left = TreeNode(1)
    root.right = TreeNode(7)
    root.right.left = TreeNode(2)
    root.right.right = TreeNode(3)
    
    sol = Solution()
    print(sol.max_path_sum(root))
  
