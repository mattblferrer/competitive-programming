#include <iostream>
#include <string>

std::string problem1807B() {
    int n, a_i, odd, even;
    std::cin >> n;

    even = 0; 
    odd = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        if (a_i % 2 == 0) {
            even += a_i;
        }
        else {
            odd += a_i;
        }
    }
    
    if (even > odd) {
        return "YES";
    }
    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1807B() << std::endl;
    }

    return 0;
}