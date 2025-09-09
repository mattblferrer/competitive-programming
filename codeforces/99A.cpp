#include <iostream>
#include <string>

std::string problem99A() {
    std::string n;
    std::cin >> n;
    std::string int_p = "";

    for (int i = 0; i < n.length(); i++) {
        if (n[i] == '.') {
            if (n[i - 1] == '9') {
                return "GOTO Vasilisa.";
            }
            else if (n[i + 1] > '4') {
                return int_p.substr(0, i - 1) + (char)(int_p[i - 1] + 1);
            }
            else {
                return int_p;
            }
        }
        else {
            int_p += n[i];
        }
    }
}

int main() {
    std::cout << problem99A();
    return 0;
}