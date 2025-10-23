#include <SFML/Graphics.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "работа #3");

    int n = 10;  // размерность матрицы
    int cellSize = 500 / n;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setFillColor(sf::Color::White);
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1.0f);

                // Побочная диагональ
                if ((i + j > n - 1) && ((i + j) % 2 != 0)) {
                    cell.setFillColor(sf::Color::Green);
                }

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
