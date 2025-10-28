def count_elements(arr, t_value):
    count = 0
    for item in arr:
        if item < t_value:
            count += 1
    return count


def find_arr(arr_a, arr_b, t_value):
    count_a = count_elements(arr_a, t_value)
    count_b = count_elements(arr_b, t_value)

    print(f"Количество элементов < {t_value} в массиве A: {count_a}")
    print(f"Количество элементов < {t_value} в массиве B: {count_b}")

    if count_a <= count_b:
        print("Массив с наименьшим количеством: A")
        print(f"Элементы массива A: {arr_a}")
        print(f"Элементы массива B: {arr_b}")
    else:
        print("Массив с наименьшим количеством: B")
        print(f"Элементы массива B: {arr_b}")
        print(f"Элементы массива A: {arr_a}")

N = 5
try:
    t = int(input("Введите пороговое значение t: "))
    print(f"Введите {N} элементов для массива A:")
    A = list(map(int, input().split()))

    print(f"Введите {N} элементов для массива B:")
    B = list(map(int, input().split()))

    if len(A) != N or len(B) != N:
        print(f"Необходимо ввести  {N} элементов для каждого массива")
    else:
        find_arr(A, B, t)
except ValueError:
    print("Вводимые значения должны быть целыми числами")
