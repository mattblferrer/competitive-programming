#include <iostream>
#include <string>

std::string problem1669D() {
    int n;
    std::string s;
    std::cin >> n >> s;
    s.append("W");
    int curr = 0;
    bool b = false;
    bool r = false;

    for (int i = 0; i <= n; i++) {
        if (s[i] == 'W') {
            if (curr == 1) {
                return "NO";
            }
            if (curr && !(b && r)) {
                return "NO";
            }
            curr = 0;
            b = r = false;
            continue;
        }
        if (s[i] == 'B') {
            b = true;
        }
        if (s[i] == 'R') {
            r = true;
        }
        curr++;
    }
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1669D() << "\n";
    }

    return 0;
}