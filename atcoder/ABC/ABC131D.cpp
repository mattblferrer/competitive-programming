#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string ABC131D() {
    long long n, a_i, b_i;
    std::cin >> n;
    std::vector<std::pair<long long, long long>> jobs(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a_i >> b_i;
        jobs[i] = {a_i, b_i};
    }

    std::sort(jobs.begin(), jobs.end(), [](std::pair<long long, long long> a, 
        std::pair<long long, long long> b) {
            return a.second < b.second;
        });
    long long curr_time = 0;
    for (const auto& jobs: jobs) {
        curr_time += jobs.first;
        if (curr_time > jobs.second) {
            return "No";
        }
    }
    return "Yes";
}

int main() {
    std::cout << ABC131D();
    return 0;
}