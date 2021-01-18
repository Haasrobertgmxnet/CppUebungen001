// PrimfaktorZerlegung.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <list>
#include <iostream>

size_t getPrimeFactor(size_t _number) {
    if (_number % 2 == 0) {
        return 2;
    }
    auto bound{ static_cast<size_t>(std::ceil(std::sqrt(_number))) };
    for (size_t j = 3; j < bound; j += 2) {
        if (_number % j == 0) {
            return j;
        }
    }
    return 1;
}

std::list<size_t> getPrimeFactorization(size_t _number) {
    std::list<size_t> primeFactors;
    auto ws{ _number };
    auto fws{ getPrimeFactor(ws) };
    if (fws == 1) {
        primeFactors.push_back(ws);
    }
    else {
        primeFactors.push_back(fws);
    }
    while (fws > 1) {
        ws = ws / fws;
        fws = getPrimeFactor(ws);
        if (fws == 1) {
            primeFactors.push_back(ws);
        }
        else {
            primeFactors.push_back(fws);
        }
    }
    return primeFactors;
}

int main() 
{   
    {
        auto w{ getPrimeFactorization(120) };
    }
    {
        auto w{ getPrimeFactorization(433) };
    }
    {
        auto w{ getPrimeFactorization(289) };
    }
    {
        auto w{ getPrimeFactorization(2020) };
    }
    {
        auto w{ getPrimeFactorization(2021) };
    }
    {
        auto w{ getPrimeFactorization(2023) };
    }
    {
        auto w{ getPrimeFactorization(2299) };
    }
    {
        auto w{ getPrimeFactorization(6578645) };
    }
    std::cout << "Finished! " << std::endl;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"


