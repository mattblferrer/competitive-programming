#include <iostream>

/*
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
2^4 (16)
3^3 (27)
5^2 (25)
7
9
11
13
17
19
23
29
*/

void solve() {
    int n; std::cin >> n; std::cout << n << '\n';

    switch (n) {
        case 1:
            std::cout << "1"; break;
        case 2:
            std::cout << "1 2"; break;
        case 3:
            std::cout << "1 2 4"; break;
        case 4:
            std::cout << "1 2 3 6"; break;
        case 5:
            std::cout << "1 2 3 4 12"; break;
        case 6:
            std::cout << "1 2 3 4 5 60"; break;
        case 7:
            std::cout << "1 2 3 4 5 6 60"; break;
        case 8:
            std::cout << "1 2 3 4 5 6 7 420"; break;
        case 9:
            std::cout << "1 2 3 4 5 6 7 8 840"; break;
        case 10:
            std::cout << "1 2 3 4 5 6 7 8 9 2520"; break;
        case 11:
            std::cout << "1 2 3 4 5 6 7 8 9 10 2520"; break;
        case 12:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 27720"; break;
        case 13:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 27720"; break;
        case 14:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 360360"; break;
        case 15:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 360360"; break;
        case 16:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 360360"; break;
        case 17:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 720720"; break;
        case 18:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 12252240"; break;
        case 19:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 12252240"; break;
        case 20:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 232792560"; break;
        case 21:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 232792560"; break;
        case 22:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 232792560"; break;
        case 23:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 232792560"; break;
        case 24:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 5354228880"; break;
        case 25:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 5354228880"; break;
        case 26:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26771144400"; break;
        case 27:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 26771144400"; break;
        case 28:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 80313433200"; break;
        case 29:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 80313433200"; break;
        case 30:
            std::cout << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 2329089562800"; break;
    }
    std::cout << '\n';
}

int main() {
    int q; std::cin >> q;
    while (q--) { solve(); }
}