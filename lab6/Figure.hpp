#pragma once
#include <cmath>
#include <string>


// Figure слишком небольшой класс, в котором ничего особого и нет, поэтому решил реализовать его как header-only библиотеку
struct Point{
    int x;
    int y;
};


double findDistance(Point first, Point second){
    return (sqrt(pow(second.x - first.x, 2)+pow(second.y - first.y, 2))); // по теореме Пифагора находим расстояние между двумя точками на плоскости
}


class Figure{
    protected:
        std::string color;
    public:
        virtual ~Figure() {};
        virtual void inputInfo() = 0;
        virtual double findSquare() = 0;
        virtual void FigureInfo() = 0;
};