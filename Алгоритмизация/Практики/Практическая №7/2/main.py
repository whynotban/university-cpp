import sys

def min_banknotes(x: int, coins: list) -> int:
    dp = [x + 2] * (x + 1)
    dp[0] = 0
    for i in range(1, x + 1):
        for coin in coins:
            if i >= coin:
                dp[i] = min(dp[i], dp[i - coin] + 1)
    return -1 if dp[x] > x + 1 else dp[x]

if __name__ == "__main__":
    input_data = sys.stdin.read().split()
    if not input_data:
        sys.exit(0)
    x = int(input_data[0])
    k = int(input_data[1])
    coins = [int(i) for i in input_data[2:2+k]]
    print(min_banknotes(x, coins))
