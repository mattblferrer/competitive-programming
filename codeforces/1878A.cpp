#include <iostream>
#include <string>

std::string problem1878A() {
    long long n, k, a_i;
    bool seen_k = false;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        if (a_i == k) {
            seen_k = true;
        }
    }
    
    if(seen_k) {
        return "YES";
    }
    else {
        return "NO";
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1878A() << std::endl;
    }

    return 0;
}