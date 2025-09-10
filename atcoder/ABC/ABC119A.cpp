#include <bits/stdc++.h>

std::string ABC119A() {
    std::string s;
    std::cin >> s;
    int year = stoi(s.substr(0, 4));
    int month = stoi(s.substr(5, 2));
    if (year < 2019) return "Heisei";
    if (year > 2019) return "TBD";
    if (month <= 4) return "Heisei";
    return "TBD";
}

int main() {
    std::cout << ABC119A();
    return 0;
}