#include <cmath>
#include <iostream>


int main(){
    int R; // Переменная радиуса, по тех. заданию целочисленная
    std::cin >> R; // Вводим значение радиуса с клавиатуры
    double S = M_PI*pow(R, 2); // Находим площадь круга по формуле 2Пr^2
    std::cout << S << std::endl;
    return 0;
}