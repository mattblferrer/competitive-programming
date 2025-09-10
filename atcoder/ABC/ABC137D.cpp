#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

long long ABC137D() {
    long long n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::pair<long long, long long>> q(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a_i >> b_i;
        q[i] = {a_i, b_i};
    }

    long long reward = 0;
    std::sort(q.begin(), q.end(), [](std::pair<long long, long long>& a, 
        std::pair<long long, long long>& b) {
        return a.first < b.first;
    });
    std::priority_queue<long long> pq;
    long long ctr = 0;
    for (int i = m - 1; i >= 0; i--) {
        while (ctr != n && q[ctr].first <= m - i) {
            pq.push(q[ctr].second);
            ctr++;
            if (ctr == n) {
                break;
            }
        }
        if (!pq.empty()) {
            reward += pq.top();
            pq.pop();
        }
    }

    return reward;
}

int main() {
    std::cout << ABC137D();
    return 0;
}