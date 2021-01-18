// KniffelVereinfacht.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <array>
#include <vector>
//#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <iostream>

namespace Kniffel {
    enum class Pasch : unsigned int { ZweierPasch, DreierPasch, ViererPasch, FuenferPasch };
    struct Zustand {
        int punkte{ 0 };
        std::vector<int> fertigeWuerfe;
        std::array<int, 5> aktuellerWurf;
        std::vector< std::tuple<int, int, double>> w;

        void neuerWurf() {
            aktuellerWurf.fill(0);
            srand(time(0));
            std::transform(aktuellerWurf.begin(), aktuellerWurf.end(), aktuellerWurf.begin(), 
                [](int x) {return (rand() % 6) + 1; });
            std::sort(aktuellerWurf.begin(), aktuellerWurf.end());
        }

        void ermittlePasche() {
            w.clear();
            std::for_each(aktuellerWurf.begin(), aktuellerWurf.end(),
                [&](int x) {auto anz{ std::count(aktuellerWurf.begin(), aktuellerWurf.end(),x) };
            w.push_back(std::tuple<int, int, double>{x, anz, wahrscheinlichkeit(anz)});
                });
            w.erase(std::unique(w.begin(), w.end()), w.end());
        }

        double wahrscheinlichkeit(int _zahl) {
            double wkt{ 6.0 / 252.0 };
            if (_zahl == 1) return 36.0 * wkt;
            if (_zahl == 2) return 25.0 * wkt;
            if (_zahl == 3) return 15.0 * wkt;
            if (_zahl == 4) return 5.0 * wkt;
            if (_zahl == 5) return wkt;
            return 0.0;
        }

        double waehleZahl() {
            //std::list<double> v;
            std::sort(w.begin(), w.end(),
                [](std::tuple<int, int, double> x, std::tuple<int, int, double> y) {
                    double dx{ static_cast<double>(std::get<0>(x) * std::get<1>(x)) / std::get<2>(x) };
                    double dy{ static_cast<double>(std::get<0>(y) * std::get<1>(y)) / std::get<2>(y) };
                    return dx > dy;
            });
            //std::for_each(w.begin(), w.end(),
            //    [=](std::tuple<int, int, double> x) {
            //        if (std::find(fertigeWuerfe.begin(), fertigeWuerfe.end(), std::get<0>(x))!= fertigeWuerfe.end()) {
            //            fertigeWuerfe.push_back(std::get<0>(x));
            //            return;
            //        }
            //    });
            int j{ 0 };
            while (j < w.size() && 
                std::find(fertigeWuerfe.begin(), fertigeWuerfe.end(), std::get<0>(w[j])) != fertigeWuerfe.end()) {
                j++;
            }
            if (1 + j < w.size()) {
                punkte += std::get<0>(w[j]) * std::get<1>(w[j]);
                fertigeWuerfe.push_back(std::get<0>(w[j]));
            }
            
            return 0.0;
        }
    };
}
int main()
{
    Kniffel::Zustand zustand;
    for (auto j = 0; j < 6; ++j) {
        zustand.neuerWurf();
        zustand.ermittlePasche();
        zustand.waehleZahl();
    }
    std::cout << "Achtung Return! "<< zustand.punkte << std::endl;
    return 0;

    //Das wird nicht mehr abgearbeitet:
    std::vector<std::string> vec;
    size_t sum{ 0 };
    size_t cnt{ 0 };
    for (auto a = 1; a < 7; a++) {
        for (auto b = a; b < 7; b++) {
            for (auto c = b; c < 7; c++) {
                for (auto d = c; d < 7; d++) {
                    for (auto e = d; e < 7; e++) {
                        std::string str;
                        sum++;
                        str += std::to_string(a);
                        str += std::to_string(b);
                        str += std::to_string(c);
                        str += std::to_string(d);
                        str += std::to_string(e);
                        std::sort(str.begin(), str.end());
                        if (str.find("6") != std::string::npos) {
                            cnt++;
                        }
                        vec.push_back(str);
                        
                    }
                }
            }
        }
    }

    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    std::cout << "Summe " << sum << std::endl;
    std::cout << "Kontrolle " << vec.size() << std::endl;
    std::cout << "cnt " << cnt << std::endl;
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
