// ZielwertSuche.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Aufgabe #315 in https://trainyourprogrammer.de/cplusplus
//

#include <array>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <iostream>

int main()
{
    srand(time(0));
    const size_t numElems{ 50 };
    std::array<int, numElems> s;
    std::transform(s.begin(), s.end(), s.begin(), [](int x) {return (rand() % 100) + 1; });
    std::sort(s.begin(), s.end());
    //std::for_each(s.begin(), s.end(), [](const int x) {std::cout << x << std::endl; });

    int target{ (rand() % 100) + 1 };
    std::list< std::pair<int, int>> listOfIndexPairs;
    auto i{ numElems - 1 };
    for (auto j = 0; j < numElems; ++j) {
        while ((s[i] > target - s[j]) && i > j)i--;
        if (s[i] == target - s[j]) {
            std::pair<int, int> indexPair(-1, -1);
            indexPair.first = j;
            indexPair.second = i;
            listOfIndexPairs.push_back(indexPair);
            //break;
        }
    }
    
    std::cout << "Hello World!\n";
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
