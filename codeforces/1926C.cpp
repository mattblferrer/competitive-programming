#include <cmath>
#include <iostream>
#include <string>

void problem1926C() {
    const int limit = 2 * std::pow(10, 5) + 1;
    int* sums = new int[limit];
    int s = 0;
    for (int i = 0; i <= limit; i++) {
        std::string num_string = std::to_string(i);
        for (int j = 0; j < num_string.length(); j++) {
            s += num_string[j] - '0';
        } 
        sums[i] = s;
    }

    int t, n;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> n;
        std::cout << sums[n] << "\n";
    }
}

int main() {
    problem1926C();
    
    return 0;
}