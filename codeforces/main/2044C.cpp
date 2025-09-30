#include <iostream>

long long problem2044C() {
    long long m, a, b, c, remove;
    std::cin >> m >> a >> b >> c;
    long long a_seats = m;
    long long b_seats = m;
    a_seats -= std::min(a, m);
    b_seats -= std::min(b, m);
    if (a_seats > 0 && c > 0) {
        remove = std::min(a_seats, c);
        a_seats -= remove;
        c -= remove;
    }
    if (b_seats > 0 && c > 0) {
        remove = std::min(b_seats, c);
        b_seats -= remove;
        c -= remove;
    }
    return 2*m - a_seats - b_seats;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2044C() << "\n";
    }
    return 0;
}