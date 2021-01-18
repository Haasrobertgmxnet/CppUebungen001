// BerechnungMedian.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Aufgabe #316 in https://trainyourprogrammer.de/cplusplus
//

#include <vector>
//#include <list>
#include <algorithm>
#include <cstdlib>
#include <iostream>

int main()
{
    srand(time(0));
    auto numElemsOfVector1{ (rand() % 10) + 1 };
    auto Vector1{ std::vector<int>(numElemsOfVector1,0) };
    std::transform(Vector1.begin(), Vector1.end(), Vector1.begin(), [](int x) {return (rand() % 100) + 1; });

    auto numElemsOfVector2{ (rand() % 10) + 1 };
    auto Vector2{ std::vector<int>(numElemsOfVector2,0) };
    std::transform(Vector2.begin(), Vector2.end(), Vector2.begin(), [](int x) {return (rand() % 100) + 1; });

    Vector2.insert(Vector2.begin(), Vector1.begin(), Vector1.end());
    std::sort(Vector2.begin(), Vector2.end());
    std::for_each(Vector2.begin(), Vector2.end(), [](int x) {std::cout << x << std::endl; });

    double median{ 0.0 };
    auto index{ numElemsOfVector1 + numElemsOfVector2 };
    std::cout << "Groesse des Vektors: " << index << std::endl;
    if (index % 2 == 0) {
        index = index / 2;
        median = 0.5 * static_cast<double>(Vector2[index - 1] + Vector2[index]);
    }
    else {
        index = index / 2;
        median = static_cast<double>( Vector2[index]);
    }
    std::cout << "Stelle des Medians: " << index+1 << std::endl;
    std::cout << "Der Median: " << median << std::endl;

    //const size_t numElemsOfVector3{ numElemsOfVector1 + numElemsOfVector2 };
    //auto Vector3{ std::vector<int>(numElemsOfVector3,0) };

    
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
