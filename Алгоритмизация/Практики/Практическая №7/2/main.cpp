#include <iostream>
#include <vector>
#include <algorithm>

int minBanknotes(int x, const std::vector<int>& coins) {
    std::vector<int> dp(x + 1, x + 2);
    dp[0] = 0;
    for (int i = 1; i <= x; ++i) {
        for (int coin : coins) {
            if (i >= coin) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[x] > x + 1 ? -1 : dp[x];
}

int main() {
    int x;
    if (!(std::cin >> x)) return 0;
    int k;
    if (!(std::cin >> k)) return 0;
    std::vector<int> coins(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> coins[i];
    }
    std::cout << minBanknotes(x, coins) << std::endl;
    return 0;
}
