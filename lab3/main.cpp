#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

class Shape {
public:
    enum Type { Circle, Square, Triangle }; // enum - ������ ��� ����������, ������� ����� ��������� ������ ���������� ��������(��������� � {})

    Shape(Type type, const sf::Vector2f& position): type(type), direction(1, 1) {
        if (type == Circle) {
            shape = std::make_unique<sf::CircleShape>(30);
            //����� � ���� ������������ ������ ����� ���������(std::unique_ptr) ��� ��������� ������ � ������� � �� ��������� ������
            speed = sf::Vector2f(50.0f, 50.0f); // �������� ��� �����
        }
        else if (type == Square) {
            shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60, 60));
            speed = sf::Vector2f(100.0f, 50.0f); // �������� ��� ��������
        }
        else if (type == Triangle) {
            auto triangleShape = std::make_unique<sf::ConvexShape>();
            // ����� �� �� ���������� shape, ������������� � ������������ ������ sf::Shape, � ����� ���������� ����������� ��� sf::ConvexShape, ������������ ������ �� � ��������
            triangleShape->setPointCount(3);
            triangleShape->setPoint(0, sf::Vector2f(0, -40));
            triangleShape->setPoint(1, sf::Vector2f(-40, 40));
            triangleShape->setPoint(2, sf::Vector2f(40, 40));
            shape = std::move(triangleShape);
            speed = sf::Vector2f(75.0f, 100.0f); // �������� ��� ������������
        }
        shape->setPosition(position);
        setRandomColor();
    }

    void update(float deltaTime, const sf::RenderWindow& window) {
        shape->move(direction.x * speed.x * deltaTime, direction.y * speed.y * deltaTime);
        // ������ ����������� �� �������� �� ����������� �������� � �� ��������� �����, ����� ����������, ���� "��������" ������

        // �������� �� ������������ � ����� ����
        sf::FloatRect bounds = shape->getGlobalBounds();
        if (bounds.top < 0) {
            direction.y = 1; // ������������� ����
            setRandomColor();
        }
        if (bounds.top + bounds.height > window.getSize().y) {
            direction.y = -1; // ������������� �����
            setRandomColor();
        }
        if (bounds.left < 0) {
            direction.x = 1; // ������������� ������
            setRandomColor();
        }
        if (bounds.left + bounds.width > window.getSize().x) {
            direction.x = -1; // ������������� �����
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
    srand(static_cast<unsigned int>(time(nullptr))); // ������������� ���������� ��������������� ����� ����� ������� srand �� C

    sf::RenderWindow window(sf::VideoMode(800, 600), L"������ � ��������");
    window.setFramerateLimit(60); // ����������� FPS, ����� ������ �� ������ ������� ������ � ����� ��������� �� �������� ����� �������� ��

    // �������� �����
    std::vector<Shape> shapes;
    shapes.emplace_back(Shape::Circle, sf::Vector2f(100, 100));
    shapes.emplace_back(Shape::Square, sf::Vector2f(300, 100));
    shapes.emplace_back(Shape::Triangle, sf::Vector2f(500, 100));

    // ��������� ��������
    sf::sleep(sf::seconds(2));

    // ������� ����
    sf::Clock clock; // ������� ���� ��� �������� �������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        } // ������ ���� ��������� ��������� ��������� ��������� ������ ��� �������� ����, �� �������

        float deltaTime = clock.restart().asSeconds(); // �������� ����� � ���������� ����������

        // ���������� �����
        for (auto& shape : shapes) {
            shape.update(deltaTime, window);
        }

        window.clear(); // ������� ����� ����� ������ ������ �����, ����� ������ �� ��������� �� ����� ����
        for (auto& shape : shapes) {
            shape.draw(window);
        }
        window.display();
    }

    return 0;
}
