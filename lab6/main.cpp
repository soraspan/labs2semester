#include <iostream>
#include "Figure.hpp"
#include "RightTriangle.hpp"
#include "Circle.hpp"


int main(){
    // Наследование позволяет создать новые классы на основе существующих, повторно используя код(это самое : public *имя материнского класса*).
    // Полиморфизм позволяет работать с объектами разных классов через общий интерфейс(одно название функции для разных классов),
    // что упрощает код и повышает его гибкость.
    Figure* triangle = new RightTriangle();
    triangle->inputInfo();
    std::cout << "Square of your triangle" << triangle->findSquare() << std::endl;
    triangle->FigureInfo();
    Figure* circle = new Circle();
    circle->inputInfo();
    std::cout << "Square of your circle" << circle->findSquare() << std::endl;
    circle->FigureInfo();
    delete triangle;
    delete circle;
    return 0;
}