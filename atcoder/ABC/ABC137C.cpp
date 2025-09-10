#include <algorithm>
#include <iostream>
#include <map>
#include <string>

long long ABC137C() {
    long long n;
    std::cin >> n;
    std::string s;
    std::map<std::string, long long> anagrams;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        std::sort(s.begin(), s.end());
        anagrams[s]++;
    }
    long long pairs = 0;
    for (const auto& pair: anagrams) {
        pairs += pair.second * (pair.second - 1) / 2;
    }
    return pairs;
}

int main() {
    std::cout << ABC137C();
    return 0;
}