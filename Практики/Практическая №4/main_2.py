def main(A, B):
    diff_A_B = A.difference(B)
    diff_B_A = B.difference(A)

    symmetric_diff = diff_A_B.union(diff_B_A)

    expectation = 0
    if symmetric_diff:
        expectation = sum(symmetric_diff) / len(symmetric_diff)

    return symmetric_diff, expectation

print(f"Введите элементы массива A:")
A = set(map(int, input().split()))
print(f"Введите элементы массива B:")
B = set(map(int, input().split()))
sym_diff, m_o = main(A, B)

print(f"Множество A: {A}")
print(f"Множество B: {B}")
print(f"Симметрическая разница: {sym_diff}")
print(f"Матожидание: {m_o}")
