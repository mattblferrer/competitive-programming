#include <iostream>

long long problem609B() {
    long long n, m, a_i;
    std::cin >> n >> m;
    long long* genres = new long long[m];
    long long pairs = 0;

    for (int i = 0; i < m; i++) {
        genres[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        genres[a_i - 1]++;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                continue;
            }
            pairs += genres[i] * genres[j];
        }
    }
    return pairs / 2;
}

int main() {
    std::cout << problem609B();
    return 0;
}