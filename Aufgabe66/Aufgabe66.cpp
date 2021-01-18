// Aufgabe66.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//Aufgabe #66 in https://trainyourprogrammer.de/cplusplus

#include <iostream>
#include <vector>

bool isPrime(size_t _n) {
    if (_n < 3) {
        return _n == 2;
    }
    auto j{ static_cast<size_t>(std::ceil(std::sqrt(_n))) };
    while (_n % j > 0) {
        j--;
    }
    return j == 1;
}

void printIsPrime(size_t _n) {
    if (isPrime(_n)) {
        std::cout << _n << " ist eine Primzahl!" << std::endl;
    }
    else {
        std::cout << _n << " ist _keine_ Primzahl!" << std::endl;
    }
}

int main()
{
    std::vector<size_t> zahlen;
    //for (size_t j = 21; j < 50; ++j) {
    //    printIsPrime(j);
    //}
    unsigned div{ 21 };
    size_t result{ 1 };
    for (size_t j = 2; j <= div; ++j) {
        if (isPrime(j)) {
            printIsPrime(j);
            result *= j;
        }
        else {
            zahlen.push_back(j);
        }
    }

    result = 24 * result;
    std::cout << "Die Zahl: " << result << std::endl;
    std::cout << "Rest bei der Division dieser Zahl durch "<< div <<" : " << result% div << std::endl;
}

