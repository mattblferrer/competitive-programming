#include <iostream>

long long problem1176B() {
    long long n, a_i;
    std::cin >> n;
    long long* rem = new long long[3];
    for (int i = 0; i < 3; i++) {
        rem[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        rem[a_i % 3]++;
    }
    if (rem[1] > rem[2]) {
        return rem[0] + rem[2] + (rem[1] - rem[2]) / 3;
    }
    else {
        return rem[0] + rem[1] + (rem[2] - rem[1]) / 3;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1176B() << "\n";	
    }   
   

    return 0;
}