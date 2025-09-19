#include <bits/stdc++.h>

class HexBigInt {
    public:
    std::vector<signed char> d;  // digits
    bool sign = false;  // false = pos, true = neg

    HexBigInt(long long a = 0) {
        if (a < 0) {
            sign = true;
            a = -a;
        }
        while (a > 0) {
            d.push_back(a % 16);
            a /= 16;
        }
    }
    HexBigInt(std::string& s) {
        std::vector<signed char> d;
        check_sign(s);
        int n = s.size();
        for (int i = n - 1; i >= sign; i--) {
            signed char ch = s[i] - '0';
            if (ch < 10) d.push_back(s[i] - '0');
            else d.push_back(s[i] - 'A' + 10);
        }
    }   
    HexBigInt(const char* s) {
        std::vector<signed char> d;
        std::string sc = s;
        check_sign(sc); 
        int n = sc.size();
        for (int i = n - 1; i >= sign; i--) {
            signed char ch = s[i] - '0';
            if (ch < 10) d.push_back(s[i] - '0');
            else d.push_back(s[i] - 'A' + 10);   
        }
    }   
    int size() const {
        return d.size();
    }
    void check_sign(std::string& s) {
        if (s.front() == '-') sign = true;
    }
    static HexBigInt abs(const HexBigInt& a) {
        HexBigInt c = a;
        c.sign = false;
        return c;
    }
    static HexBigInt add_abs(HexBigInt& a, const HexBigInt& b) {
        int n = std::max(a.size(), b.size());
        while (a.size() != n + 1) a.d.push_back(0);
        for (int i = 0; i < b.size(); i++) a.d[i] += b.d[i];
        for (int i = 0; i < n; i++) {
            if (a.d[i] > 15) {
                a.d[i] -= 16;
                a.d[i + 1]++;
            }
        }
        while (a.size() > 1 && a.d.back() == 0) a.d.pop_back();
        return a;
    }
    static HexBigInt sub_abs(HexBigInt& a, const HexBigInt& b) {
        int n = std::max(a.size(), b.size());
        for (int i = 0; i < b.size(); i++) a.d[i] -= b.d[i];
        for (int i = 0; i < n - 1; i++) {
            if (a.d[i] < 0) {
                a.d[i] += 16;
                a.d[i + 1]--;
            }
        }
        while (a.size() > 1 && a.d.back() == 0) a.d.pop_back();
        return a;
    }

    HexBigInt& operator=(const HexBigInt& a) {
        d.resize(a.size());
        for (int i = 0; i < a.size(); i++) {
            d[i] = a.d[i];
        }
        sign = a.sign;
        return *this;
    }
    friend bool operator==(const HexBigInt& a, const HexBigInt& b) {
        return a.d == b.d;
    }
    friend bool operator<(const HexBigInt& a,const HexBigInt& b){
        if (a.sign != b.sign) return a.sign > b.sign;
        int n = a.size(), m = b.size();
        if (n != m) return n < m;
        for (int i = n - 1; i >= 0; i--) {
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
        }
        return false;
    }
    friend bool operator>(const HexBigInt& a,const HexBigInt& b){
        return b < a;
    }
    friend bool operator>=(const HexBigInt& a,const HexBigInt& b){
        return !(a < b);
    }
    friend bool operator<=(const HexBigInt& a,const HexBigInt& b){
        return !(a > b);
    }
    friend HexBigInt& operator+=(HexBigInt& a, HexBigInt& b) {
        if (a.sign == b.sign) a = add_abs(a, b);
        else if (abs(a) == abs(b)) a = HexBigInt(0LL);
        else if (abs(a) <= abs(b)) {
            a = sub_abs(b, a);
            a.sign = b.sign;
        }
        else a = sub_abs(a, b);
        return a;
    }
    friend HexBigInt& operator-=(HexBigInt& a, HexBigInt& b) {
        if (a.sign != b.sign) a = add_abs(a, b);
        else if (abs(a) == abs(b)) a = HexBigInt(0LL);
        else if (abs(a) <= abs(b)) {
            a = sub_abs(b, a);
            a.sign = b.sign;
        }
        else a = sub_abs(a, b);
        return a;
    }
    friend HexBigInt operator+(HexBigInt& a, HexBigInt& b) {
        HexBigInt c = a;
        c += b;
        return c;
    }
    friend HexBigInt operator-(HexBigInt& a, HexBigInt& b) {
        HexBigInt c = a;
        c -= b;
        return c;
    }
    int operator[](const int idx) const {
        return (int)d[d.size() - idx - 1];
    }
    friend std::istream &operator>>(std::istream& in, HexBigInt& a) {
        std::string s;
        in >> s;
        a.check_sign(s);
        int n = s.size();
        for (int i = n - 1; i >= a.sign; i--) {
            signed char ch = s[i] - '0';
            if (ch < 10) a.d.push_back(s[i] - '0');
            else a.d.push_back(s[i] - 'A' + 10);
        }
        return std::cin;
    }
    friend std::ostream &operator<<(std::ostream& out, const HexBigInt& a) {
        int n = a.d.size();
        if (n == 0) {
            std::cout << "0";
            return std::cout;
        }
        if (a.sign) std::cout << '-';
        for (int i = n - 1; i >= 0; i--) {
            signed char ch = (int)a.d[i];
            if (ch < 10) std::cout << ch;
            else std::cout << (ch - 10 + 'A');
        }
        return std::cout;
    }
};