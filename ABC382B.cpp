#include <iostream>
#include <string>

void ABC382B() {
    int n, d;
    std::string s;
    std::cin >> n >> d >> s;
    bool* cookies = new bool[n];
    int curr = n - 1;

    for (int i = 0; i < d; i++) {
        while (s[curr] == '.') {
            curr -= 1;
        }
        s[curr] = '.';
        curr -= 1;
    }
    std::cout << s;
}

int main() { 
    ABC382B();
    return 0;
}