// KfzSteuer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//Aufgabe #320 in https://trainyourprogrammer.de/cplusplus
//

#include <iostream>
#include <vector>
#include <numeric>

namespace KfzSteuer {
    enum class MotorTyp : unsigned int { Diesel, Otto };

    class Automobil {
        MotorTyp motorTyp;
        unsigned int hubRaum;
        unsigned int emissionKm;
    public:
        Automobil() = default;
        Automobil(MotorTyp _motorTyp, unsigned int _hubRaum, unsigned int _emissionKm) : 
            motorTyp{_motorTyp}, hubRaum{_hubRaum}, emissionKm{_emissionKm}
        {}
        ~Automobil() = default;
        void setMotorTyp(MotorTyp _motorTyp) {
            motorTyp = _motorTyp;
        }
        void setHubRaum(unsigned int _hubRaum) {
            hubRaum = _hubRaum;
        }
        void setEmissionKm(unsigned int _emissionKm) {
            emissionKm = _emissionKm;
        }
        double getKfzSteuer() {
            return getKfzSteuer(motorTyp, hubRaum, emissionKm);
        }
        static double getKfzSteuer(MotorTyp _motorTyp, unsigned int _hubRaum, unsigned int _emissionKm) {
            double emissionsSteuer{ getEmissionsSteuer(_emissionKm) };
            double hubraumSteuer{ 0.0 };
            double hubraumSatz{ 0.0 };
            unsigned int hubraumFaktor{ 0 };

            if (_motorTyp == MotorTyp::Diesel) {
                hubraumSatz = 9.50;
            }
            if (_motorTyp == MotorTyp::Otto) {
                hubraumSatz = 2.00;
            }
            hubraumFaktor = (_hubRaum % 100 > 0) ? 1 : 0;
            hubraumFaktor += _hubRaum / 100;
            hubraumSteuer = hubraumFaktor * hubraumSatz;

            return emissionsSteuer + hubraumSteuer;
        }

        static double getEmissionsSteuer(unsigned int _emissionCO = 0) {
            std::vector<double> v{ 4.00,3.40,2.90,2.50,2.20,2.00 };
            unsigned int compVal{ 0 };
            compVal = 195;
            if (_emissionCO > compVal) {
                auto it = v.begin();
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0 * std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
            compVal = 175;
            if (_emissionCO > compVal) {
                auto it = v.begin()+1;
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0 * std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
            compVal = 155;
            if (_emissionCO > compVal) {
                auto it = v.begin()+2;
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0*std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
            compVal = 135;
            if (_emissionCO > compVal) {
                auto it = v.begin()+3;
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0 * std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
            compVal = 115;
            if (_emissionCO > compVal) {
                auto it = v.begin()+4;
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0 * std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
            compVal = 95;
            if (_emissionCO > compVal) {
                auto it = v.begin()+5;
                double sum{ (_emissionCO - compVal) * *it++ };
                sum += 20.0 * std::accumulate(it, v.end(), 0.0);
                return  sum;
            }
        }
    };
}

int main()
{
    std::cout << "Steuer Otto: " << KfzSteuer::Automobil::getKfzSteuer(KfzSteuer::MotorTyp::Otto, 1438, 130) << std::endl;
    std::cout << "Steuer Diesel: " << KfzSteuer::Automobil::getKfzSteuer(KfzSteuer::MotorTyp::Diesel, 1969, 158) << std::endl;

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
