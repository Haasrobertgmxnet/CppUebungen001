// TernaryLogic.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//Aufgabe #319 in https://trainyourprogrammer.de/cplusplus
//

#include <iostream>

namespace TernaereLogik {
    enum class Werte : unsigned int { Wahr, Falsch, Unsinnig };

    TernaereLogik::Werte NICHT(TernaereLogik::Werte a) {
        return (a == TernaereLogik::Werte::Wahr) ? TernaereLogik::Werte::Falsch : (
            (a == TernaereLogik::Werte::Falsch) ? TernaereLogik::Werte::Wahr: TernaereLogik::Werte::Unsinnig);
    }

    TernaereLogik::Werte UND(TernaereLogik::Werte a, TernaereLogik::Werte b) {
        if (a == TernaereLogik::Werte::Unsinnig || b == TernaereLogik::Werte::Unsinnig) {
            if (a == TernaereLogik::Werte::Falsch || b == TernaereLogik::Werte::Falsch) {
                return TernaereLogik::Werte::Falsch;
            }
            return TernaereLogik::Werte::Unsinnig;
        }
        else {
            bool bla = (a == TernaereLogik::Werte::Wahr) ? true : false;
            bool blb = (b == TernaereLogik::Werte::Wahr) ? true : false;
            bool blres = bla && blb;
            return (blres == true) ? TernaereLogik::Werte::Wahr : TernaereLogik::Werte::Falsch;
        }
    }

    TernaereLogik::Werte ODER(TernaereLogik::Werte a, TernaereLogik::Werte b) {
        if (a == TernaereLogik::Werte::Unsinnig || b == TernaereLogik::Werte::Unsinnig) {
            if (a == TernaereLogik::Werte::Wahr || b == TernaereLogik::Werte::Wahr) {
                return TernaereLogik::Werte::Wahr;
            }
            return TernaereLogik::Werte::Unsinnig;
        }
        else {
            bool bla = (a == TernaereLogik::Werte::Wahr) ? true : false;
            bool blb = (b == TernaereLogik::Werte::Wahr) ? true : false;
            bool blres = bla || blb;
            return (blres == true) ? TernaereLogik::Werte::Wahr : TernaereLogik::Werte::Falsch;
        }
    }
}

int main()
{
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
