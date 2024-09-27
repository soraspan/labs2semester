#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Figure.hpp"


class RightTriangle : public Figure {
    private: // private можно не писать, это больше для красоты, потому что по умолчанию все поля класса имеют такой статус, если не указано иного
        Point A, B, C;
    public:
        void inputInfo() override {
            std::cout << "Please, input color of your figure" << std::endl;
            std::cin >> color;
            std::cout << "Please, input coordinates of points A, B, C(6 numbers)" << std::endl;
            std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
        }
        double findSquare() override {
            std::vector<double> sides = {findDistance(A, B), findDistance(B, C), findDistance(A, C)};
            // массив, содержащий длины сторон
            sides.erase(std::max_element(sides.begin(), sides.end()));
            // нам не нужна длина гипотенузы, являющейся наибольшей стороной, удаляем её из массива
            return sides[0]*sides[1]*0.5; // по формуле S=a*b/2
        }
        void FigureInfo() override {
            std::cout << "Right Triangle" << std::endl;
            std::cout << "Color: " << color << std::endl;
            std::cout << "Point A: (" << A.x << ',' << A.y << ')' << std::endl;
            std::cout << "Point B: (" << B.x << ',' << B.y << ')' << std::endl;
            std::cout << "Point C: (" << C.x << ',' << C.y << ')' << std::endl;
        }
};