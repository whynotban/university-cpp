#include <iostream>
#include <vector>
#include <string>

bool isSafe(int v, const std::vector<std::vector<int>>& graph, const std::vector<int>& color, int c, int n) {
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

bool graphColoringUtil(const std::vector<std::vector<int>>& graph, int m, std::vector<int>& color, int v, int n) {
    if (v == n) {
        return true;
    }
    for (int c = 1; c <= m; ++c) {
        if (isSafe(v, graph, color, c, n)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1, n)) {
                return true;
            }
            color[v] = 0;
        }
    }
    return false;
}

bool graphColoring(const std::vector<std::vector<int>>& graph, int m, std::vector<int>& color, int n) {
    color.assign(n, 0);
    return graphColoringUtil(graph, m, color, 0, n);
}

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::cin >> line;
        for (int j = 0; j < n; ++j) {
            graph[i][j] = line[j] - '0';
        }
    }
    std::vector<int> color(n, 0);
    if (graphColoring(graph, k, color, n)) {
        std::cout << "YES" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << color[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
