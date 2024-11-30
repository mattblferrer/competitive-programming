#include <iostream>
#include <string>

void ABC382B() {
    int n, d;
    std::string s;
    std::cin >> n >> d >> s;
    bool* cookies = new bool[n];

    for (int i = 0; i < n; i++) {
        if (s[i] == '@') {
            cookies[i] = true;
        }
        else {
            cookies[i] = false;
        }
    }

    int curr = n - 1;
    for (int i = 0; i < d; i++) {
        while (!cookies[curr]) {
            curr -= 1;
        }
        cookies[curr] = false;
        curr -= 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (cookies[i]) {
            std::cout << '@';
        }
        else {
            std::cout << '.';
        }
    }
}

int main() { 
    ABC382B();
    return 0;
}