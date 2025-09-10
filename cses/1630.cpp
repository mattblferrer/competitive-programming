#include <algorithm>
#include <iostream>
#include <vector>

long long CSES1630() {
    long long n, a, d;
    std::cin >> n;
    std::vector<std::pair<long long, long long>> tasks(n);
    for (long long i = 0; i < n; i++) {
        std::cin >> a >> d;
        tasks[i] = {a, d};
    }
    long long reward = 0;
    long long time = 0;
    std::sort(tasks.begin(), tasks.end(), [](std::pair<long long, long long> a, 
        std::pair<long long, long long> b) {
            return a.first < b.first;
        });
    for (long long i = 0; i < n; i++) {
        time += tasks[i].first;
        reward += tasks[i].second - time;
    }

    return reward;
}

int main() {
    std::cout << CSES1630();
    return 0;
}