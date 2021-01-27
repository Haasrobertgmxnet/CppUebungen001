// Geburtstagsproblem.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Aufgabe #308 in https://trainyourprogrammer.de/cplusplus
// Geburtstags-Paradoxon

#include <iostream>

double prob(unsigned _number) {
    auto k{ 0 };
    auto res{ 1.0 };
    while (k < _number) {
        res *= (365.0 - k) / 365.0;
        k++;
    }
    return res;
}

auto number_from_prob(double _prob) {
    auto k{ 1 };
    while (1.0-prob(k) <= _prob)k++;
    return k;
}

int main()
{
    std::cout << "Das Geburtstagsproblem\n";
    for (auto j = 0; j < 100; ++j) {
        std::cout << "j: " << "Prob(" << j << "): " << 1.0-prob(j) << std::endl;
    }
    std::cout << "j: " << number_from_prob(0.5) << std::endl;
    std::cout << "Prob: " << 1.0-prob(number_from_prob(0.5)) << std::endl;
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
