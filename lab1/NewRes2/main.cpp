#include <iostream>
#include <bitset>


int main(){
    int i;
    unsigned char X = 7;
    // 7 = 00000111
    //unsigned char X = 98; 
    // 98 = 01100010
    //unsigned char X = 241; 
    // 241 = 11110001
    std::cout << "Изначальное число: " << int(X) << " = " << std::bitset<sizeof(char)*8>(X) << std::endl;
    std::cout << "Введите i: ";
    std::cin >> i;
    std::cout << std::endl;
    std::cout << "Измененное число: " << int(X|(1<<i)) << " = " << std::bitset<sizeof(char)*8>(X|(1<<i)) << std::endl;
    // std::bitset<sizeof(char)*8>(X) выводит число X типа char, состоящего из 8 бит, в двоичной системе.
    // 1<<i - битовый сдвиг единицы 00000001 на i бит влево
    // X|(1<<i) - применение дизъюнкции(логического ИЛИ) для операндов X и (1<<i). 
    // Если в двоичном представлении хотя бы одного из чисел присутствует единица, то в результирующем значении на той же позиции тоже будет единица.
    return 0;
}