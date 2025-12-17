import time
import random
import summodule


def py_sum_function(arr):
    start_time = time.time()
    total = 0.0
    for x in arr:
        total += x
    end_time = time.time()
    return end_time - start_time


sizes = [1000000, 5000000, 10000000]


for i, N in enumerate(sizes, 1):
    data = [random.uniform(1.0, 100.0) for _ in range(N)]

    time_cpp = summodule.calculate_sum(data)
    time_python = py_sum_function(data)
    print(f'Тест #{i} [размер: {N}]:')
    print(f'Время C++: {time_cpp:.2f}')
    print(f'Время Python: {time_python:.2f}')
    print()
