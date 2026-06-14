#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

int GRID_ROWS = 10;
const int CELL_SIZE = 40;
enum CellType { EMPTY, OBSTACLE, START, END, PATH, VISITED, OPEN };

struct Cell {
    int x, y;
    CellType type;
    int f, g, h, weight;
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), weight(1), parent(nullptr) {}
};

struct CompareCells {
    bool operator()(Cell* const& a, Cell* const& b) {
        return a->f > b->f;
    }
};

int heuristic(Cell* a, Cell* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

void resetGrid(vector<vector<Cell>>& grid, int rows) {
    grid.clear();
    for (int i = 0; i < rows; ++i) {
        vector<Cell> row;
        for (int j = 0; j < rows; ++j) {
            row.push_back(Cell(j, i));
        }
        grid.push_back(row);
    }
}

void loadVariant12(vector<vector<Cell>>& grid, Cell*& start, Cell*& end) {
    GRID_ROWS = 10;
    resetGrid(grid, GRID_ROWS);
    start = &grid[2][0];
    start->type = START;
    end = &grid[9][9];
    end->type = END;

    int obs[23][2] = {
        {3,0}, {0,1}, {7,1}, {2,3}, {5,3}, {6,3},
        {3,4}, {4,4}, {8,4}, {9,4}, {5,6}, {8,6},
        {0,7}, {1,7}, {5,7}, {8,7}, {9,7},
        {0,8}, {2,8}, {5,8}, {6,8}, {0,9}, {8,9}
    };
    for (int i = 0; i < 23; i++) {
        grid[obs[i][1]][obs[i][0]].type = OBSTACLE;
    }
}

void loadRandomMap(vector<vector<Cell>>& grid, Cell*& start, Cell*& end, bool useWeights) {
    GRID_ROWS = 20;
    resetGrid(grid, GRID_ROWS);
    int sy = rand() % GRID_ROWS, sx = rand() % GRID_ROWS;
    int ey = rand() % GRID_ROWS, ex = rand() % GRID_ROWS;
    start = &grid[sy][sx]; start->type = START;
    end = &grid[ey][ex]; end->type = END;

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            if (&grid[i][j] != start && &grid[i][j] != end) {
                int r = rand() % 100;
                if (r < 25) grid[i][j].type = OBSTACLE;
                else if (useWeights && r < 50) {
                    int w = rand() % 3;
                    grid[i][j].weight = (w == 0) ? 3 : (w == 1 ? 5 : 9);
                }
            }
        }
    }
}

void runAStar(vector<vector<Cell>>& grid, Cell* start, Cell* end, RenderWindow& window) {
    priority_queue<Cell*, vector<Cell*>, CompareCells> openList;
    for(auto& row : grid) for(auto& cell : row) { cell.g = 999999; cell.parent = nullptr; }

    start->g = 0;
    start->f = heuristic(start, end);
    openList.push(start);

    while (!openList.empty()) {
        Cell* current = openList.top();
        openList.pop();

        if (current->type != START && current->type != END) current->type = VISITED;

        if (current == end) {
            Cell* pathNode = current->parent;
            while (pathNode != start) {
                pathNode->type = PATH;
                pathNode = pathNode->parent;
            }
            return;
        }

        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (nx >= 0 && nx < GRID_ROWS && ny >= 0 && ny < GRID_ROWS) {
                Cell* neighbor = &grid[ny][nx];
                if (neighbor->type == OBSTACLE) continue;

                int tg = current->g + neighbor->weight;
                if (tg < neighbor->g) {
                    neighbor->parent = current;
                    neighbor->g = tg;
                    neighbor->f = tg + heuristic(neighbor, end);
                    if (neighbor->type != VISITED && neighbor->type != OPEN) {
                        if (neighbor->type != START && neighbor->type != END) neighbor->type = OPEN;
                        openList.push(neighbor);
                    }
                }
            }
        }

        window.clear(Color::White);
        for (int i = 0; i < GRID_ROWS; i++) {
            for (int j = 0; j < GRID_ROWS; j++) {
                RectangleShape rect(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                if (grid[i][j].type == OBSTACLE) rect.setFillColor(Color::Black);
                else if (grid[i][j].type == START) rect.setFillColor(Color::Blue);
                else if (grid[i][j].type == END) rect.setFillColor(Color::Red);
                else if (grid[i][j].type == VISITED) rect.setFillColor(Color::Cyan);
                else if (grid[i][j].type == OPEN) rect.setFillColor(Color::Green);
                else if (grid[i][j].type == PATH) rect.setFillColor(Color::Magenta);
                else if (grid[i][j].weight > 1) {
                    if (grid[i][j].weight == 3) rect.setFillColor(Color(255, 255, 153));
                    else if (grid[i][j].weight == 5) rect.setFillColor(Color(255, 178, 102));
                    else rect.setFillColor(Color(153, 76, 0));
                }
                else rect.setFillColor(Color::White);
                window.draw(rect);
            }
        }
        window.display();
    }
}

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(800, 800), "A*");
    vector<vector<Cell>> grid;
    Cell *start, *end;

    loadVariant12(grid, start, end);
    cout << "1 - Вариант 12\n2 - Случайная карта\n3 - Карта с весами\nПробел - Запуск" << endl;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Num1) loadVariant12(grid, start, end);
                if (event.key.code == Keyboard::Num2) loadRandomMap(grid, start, end, false);
                if (event.key.code == Keyboard::Num3) loadRandomMap(grid, start, end, true);
                if (event.key.code == Keyboard::Space) runAStar(grid, start, end, window);
            }
        }

        window.clear(Color::White);
        for (int i = 0; i < GRID_ROWS; i++) {
            for (int j = 0; j < GRID_ROWS; j++) {
                RectangleShape rect(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                if (grid[i][j].type == OBSTACLE) rect.setFillColor(Color::Black);
                else if (grid[i][j].type == START) rect.setFillColor(Color::Blue);
                else if (grid[i][j].type == END) rect.setFillColor(Color::Red);
                else if (grid[i][j].type == PATH) rect.setFillColor(Color::Magenta);
                else if (grid[i][j].weight > 1) {
                    if (grid[i][j].weight == 3) rect.setFillColor(Color(255, 255, 153));
                    else if (grid[i][j].weight == 5) rect.setFillColor(Color(255, 178, 102));
                    else rect.setFillColor(Color(153, 76, 0));
                }
                else rect.setFillColor(Color::White);
                window.draw(rect);
            }
        }
        window.display();
    }
    return 0;
}
