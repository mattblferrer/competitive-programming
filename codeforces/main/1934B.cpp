#include <iostream> 
#include <map>

long long problem1934B() { 
    long long n, steps;
    std::cin >> n;
    if (n > 30) {
        steps = n / 15 - 1;  // reduce to below 2*15=30
        n = n % 15 + 15;
    }
    else {
        steps = 0;
    }
    int t[5] = {1,3,6,10,15};

    std::map<int, int> shortcuts;
    shortcuts[0] = 0;
    for (int i = 1; i <= 30; i++) {
        int min = 100;
        for (int j = 0; j < 5; j++) {
            if (t[j] > i) {
                break;
            }
            min = std::min(min, shortcuts[i - t[j]] + 1);
        } 
        shortcuts[i] = min;
    }

    return steps + shortcuts[n];
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1934B() << "\n";
    }
    return 0;
}