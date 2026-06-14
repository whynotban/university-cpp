import pygame
import random
from queue import PriorityQueue

pygame.init()
pygame.font.init()

WIDTH, UI_WIDTH = 600, 200
WIN = pygame.display.set_mode((WIDTH + UI_WIDTH, WIDTH))
pygame.display.set_caption("Алгоритм A*")

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREY = (160, 160, 160)
DARK_GREY = (40, 40, 40)
BLUE = (0, 0, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
PURPLE = (128, 0, 128)
WEIGHT_3 = (255, 255, 153)
WEIGHT_5 = (255, 178, 102)
WEIGHT_9 = (153, 76, 0)


class Node:
    def __init__(self, row, col, width, total_rows):
        self.row = row
        self.col = col
        self.x = col * width
        self.y = row * width
        self.color = WHITE
        self.neighbors = []
        self.width = width
        self.total_rows = total_rows
        self.weight = 1

    def get_pos(self):
        return self.col, self.row

    def is_closed(self):
        return self.color == CYAN

    def is_open(self):
        return self.color == GREEN

    def is_barrier(self):
        return self.color == BLACK

    def is_start(self):
        return self.color == BLUE

    def is_end(self):
        return self.color == RED

    def reset(self):
        self.color = WHITE
        self.weight = 1

    def make_start(self):
        self.color = BLUE

    def make_closed(self):
        self.color = CYAN

    def make_open(self):
        self.color = GREEN

    def make_barrier(self):
        self.color = BLACK
        self.weight = float('inf')

    def make_end(self):
        self.color = RED

    def make_path(self):
        self.color = PURPLE

    def set_weight(self, weight):
        self.weight = weight
        if weight == 3:
            self.color = WEIGHT_3
        elif weight == 5:
            self.color = WEIGHT_5
        elif weight == 9:
            self.color = WEIGHT_9

    def draw(self, win):
        pygame.draw.rect(win, self.color, (self.x, self.y, self.width, self.width))

    def update_neighbors(self, grid):
        self.neighbors = []
        if self.row < self.total_rows - 1 and not grid[self.row + 1][self.col].is_barrier():
            self.neighbors.append(grid[self.row + 1][self.col])
        if self.row > 0 and not grid[self.row - 1][self.col].is_barrier():
            self.neighbors.append(grid[self.row - 1][self.col])
        if self.col < self.total_rows - 1 and not grid[self.row][self.col + 1].is_barrier():
            self.neighbors.append(grid[self.row][self.col + 1])
        if self.col > 0 and not grid[self.row][self.col - 1].is_barrier():
            self.neighbors.append(grid[self.row][self.col - 1])


def heuristic(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return abs(x1 - x2) + abs(y1 - y2)


def reconstruct_path(came_from, current, draw_func):
    while current in came_from:
        current = came_from[current]
        current.make_path()
        draw_func()


def a_star_algorithm(draw_func, grid, start, end, use_weights=False):
    count = 0
    open_set = PriorityQueue()
    open_set.put((0, count, start))
    came_from = {}

    g_score = {node: float("inf") for row in grid for node in row}
    g_score[start] = 0

    f_score = {node: float("inf") for row in grid for node in row}
    f_score[start] = heuristic(start.get_pos(), end.get_pos())

    open_set_hash = {start}

    while not open_set.empty():
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()

        current = open_set.get()[2]
        open_set_hash.remove(current)

        if current == end:
            reconstruct_path(came_from, end, draw_func)
            end.make_end()
            start.make_start()
            return True

        for neighbor in current.neighbors:
            step_cost = neighbor.weight if use_weights else 1
            temp_g_score = g_score[current] + step_cost

            if temp_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = temp_g_score
                f_score[neighbor] = temp_g_score + heuristic(neighbor.get_pos(), end.get_pos())
                if neighbor not in open_set_hash:
                    count += 1
                    open_set.put((f_score[neighbor], count, neighbor))
                    open_set_hash.add(neighbor)
                    neighbor.make_open()

        draw_func()
        if current != start:
            current.make_closed()
    return False


def make_grid(rows, width):
    grid = []
    gap = width // rows
    for i in range(rows):
        grid.append([])
        for j in range(rows):
            node = Node(i, j, gap, rows)
            grid[i].append(node)
    return grid


def draw_grid_lines(win, rows, width):
    gap = width // rows
    for i in range(rows):
        pygame.draw.line(win, GREY, (0, i * gap), (width, i * gap))
        for j in range(rows):
            pygame.draw.line(win, GREY, (j * gap, 0), (j * gap, width))


def draw_ui(win, use_weights):
    pygame.draw.rect(win, DARK_GREY, (WIDTH, 0, UI_WIDTH, WIDTH))

    try:
        font_title = pygame.font.SysFont('arial', 20, bold=True)
        font_main = pygame.font.SysFont('arial', 16)
    except Exception:
        font_title = pygame.font.Font(None, 24)
        font_main = pygame.font.Font(None, 20)

    title = font_title.render("легенда", True, WHITE)
    win.blit(title, (WIDTH + 15, 20))

    legend_items = [
        (BLUE, "Старт"),
        (RED, "Финиш"),
        (PURPLE, "Путь"),
        (CYAN, "Посещена"),
        (GREEN, "В очереди"),
        (BLACK, "Препятствие"),
        (WHITE, "Пустая (вес 1)")
    ]

    if use_weights:
        legend_items.extend([
            (WEIGHT_3, "Вес 3 (желтая)"),
            (WEIGHT_5, "Вес 5 (оранжевая)"),
            (WEIGHT_9, "Вес 9 (коричневая)")
        ])

    y_offset = 60
    for color, text in legend_items:
        pygame.draw.rect(win, color, (WIDTH + 15, y_offset, 20, 20))
        pygame.draw.rect(win, GREY, (WIDTH + 15, y_offset, 20, 20), 1)  # обводка
        label = font_main.render(text, True, WHITE)
        win.blit(label, (WIDTH + 45, y_offset + 2))
        y_offset += 30

    y_offset += 20
    controls_title = font_title.render("управление", True, WHITE)
    win.blit(controls_title, (WIDTH + 15, y_offset))

    y_offset += 30
    controls = [
        "1: Вариант 12",
        "2: Случайная",
        "3: Карта с весами",
        "пробел - поиск пути"
    ]

    for text in controls:
        label = font_main.render(text, True, (200, 200, 200))
        win.blit(label, (WIDTH + 15, y_offset))
        y_offset += 25


def draw(win, grid, rows, width, use_weights):
    win.fill(WHITE)
    for row in grid:
        for node in row:
            node.draw(win)

    draw_grid_lines(win, rows, width)
    draw_ui(win, use_weights)
    pygame.display.update()


def load_variant_12(grid):
    for row in grid:
        for node in row:
            node.reset()

    start = grid[2][0]
    end = grid[9][9]
    start.make_start()
    end.make_end()

    obstacles = [
        (3, 0), (0, 1), (7, 1), (2, 3), (5, 3), (6, 3),
        (3, 4), (4, 4), (8, 4), (9, 4), (5, 6), (8, 6),
        (0, 7), (1, 7), (5, 7), (8, 7), (9, 7),
        (0, 8), (2, 8), (5, 8), (6, 8), (0, 9), (8, 9)
    ]
    for ox, oy in obstacles:
        grid[oy][ox].make_barrier()
    return start, end


def load_random_map(grid, use_weights):
    rows = len(grid)
    for row in grid:
        for node in row:
            node.reset()

    start_y, start_x = random.randint(0, rows - 1), random.randint(0, rows - 1)
    end_y, end_x = random.randint(0, rows - 1), random.randint(0, rows - 1)
    while (start_y, start_x) == (end_y, end_x) or abs(start_y - end_y) + abs(start_x - end_x) < rows // 2:
        end_y, end_x = random.randint(0, rows - 1), random.randint(0, rows - 1)

    start = grid[start_y][start_x]
    end = grid[end_y][end_x]
    start.make_start()
    end.make_end()

    for row in grid:
        for node in row:
            if node != start and node != end:
                val = random.random()
                if val < 0.25:
                    node.make_barrier()
                elif use_weights and val < 0.5:
                    weight_choice = random.choice([3, 5, 9])
                    node.set_weight(weight_choice)
    return start, end


def main():
    ROWS = 10
    grid = make_grid(ROWS, WIDTH)
    start, end = load_variant_12(grid)
    use_weights_mode = False
    run = True

    while run:
        draw(WIN, grid, ROWS, WIDTH, use_weights_mode)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_1:
                    ROWS = 10
                    grid = make_grid(ROWS, WIDTH)
                    start, end = load_variant_12(grid)
                    use_weights_mode = False

                if event.key == pygame.K_2:
                    ROWS = 20
                    grid = make_grid(ROWS, WIDTH)
                    start, end = load_random_map(grid, False)
                    use_weights_mode = False

                if event.key == pygame.K_3:
                    ROWS = 20
                    grid = make_grid(ROWS, WIDTH)
                    start, end = load_random_map(grid, True)
                    use_weights_mode = True

                if event.key == pygame.K_SPACE and start and end:
                    for row in grid:
                        for node in row:
                            node.update_neighbors(grid)
                    a_star_algorithm(lambda: draw(WIN, grid, ROWS, WIDTH, use_weights_mode), grid, start, end, use_weights_mode)

    pygame.quit()


if __name__ == "__main__":
    main()
