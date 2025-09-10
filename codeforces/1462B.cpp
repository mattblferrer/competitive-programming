#include <bits/stdc++.h>

std::string problem1462B() {
    int n;
    std::string s;
    std::cin >> n >> s;
    if (s == "2020") return "YES";
    for (int i = 0; i < 5; i++) {
        int j = n + i - 4;
        if (s.substr(0, i) + s.substr(j, 4 - i) == "2020") return "YES";
    }
    return "NO";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1462B() << "\n";
    }
    return 0;
}