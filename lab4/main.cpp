#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <cctype>
#include <Windows.h>

class MyText {
public:
    MyText(const std::string& text, float animationTime): text(text + "-"), animationTime(animationTime), displayTime(1.0f) {}
    void verbAnimatedText(sf::RenderWindow& window) const {
        // �������� �� ������������ �� ������� ������ ��������� �� �����������, ���� ������� ������� �� �� ����������� ��� � ���� ����� �������,
        // ��� ��� ����� ���������� ����������� ��������� ����� ���������� ������ �� ��������� �����
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "����� �� ��������!" << std::endl;
            return;
        }
        sf::Text animatedText("", font, 30);
        animatedText.setPosition(50, 50);
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("beep.wav")) {
            std::cerr << "���� �� ������!" << std::endl;
            return;
        }
        sf::Sound sound;
        sound.setBuffer(buffer);
        const float interval = 0.15; // ����� ����� ������� ������� �������
        sf::Clock clock, animationClock;
        size_t currentLength = 0;
        std::string displayedText = "";
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            } // ��������� ��������� ��������� ������ � ������� ������ ��� �������� ����
            if (animationClock.getElapsedTime().asSeconds() < animationTime) {
                if (clock.getElapsedTime().asSeconds() >= interval) {
                    if (currentLength < text.length()) {
                        displayedText += text[currentLength];
                        currentLength++;
                    }
                    else {
                        currentLength = 0; // �������� �������� ������ �� �����, ���� ��� �������� �����
                    }
                    animatedText.setString(displayedText);
                    for (size_t i = 0; i < displayedText.length(); ++i) {
                        if (isUpperCaseOrDigit(displayedText[i])) {
                            animatedText.setFillColor(generateBrightColor());
                        }
                    } // ������������� ���� ������� ������� ����� ����� �������
                    clock.restart();
                }
                window.clear();
                window.draw(animatedText);
                window.display();
            }
            else {
                sound.play();
                while (sound.getStatus() == sf::Sound::Playing) {
                    // �������� ���������� ��������� �������
                }
                break;
            }
        }
    }
private:
    std::string text;
    float animationTime;
    float displayTime;
    bool isUpperCaseOrDigit(char ch) const {
        return std::isupper(ch) || std::isdigit(ch);
    }
    sf::Color generateBrightColor() const {
        srand(static_cast<unsigned int>(time(nullptr)) + rand());
        sf::Uint8 r = 75 + rand() % 181; // ����������� �������� 75, ����� ���� ��� ����
        sf::Uint8 g = 75 + rand() % 181;
        sf::Uint8 b = 75 + rand() % 181;
        return sf::Color(r, g, b);
    }
};
int main() {
    SetConsoleOutputCP(1251);
    std::string userText = "1234567890";
    float animationTime;
    std::cout << "������� ����� �������� � ��������: ";
    std::cin >> animationTime;
    sf::RenderWindow window(sf::VideoMode(800, 600), L"������������� ����� ������");
    MyText animatedText(userText, animationTime);
    animatedText.verbAnimatedText(window);
    return 0;
}
