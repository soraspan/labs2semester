#pragma once
#include "Figure.hpp"
#include <iostream>


class Circle : public Figure {
    private:
        Point O, A;
    public:
        void inputInfo() override {
            std::cout << "Please, input color of your figure" << std::endl;
            std::cin >> color;
            std::cout << "Please, input coordinates of points O, Y(4 numbers)" << std::endl;
            std::cin >> O.x >> O.y >> A.x >> A.y;
        }
        double findSquare() override {
            return M_PI*pow(findDistance(O, A), 2); // по формуле площади круга S = Пr^2
        }
        void FigureInfo() override {
            std::cout << "Circle" << std::endl;
            std::cout << "Color: " << color << std::endl;
            std::cout << "Point O(center): (" << O.x << ',' << O.y << ')' << std::endl;
            std::cout << "Point A: (" << A.x << ',' << A.y << ')' << std::endl;
        }
};