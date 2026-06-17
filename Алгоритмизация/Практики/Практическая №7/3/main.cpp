#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

std::pair<int, int> findMinMax(const std::vector<int>& nums, int low, int high) {
    if (low == high) {
        return { nums[low], nums[low] };
    }
    if (high == low + 1) {
        if (nums[low] < nums[high]) {
            return { nums[low], nums[high] };
        }
        else {
            return { nums[high], nums[low] };
        }
    }
    int mid = low + (high - low) / 2;
    auto left = findMinMax(nums, low, mid);
    auto right = findMinMax(nums, mid + 1, high);
    return { std::min(left.first, right.first), std::max(left.second, right.second) };
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    if (n > 0) {
        auto result = findMinMax(nums, 0, n - 1);
        std::cout << "The minimum array element is " << result.first << std::endl;
        std::cout << "The maximum array element is " << result.second << std::endl;
    }
    return 0;
}
