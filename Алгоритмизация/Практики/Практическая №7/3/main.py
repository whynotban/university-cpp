import sys

def find_min_max(nums: list, low: int, high: int) -> tuple:
    if low == high:
        return nums[low], nums[low]
    if high == low + 1:
        if nums[low] < nums[high]:
            return nums[low], nums[high]
        else:
            return nums[high], nums[low]
    mid = low + (high - low) // 2
    left_min, left_max = find_min_max(nums, low, mid)
    right_min, right_max = find_min_max(nums, mid + 1, high)
    return min(left_min, right_min), max(left_max, right_max)

if __name__ == "__main__":
    input_data = sys.stdin.read().split()
    if not input_data:
        sys.exit(0)
    n = int(input_data[0])
    nums = [int(i) for i in input_data[1:1+n]]
    if n > 0:
        res_min, res_max = find_min_max(nums, 0, n - 1)
        print(f"The minimum array element is {res_min}")
        print(f"The maximum array element is {res_max}")
      
