#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

class Shape {
public:
    enum Type { Circle, Square, Triangle }; // enum - особый тип переменной, который может принимать только конкретные значения(указанные в {})

    Shape(Type type, const sf::Vector2f& position): type(type), direction(1, 1) {
        if (type == Circle) {
            shape = std::make_unique<sf::CircleShape>(30);
            //везде в коде используются именно умные указатели(std::unique_ptr) для упрощения работы с памятью и во избежание утечек
            speed = sf::Vector2f(50.0f, 50.0f); // скорость для круга
        }
        else if (type == Square) {
            shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60, 60));
            speed = sf::Vector2f(100.0f, 50.0f); // скорость для квадрата
        }
        else if (type == Triangle) {
            auto triangleShape = std::make_unique<sf::ConvexShape>();
            // здесь мы не используем shape, принадлежащий к абстрактному классу sf::Shape, а сразу определяем необходимый нам sf::ConvexShape, определяющий фигуру по её вершинам
            triangleShape->setPointCount(3);
            triangleShape->setPoint(0, sf::Vector2f(0, -40));
            triangleShape->setPoint(1, sf::Vector2f(-40, 40));
            triangleShape->setPoint(2, sf::Vector2f(40, 40));
            shape = std::move(triangleShape);
            speed = sf::Vector2f(75.0f, 100.0f); // скорость для треугольника
        }
        shape->setPosition(position);
        setRandomColor();
    }

    void update(float deltaTime, const sf::RenderWindow& window) {
        shape->move(direction.x * speed.x * deltaTime, direction.y * speed.y * deltaTime);
        // вектор направления мы умножаем на коэффициент скорости и на прошедшее время, чтобы определить, куда "долетела" фигура

        // Проверка на столкновение с краем окна
        sf::FloatRect bounds = shape->getGlobalBounds();
        if (bounds.top < 0) {
            direction.y = 1; // Отталкиваемся вниз
            setRandomColor();
        }
        if (bounds.top + bounds.height > window.getSize().y) {
            direction.y = -1; // Отталкиваемся вверх
            setRandomColor();
        }
        if (bounds.left < 0) {
            direction.x = 1; // Отталкиваемся вправо
            setRandomColor();
        }
        if (bounds.left + bounds.width > window.getSize().x) {
            direction.x = -1; // Отталкиваемся влево
            setRandomColor();
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*shape);
    }

private:
    void setRandomColor() {
        shape->setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }

    Type type;
    std::unique_ptr<sf::Shape> shape;
    sf::Vector2f direction;
    sf::Vector2f speed;
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // инициализация генератора псевдослучайных чисел через функцию srand из C

    sf::RenderWindow window(sf::VideoMode(800, 600), L"Работа с графикой");
    window.setFramerateLimit(60); // ограничение FPS, чтобы фигуры не летали слишком быстро и чтобы программа не отъедала много ресурсов ПК

    // Создание фигур
    std::vector<Shape> shapes;
    shapes.emplace_back(Shape::Circle, sf::Vector2f(100, 100));
    shapes.emplace_back(Shape::Square, sf::Vector2f(300, 100));
    shapes.emplace_back(Shape::Triangle, sf::Vector2f(500, 100));

    // Начальная задержка
    sf::sleep(sf::seconds(2));

    // Главный цикл
    sf::Clock clock; // создаем часы для подсчета времени
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        } // данный цикл позволяет программе правильно завершать работу при закрытии окна, не зависая

        float deltaTime = clock.restart().asSeconds(); // получаем время с последнего обновления

        // Обновление фигур
        for (auto& shape : shapes) {
            shape.update(deltaTime, window);
        }

        window.clear(); // очищаем экран перед каждой сменой кадра, чтобы фигуры не оставляли за собой след
        for (auto& shape : shapes) {
            shape.draw(window);
        }
        window.display();
    }

    return 0;
}
