#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

class BigInt {
    public:
    std::vector<signed char> d;  // digits
    bool sign = false;  // false = pos, true = neg

    BigInt(long long a = 0) {
        if (a < 0) {
            sign = true;
            a = -a;
        }
        while (a > 0) {
            d.push_back(a % 10);
            a /= 10;
        }
    }
    BigInt(std::string& s) {
        std::vector<signed char> d;
        check_sign(s);
        int n = s.size();
        for (int i = n - 1; i >= sign; i--) d.push_back(s[i] - '0');    
    }   
    BigInt(const char* s) {
        std::vector<signed char> d;
        std::string sc = s;
        check_sign(sc); 
        int n = sc.size();
        for (int i = n - 1; i >= sign; i--) d.push_back(s[i] - '0');    
    }   
    int size() const {
        return d.size();
    }
    void check_sign(std::string& s) {
        if (s.front() == '-') sign = true;
    }
    static BigInt abs(const BigInt& a) {
        BigInt c = a;
        c.sign = false;
        return c;
    }
    static BigInt add_abs(BigInt& a, const BigInt& b) {
        int n = std::max(a.size(), b.size());
        while (a.size() != n + 1) a.d.push_back(0);
        for (int i = 0; i < b.size(); i++) a.d[i] += b.d[i];
        for (int i = 0; i < n; i++) {
            if (a.d[i] > 9) {
                a.d[i] -= 10;
                a.d[i + 1]++;
            }
        }
        while (a.size() > 1 && a.d.back() == 0) a.d.pop_back();
        return a;
    }
    static BigInt sub_abs(BigInt& a, const BigInt& b) {
        int n = std::max(a.size(), b.size());
        for (int i = 0; i < b.size(); i++) a.d[i] -= b.d[i];
        for (int i = 0; i < n - 1; i++) {
            if (a.d[i] < 0) {
                a.d[i] += 10;
                a.d[i + 1]--;
            }
        }
        while (a.size() > 1 && a.d.back() == 0) a.d.pop_back();
        return a;
    }

    BigInt& operator=(const BigInt& a) {
        d.resize(a.size());
        for (int i = 0; i < a.size(); i++) {
            d[i] = a.d[i];
        }
        sign = a.sign;
        return *this;
    }
    friend bool operator==(const BigInt& a, const BigInt& b) {
        return a.d == b.d;
    }
    friend bool operator<(const BigInt& a,const BigInt& b){
        if (a.sign != b.sign) return a.sign > b.sign;
        int n = a.size(), m = b.size();
        if (n != m) return n < m;
        for (int i = n - 1; i >= 0; i--) {
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
        }
        return false;
    }
    friend bool operator>(const BigInt& a,const BigInt& b){
        return b < a;
    }
    friend bool operator>=(const BigInt& a,const BigInt& b){
        return !(a < b);
    }
    friend bool operator<=(const BigInt& a,const BigInt& b){
        return !(a > b);
    }
    friend BigInt& operator+=(BigInt& a, BigInt& b) {
        if (a.sign == b.sign) a = add_abs(a, b);
        else if (abs(a) == abs(b)) a = BigInt(0LL);
        else if (abs(a) <= abs(b)) {
            a = sub_abs(b, a);
            a.sign = b.sign;
        }
        else a = sub_abs(a, b);
        return a;
    }
    friend BigInt& operator-=(BigInt& a, BigInt& b) {
        if (a.sign != b.sign) a = add_abs(a, b);
        else if (abs(a) == abs(b)) a = BigInt(0LL);
        else if (abs(a) <= abs(b)) {
            a = sub_abs(b, a);
            a.sign = b.sign;
        }
        else a = sub_abs(a, b);
        return a;
    }
    friend BigInt operator+(BigInt& a, BigInt& b) {
        BigInt c = a;
        c += b;
        return c;
    }
    friend BigInt operator-(BigInt& a, BigInt& b) {
        BigInt c = a;
        c -= b;
        return c;
    }
    int operator[](const int idx) const {
        return (int)d[d.size() - idx - 1];
    }
    friend std::istream &operator>>(std::istream& in, BigInt& a) {
        std::string s;
        in >> s;
        a.check_sign(s);
        int n = s.size();
        for (int i = n - 1; i >= a.sign; i--) a.d.push_back(s[i] - '0');
        while (a.size() > 1 && a.d.back() == 0) a.d.pop_back();
        return std::cin;
    }
    friend std::ostream &operator<<(std::ostream& out, const BigInt& a) {
        int n = a.d.size();
        if (n == 0) {
            std::cout << "0";
            return std::cout;
        }
        if (a.sign) std::cout << '-';
        for (int i = n - 1; i >= 0; i--) {
            std::cout << (int)a.d[i];
        }
        return std::cout;
    }
};

void solve() {
    BigInt a, b;
    cin >> a >> b;
    if (a < b) cout << "<";
    else if (a > b) cout << ">";
    else cout << "=";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}