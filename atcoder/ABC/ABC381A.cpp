#include <iostream>
#include <string>

std::string ABC381A() {
    int n;
    std::cin >> n;
    std::string t;
    std::cin >> t;
    
    if (n % 2 == 0) {
        return "No";
    }
    for (int i = 0; i < (n + 1) / 2 - 1; i++) {
        if (t[i] != '1') {
            return "No";
        }
    }
    if (t[(n + 1) / 2 - 1] != '/') {
        return "No";
    }
    for (int i = (n + 1) / 2; i < n; i++) {
        if (t[i] != '2') {
            return "No";
        }
    }
    return "Yes";
}

int main() { 
    std::cout << ABC381A();
    return 0;
}