#include <iostream>
#include <string>

long long ABC046D() {
    std::string s;
    std::cin >> s;
    long long score = 0;
    for (char c: s) {
        if (c == 'g') {
            score++;
        }
        else {
            score--;
        }
    }
    return score / 2;
}

int main() {
    std::cout << ABC046D();
    return 0;
}