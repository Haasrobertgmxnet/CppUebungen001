// PeriodenlaengeStammbruch.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Aufgabe #309 in https://trainyourprogrammer.de/cplusplus
//

#include <vector>
#include <algorithm>
//#include <cstdlib>
#include <cmath>
#include <iostream>

int main()
{
    srand(time(0));
    std::vector <int> ziffern;
    std::vector <int> reste;
    auto nenner{ (rand() % 100) + 1 };
    auto dividend{ static_cast<int>(pow(10,ceil(log10(nenner)))) };
    do
    {
        auto w1 = dividend / nenner;
        auto rest = dividend % nenner;
        if (rest > 0) {
            auto it = std::find(reste.begin(), reste.end(), rest);
            if (it != reste.end()) {
                break;
            }
            else {
                ziffern.push_back(w1);
                reste.push_back(rest);
                dividend = 10 * rest;
            }
        }
        else {
            reste.clear();
            break;
        }
    } while (true);
    
    std::cout << "Stammbruch: 1/" << nenner << std::endl;
    std::cout << "Periodenlange: " << reste.size() << std::endl;
    std::cout << "Periode: ";
    std::for_each(ziffern.begin(), ziffern.end(), [](int x) {std::cout << x; });
    std::cout << std::endl;
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
