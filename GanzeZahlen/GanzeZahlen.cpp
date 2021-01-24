// GanzeZahlen.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

class GanzeZahl {
public:
    void set(std::vector<uint8_t>&& _digits) {
        set(std::forward<std::vector<uint8_t>&&>(_digits), [this]() {this->cutLeadingZeros(); });
    }

    void set(std::vector<uint8_t>&& _digits, std::function<void()> _func) {
        digits = _digits;
        _func();
    }

    void set(uint64_t _number) {
        set(_number, [this]() {this->cutLeadingZeros(); });
    }

    void set(uint64_t _number, std::function<void()> _func) {
        auto tmp{ _number };
        do{
            auto rem{ tmp % 10 };
            digits.push_back(tmp);
            tmp /= 10;
        } while (tmp > 0);
        _func();
    }

    std::vector<uint8_t> get() const {
        return digits;
    }

    size_t getDigits() const {
        return digits.size();
    }

    friend bool operator< (const GanzeZahl& lhs, const GanzeZahl& rhs) {
        if (lhs.getDigits() == rhs.getDigits()) {
            auto itlhs{ lhs.digits.end() - 1 };
            auto itrhs{ rhs.digits.end() - 1 };
            while (*itlhs == *itrhs && itlhs!=lhs.digits.begin() && itrhs!=rhs.digits.begin()) {
                itlhs--;
                itrhs--;
            }
            return *itlhs < *itrhs;
        }
        return lhs.getDigits() < rhs.getDigits();
    }

