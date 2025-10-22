#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <string>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Вычисление значения функции

        // Преобразование координат в экранные
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        // Добавление точки в массив вершин
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Приложение для вывода графиков");

    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная для проверки существования пользовательской точки

    // 1 _ Загрузка шрифта (допишите код)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }

    // 2 _ Текст для отображения координат точки (допишите код)
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setPosition(10, 10);
    coordinatesText.setFillColor(sf::Color::White);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, 300); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(800, 300); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 0); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 600); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    // Вертикальная линия для графика x = -3
    sf::VertexArray verticalLine(sf::Lines, 2);
    float lineXScreen = 400 + (-3.0f) * 30.0f; // 400 - центр, 30 - масштаб по X
    verticalLine[0].position = sf::Vector2f(lineXScreen, 0);
    verticalLine[0].color = sf::Color::Blue;
    verticalLine[1].position = sf::Vector2f(lineXScreen, 600);
    verticalLine[1].color = sf::Color::Blue;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 30.0f; // Масштаб 30 по X
                    float mathY = -(mousePos.y - 300) / 30.0f; // Масштаб 30 по Y

                    // Установка новой пользовательской точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем, что точка существует

                    // 3 _ Допишите логику проверки точки по переменным mathX и mathY !
                    std::string zoneString;
                    const float epsilon = 0.15f;

                    if (std::abs(mathX - (-3.0f)) < epsilon || std::abs(mathY - (-mathX)) < epsilon) {
                        zoneString = "zone: graniza";
                    }
                    else if (mathX > -3.0f && mathY < -mathX) {
                        zoneString = "zone: 1";
                    }
                    else if (mathX < -3.0f && mathY > -mathX) {
                        zoneString = "zone: 2";
                    }
                    else if (mathX < -3.0f && mathY < -mathX) {
                        zoneString = "zone: 3";
                    }
                    else if (mathX > -3.0f && mathY > -mathX) {
                        zoneString = "zone: 4";
                    }
                    else {
                        zoneString = "zone: -";
                    }

                    // Обновление текста с координатами точки 
                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ")\n" + zoneString);
                }
            }
        }

        // 4 _ Очистка экрана (допишите код)
        window.clear();

        // Отрисовка осей
        window.draw(xAxis);
        window.draw(yAxis);

        // 5 _  Отрисовка графика y = -x (Замените на ваш график)
        drawGraph(window, [](float x) { return -x; }, -15.0f, 15.0f, 30.0f, 30.0f, sf::Color::Red);

        // 5 _   Отрисовка графика x = -3 (Замените на ваш график)
        window.draw(verticalLine);

        // Отрисовка пользовательской точки, если она существует
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        // Отображение нового кадра
        window.display();
    }

    return 0;
}