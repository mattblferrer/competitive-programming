#include <iostream>

long long ARC174B() {
    long long* a = new long long[5];
    long long* p = new long long[5];
    long long stars = 0;
    long long reviews = 0;

    for (int i = 0; i < 5; i++) {
        std::cin >> a[i];
        stars += a[i] * (i + 1);
        reviews += a[i];
    }
    for (int i = 0; i < 5; i++) {
        std::cin >> p[i];
    }
    if (stars / reviews >= 3) {
        return 0;
    }
    long long curr = 0;
    long long min = 99999999999999999;
    
    // case 1, all 4 stars
    curr = p[3] * (3 * reviews - stars);
    min = std::min(curr, min);

    // case 2, all 5 stars
    curr = p[4] * ((3 * reviews - stars + 1) / 2);
    min = std::min(curr, min);

    // case 3, all 5 stars + one 4 star
    curr = p[4] * ((3 * reviews - stars) / 2) + p[3];
    min = std::min(curr, min);

    return min;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << ARC174B() << "\n";
    }
    return 0;
}