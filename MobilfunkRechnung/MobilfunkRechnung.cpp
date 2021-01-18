// MobilfunkRechnung.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Aufgabe #311 in https://trainyourprogrammer.de/cplusplus
//

#include <map>
#include <algorithm>
#include <limits>
#include <iostream>

namespace MobilFunk {
    struct Paket {
        std::string paketName;
        double basisPreis{ 0.0 };
        int freiMinuten{ 0 };
        double preisMinute{ 0.0 };
        Paket() = default;
        Paket(std::string _paketName, double _basisPreis, int _freiMinuten, double _preisMinute) :
            paketName{_paketName},
            basisPreis{_basisPreis},
            freiMinuten{_freiMinuten},
            preisMinute{ _preisMinute }
        {}
        double getMonatsBetrag(int _minuten) {
            double res{ static_cast<double>(_minuten - freiMinuten) };
            res = (res < 0) ? 0.0 : static_cast<double>(preisMinute * res);
            res += basisPreis;
            return res;
        }
    };
}
int main()
{
    std::map<std::string, MobilFunk::Paket> pakete{
        {"P_Basis", MobilFunk::Paket("P_Basis", 2.95,0,0.10)},
        {"P_100", MobilFunk::Paket("P_100", 3.95,100,0.12)},
        {"P_300", MobilFunk::Paket("P_300", 7.95,300,0.15)},
        {"P_600", MobilFunk::Paket("P_600", 12.95,600,0.20)},
        {"P_Flat", MobilFunk::Paket("P_Flat", 29.95,std::numeric_limits<int>::max(),0.00)}
    };

    int verbrauchteMinuten{ 450 };
    std::for_each(pakete.begin(), pakete.end(), [=](std::pair<std::string, MobilFunk::Paket> x) {
        std::cout << "Betrag fuer Tarif " << x.first << " : " << x.second.getMonatsBetrag(verbrauchteMinuten) << std::endl; });
    std::cout << "Ende\n";
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
