#include <iostream>
#include <map>
#include <string>

std::string problem977B() {
    long long n;
    std::string s;
    std::cin >> n >> s;
    std::map<std::string, long long> count;
    for (int i = 0; i < n - 1; i++) { 
        count[s.substr(i, 2)]++;
    }
    long long max_freq = 0;
    std::string max_substr;
    for (const auto& pair: count) {
        if (pair.second > max_freq) {
            max_freq = pair.second;
            max_substr = pair.first;
        }
    }
    return max_substr;
}

int main() {
    std::cout << problem977B();
    return 0;
}