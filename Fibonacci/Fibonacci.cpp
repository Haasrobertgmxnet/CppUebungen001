// Fibonacci.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
//Verwendung eine TMP-basierten For-Loop, entnommen aus: http://spraetor.github.io/2015/12/26/compile-time-loops.html
#include <iostream>

template <int I>
struct Fac // recursion formula
{
    static constexpr size_t value = I * Fac<I - 1>::value;
};

template <> struct Fac<0> { static constexpr size_t value = 1; };
template <> struct Fac<1> { static constexpr size_t value = 1; };

template <int I>
struct Fibo // recursion formula
{
    static constexpr size_t value = Fibo<I - 1>::value + Fibo<I - 2>::value;
};

template <> struct Fibo<1> { static constexpr size_t value = 1; };
template <> struct Fibo<0> { static constexpr size_t value = 0; };

template <int I, int N, class F>
struct Loop {
    static void run() {
        F::template eval<I>();
        Loop<I + 1, N, F>::run();
    }
};

template <int N, class F>
struct Loop<N, N, F> { static void run() {} };

struct PrintFac
{
    template <int I>
    static void eval() {
        std::cout << "Fac<" << I << ">::value = " << Fac<I>::value << std::endl;
    }
};

struct PrintFibo
{
    template <int I>
    static void eval() {
        std::cout << "Fibo<" << I << ">::value = " << Fibo<I>::value << std::endl;
    }
};

int main()
{
    //F::template eval<I>();
    Loop<0, 11, PrintFac>::run();
    Loop<0, 11, PrintFibo>::run();
    std::cout << "Hello World!\n";
}

