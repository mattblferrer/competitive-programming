#include <bits/stdc++.h>

void problem1157B() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::array<int, 9> f;
    for (int i = 0; i < 9; i++) {
        std::cin >> f[i];
    }
    bool op = false;
    for (int i = 0; i < n; i++) {
        int rep = s[i] - '0';
        if (f[rep - 1] + '0' > s[i]) {
            s[i] = f[rep - 1] + '0';
            op = true;
        }
        else if (op && f[rep - 1] + '0' != s[i]) break;
    }
    std::cout << s;
}

int main() {
    problem1157B();
    return 0;
}