#include <iostream>
#include <string>

std::string problem1509B() {
    int n;
    int ts = 0;
    int mid = 0;
    std::string s;
    std::cin >> n >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'T') {
            ts++;
        }
        if (ts == n / 3) {
            mid = i + 1;
        }
    }
    if (n - ts != n / 3) {
        return "NO";
    }
    
    int left = 0;
    int right = mid;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'M') {
            while (s[left] == 'M') {
                left++;
            }
            while (s[right] == 'M') {
                right++;
            }
            if (left > i || right < i || right > n - 1) {
                return "NO";
            }
            left++;
            right++;
        }
    }

    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1509B() << "\n";
    }

    return 0;
}