#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

long long problem1862E() {
    long long n, m, d, a_i, remove;
    std::cin >> n >> m >> d;
    std::vector<long long> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }

    long long max = 0;
    long long size = 0;
    long long sum = 0;
    std::map<long long, long long> movies;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            movies[a[i]]++;
            sum += a[i];
            size++;
        }
        if (size > m) {
            remove = movies.begin()->first;
            movies[remove]--;
            sum -= remove;
            if (movies[remove] == 0) {
                movies.erase(remove);
            }
            size--;
        }
        max = std::max(sum - d * (i + 1), max);
    }
    return max;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1862E() << "\n";
    }
    return 0;
}