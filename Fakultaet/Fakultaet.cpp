// Fakultaet.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>

static int kontrolle = 0;

template <int N> struct Fakultaet {
    static const int value = N * Fakultaet<N - 1>::value;
};

template <> struct Fakultaet<0> {
    static const int value = 1;
};

template <int I, int N>
struct Print {
    static void run() {
        kontrolle++;
        std::cout << "Fibo<" << I << ">::value = " << Fakultaet<I>::value << "\n";
        Print<I + 1, N>::run();
    }
};

template <int N>
struct Print<N, N> { static void run() {} };

template <int N>
struct Drucke {
    static void run() {
        kontrolle++;
        std::cout << "Fibo<" << N << ">::value = " << Fakultaet<N>::value << "\n";
        Drucke<N-1>::run();
    }
};

template <>
struct Drucke<0> { static void run() {} };

constexpr int fac(int _n) {
    if (_n < 2) {
        return 1;
    }
    return _n * fac(_n - 1);
}


int main()
{
    std::cout << "Fakultaet<3>::value: " << Fakultaet<3>::value << std::endl;
    std::cout << "Fakultaet<5>::value: " << Fakultaet<5>::value << std::endl;
    Print<0, 5>::run();
    Drucke<5>::run();
    std::cout << "Kontrolle: " << kontrolle << std::endl;
    for (int j = 0; j < 5; j++) {

        std::cout << "Fakultaet<" << j << ">::value: " << fac(j) << std::endl;
    }
    int k{ 0 };
    std::cout << "Zahlenwert: ";
    std::cin >> k;
    std::cout << "Fakultaet<" << k << ">::value: " << fac(k) << std::endl;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
