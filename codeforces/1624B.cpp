#include <bits/stdc++.h>

std::string problem1624B() {
    int a, b, c;
    std::cin >> a >> b >> c;
    if ((b - (c - b)) % a == 0 && (b - (c - b)) > 0) return "YES";  // a
    if ((c + a) % 2 == 0 && ((c + a) / 2) % b == 0) return "YES";  // b
    if ((b + (b - a)) % c == 0 && (b + (b - a)) > 0) return "YES";  // c 
    return "NO";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1624B() << "\n";
    }
    return 0;
}