    friend bool operator<= (const GanzeZahl& lhs, const GanzeZahl& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator== (const GanzeZahl& lhs, const GanzeZahl& rhs) {
        return (lhs <= rhs) && (rhs <= lhs);
    }

    void cutLeadingZeros() {
        cutLeadingZeros(this);
    }

    static void cutLeadingZeros(GanzeZahl* _gz) {
        auto it{ _gz->digits.end()-1 };
        while (it != _gz->digits.begin() && *it==0) {
            _gz->digits.erase(it);
            it = _gz->digits.end() - 1;
        }
    }

    std::string toString() const {
        std::string res;
        std::for_each(digits.begin(), digits.end(), [&](uint8_t x) {res.insert(0,std::to_string(x)); });
        return res;
    }

    //Definition der Rechenoperationen durch Überladen der Operatoren
    //Siehe: https://en.cppreference.com/w/cpp/language/operators

    //Addition: Schriftliche Addition aus der Schule
    GanzeZahl& operator+=(const GanzeZahl& rhs)
    {                           
        if (rhs.getDigits() > this->getDigits()) {
            auto diffDigits{ rhs.getDigits() - this->getDigits() };
            this->digits.resize(this->getDigits() + diffDigits);
        }
        this->digits.resize(this->getDigits() + 1);
        uint8_t ws1{ 0 };
        uint8_t ws2{ 0 };
        auto itrhs{ rhs.digits.begin() };
        auto itthis{ this->digits.begin() };
        while (itrhs != rhs.digits.end()) {
            ws2 = *itrhs + *itthis + ws1;
            ws1 = 0;
            *itthis = ws2 % 10;
            if (ws2 >= 10) {
                ws1 = ws2 / 10;
            }
            itrhs++;
            itthis++;
        }
        *itthis += ws1;
        itthis = this->digits.end() - 1;
        if (*itthis == 0) {
            this->digits.pop_back();
        }
        return *this;
    }

    GanzeZahl& operator+=(const uint64_t& rhs) {
        GanzeZahl g;
        g.set(rhs);
        *this += g;
        return *this;
    }

    friend GanzeZahl operator+(GanzeZahl lhs,
        const GanzeZahl& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    //Subtraktion: Schriftliche Subtraktion aus der Schule
    GanzeZahl& operator-=(const GanzeZahl& rhs)
    {
        if (*this < rhs) {
            return *this;
        }
        uint8_t ws1{ 0 };
        uint8_t ws2{ 0 };
        auto itrhs{ rhs.digits.begin() };
        auto itthis{ this->digits.begin() };
        while (itrhs != rhs.digits.end()) {
            if (*itrhs + ws1 <= *itthis) {
                ws2 = *itthis - (*itrhs + ws1);
                ws1 = 0;
            }
            else {
                ws2 = 10 + (*itthis) - (*itrhs + ws1);
                ws1 = 1;
            }
            *itthis = ws2;
            itrhs++;
            itthis++;
        }
        if (itthis != digits.end()) {
            *itthis -= ws1;
        }
        return *this;
    }

    GanzeZahl& operator-=(const uint64_t& rhs) {
        GanzeZahl g;
        g.set(rhs);
        *this -= g;
        return *this;
    }

    friend GanzeZahl operator-(GanzeZahl lhs,
        const GanzeZahl& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    //Multiplikation: Schriftliche Multiplikation aus der Schule
    GanzeZahl& operator*=(const GanzeZahl& rhs)
    {
        GanzeZahl g1;
        GanzeZahl g2;
        
        g2.set(std::vector<uint8_t>(this->getDigits(), 0), []() {});
        this->digits.resize(this->getDigits() + 1);
        uint8_t ws1{ 0 };
        uint8_t ws2{ 0 };
        auto k{ 0 };
        
        auto itrhs{ rhs.digits.begin() };
        while (itrhs != rhs.digits.end()) {
            g1.set(this->get(), []() {});
            auto itg1{ g1.digits.begin() };
            while (itg1 != g1.digits.end()) {
                ws2 = *itrhs * *itg1 + ws1;
                ws1 = 0;
                *itg1 = ws2 % 10;
                if (ws2 >= 10) {
                    ws1 = ws2 / 10;
                }
                itg1++;
            }
            itrhs++;
            g1.digits.push_back(ws1);
            auto v = std::vector<uint8_t>(k, 0);
            g1.digits.insert(g1.digits.begin(), v.begin(),v.end());
            g2 += g1;
            k++;
        }
        g2.cutLeadingZeros();
        *this = g2;
        return *this;
    }

    GanzeZahl& operator*=(const uint64_t& rhs) {
        GanzeZahl g;
        g.set(rhs);
        *this *= g;
        return *this;
    }

    friend GanzeZahl operator*(GanzeZahl lhs,
        const GanzeZahl& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    //Division: Schriftliche Division aus der Schule funktioniert hier nicht
    //Eigenes Verfahren durch Probieren
    GanzeZahl& operator/=(const GanzeZahl& rhs)
    {
        GanzeZahl g1;
        GanzeZahl g2;
        g1.set(std::vector<uint8_t>(1, 1), []() {});
        g2.set(std::vector<uint8_t>(1, 1), []() {});
        int k{ 1 };
        while (g1 * rhs < *this) {
            g1 += g2;
            k++;
        }
        g1 -= g2;
        *this = g1;
        return *this;
    }

    GanzeZahl& operator/=(const uint64_t& rhs) {
        GanzeZahl g;
        g.set(rhs);
        *this /= g;
        return *this;
    }

    friend GanzeZahl operator/(GanzeZahl lhs,
        const GanzeZahl& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    //Rest der ganzzahligen Division
    GanzeZahl& operator%=(const GanzeZahl& rhs)
    {
        GanzeZahl g;
        g = *this - (*this / rhs) * rhs;
        g.cutLeadingZeros();
        *this = g;
        return *this;
    }

    friend GanzeZahl operator%(GanzeZahl lhs,
        const GanzeZahl& rhs)
    {
        lhs %= rhs;
        return lhs;
    }

    static GanzeZahl& SqRoot(const GanzeZahl& rhs)
    {
        GanzeZahl g;
        g.set({ 0 });
        do {
            g += 1;
        }
        while (g * g < rhs);
        return g;
    }

private:
    std::vector<uint8_t> digits;
};

int main()
{
    {
        std::cout << "Beispiel 1" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,4 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 2" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,5 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 3" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4,3 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,5 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 - s2;
        std::cout << "Die Zahl s1-s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 4" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,5,5 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 5" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,5,0, 2 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 6" << std::endl;
        GanzeZahl s1;
        s1.set({ 1,2,7,4,4,5,4,7,5,9,1,0,4,5,3,8,4,9,1,0,8,7,5,3,8,5,0,2,5,2,7,3,8,2,0,1,2,3,5,4,7,5,9,5,7,2,5,4,7,4 });
        GanzeZahl s2;
        s2.set({ 4,4,4,7,5,0,2,3,6,3,8,4,7,4,8,4,8,3,5,3,8,7,5,6,3,0,9,6,3,5,3,7,6,5,8,4,9,4,6,3,7,3,8,4,8,6,9,3,5,1,0,5,7 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 7" << std::endl;
        auto ws = std::vector<uint8_t>(80, 0);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s1;
        s1.set(std::move(ws));
        ws.clear();
        ws.resize(80);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s2;
        s2.set(std::move(ws));
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 + s2;
        std::cout << "Die Zahl s1+s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 8" << std::endl;
        auto ws = std::vector<uint8_t>(9, 0);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s1;
        s1.set(std::move(ws));
        ws.clear();
        ws.resize(7);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s2;
        s2.set(std::move(ws));
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 * s2;
        std::cout << "Die Zahl s1*s2: " << r3.toString() << std::endl;
        s2 *= s1;
        std::cout << "Die Zahl s1*s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 9" << std::endl;
        srand(time(0));
        auto ws = std::vector<uint8_t>(99, 0);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s1;
        s1.set(std::move(ws));
        ws.clear();
        ws.resize(111);
        std::transform(ws.begin(), ws.end(), ws.begin(), [](uint8_t x) {x = static_cast<uint8_t>(rand() % 10); return x; });
        GanzeZahl s2;
        s2.set(std::move(ws));
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 * s2;
        std::cout << "Die Zahl s1*s2: " << r3.toString() << std::endl;
        s2 *= s1;
        std::cout << "Die Zahl s1*s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 10" << std::endl;
        GanzeZahl s1;
        s1.set({ 4,4,4 });
        GanzeZahl s2;
        s2.set({ 3,5,2 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s1 - s2;
        std::cout << "Die Zahl s1-s2: " << r3.toString() << std::endl;
        s2 += s1;
        std::cout << "Die Zahl s1+s2: " << s2.toString() << std::endl;
    }
    {
        std::cout << "Beispiel 11" << std::endl;
        GanzeZahl s1;
        s1.set({ 9,8 });
        GanzeZahl s2;
        s2.set({ 1,2,7,2 });
        std::cout << "Die Zahl s1: " << s1.toString() << std::endl;
        std::cout << "Die Zahl s2: " << s2.toString() << std::endl;
        auto r3 = s2 / s1;
        std::cout << "Die Zahl s2/s1: " << r3.toString() << std::endl;
        auto r4 = s2 % s1;
        std::cout << "Die Zahl s2%s1: " << r4.toString() << std::endl;
    }
    {
        std::vector<GanzeZahl> vec;// 
        std::vector<uint8_t> ivec{ 2, 7, 11, 13, 17, 19, 23, 25, 27, 29 };
        
        for (auto it = ivec.begin(); it != ivec.end(); it++) {
            GanzeZahl g0;
            g0.set(*it);
            vec.push_back(g0);
        }

        GanzeZahl g;
        g.set({ 1 });
        for (auto it = vec.begin(); it != vec.end(); it++) {
            g *= *it;
        }

        std::cout << "Beispiel 12" << std::endl;
        std::cout << "Zahl: " << g.toString() << std::endl;
        //for (auto it = vec.begin(); it != vec.end(); it++) {
        //    std::cout << "Teiler: " << it->toString() << "  ";
        //    std::cout << "Rest: " << (g%(*it)).toString() << std::endl;
        //}

        
        //GanzeZahl g1; g1.set({ 29 });
        //GanzeZahl g2; g2.set({ 27 });
        //GanzeZahl g3; g3.set({ 25 });
        //GanzeZahl g4; g4.set({ 23 });
        //GanzeZahl g5; g5.set({ 19 });
        //GanzeZahl g6; g6.set({ 17 });
        //GanzeZahl g7; g7.set({ 16 });
        //GanzeZahl g8; g8.set({ 13 });
        //GanzeZahl g9; g9.set({ 11 });
        //GanzeZahl g10; g10.set({ 7 });
        //GanzeZahl g11; g11.set({ 2 });
        //auto r3 = g1 * g2 * g3 * g4 * g5 * g6 * g7 * g8 * g9 * g10 * g11;
        //std::cout << "Die Zahl: " << r3.toString() << std::endl;
        
    }
    {
        std::cout << "Beispiel 13" << std::endl;
        GanzeZahl g;
        g.set({ 9,2,7 });
        GanzeZahl g1;
        g1.set({ 0 });
        g1 += GanzeZahl::SqRoot(g);
        std::cout << "Zahl: " << g1.toString() << std::endl;
    }
}


