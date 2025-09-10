#include <iostream>
#include <string>

void problem2044B() {
    std::string a;
    std::cin >> a;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == 'p') {
            a[i] = 'q';
        }
        else if (a[i] == 'q') {
            a[i] = 'p';
        }
    }
    for (int i = a.length() - 1; i >= 0; i--) {
        std::cout << a[i];
    }
    std::cout << '\n';
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2044B();
    }
    return 0;
}