import sys

def is_safe(v: int, graph: list, color: list, c: int, n: int) -> bool:
    for i in range(n):
        if graph[v][i] and c == color[i]:
            return False
    return True

def graph_coloring_util(graph: list, m: int, color: list, v: int, n: int) -> bool:
    if v == n:
        return True
    for c in range(1, m + 1):
        if is_safe(v, graph, color, c, n):
            color[v] = c
            if graph_coloring_util(graph, m, color, v + 1, n):
                return True
            color[v] = 0
    return False

def graph_coloring(graph: list, m: int, color: list, n: int) -> bool:
    color[:] = [0] * n
    return graph_coloring_util(graph, m, color, 0, n)

if __name__ == "__main__":
    input_data = sys.stdin.read().split()
    if not input_data:
        sys.exit(0)
    n = int(input_data[0])
    k = int(input_data[1])
    graph = []
    idx = 2
    for i in range(n):
        row_str = input_data[idx]
        graph.append([int(char) for char in row_str])
        idx += 1
    color = [0] * n
    if graph_coloring(graph, k, color, n):
        print("YES")
        print(" ".join(map(str, color)))
    else:
        print("NO")
      
