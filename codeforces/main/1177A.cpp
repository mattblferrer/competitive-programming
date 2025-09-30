#include <bits/stdc++.h>

int problem1177A() {
    long long k;
    std::cin >> k;
    if (k < 10) return k;

    long long ctr = 1, curr = 0;
    std::vector<int> lb = {0};
    while (curr < powl(10, 14)) {
        curr += (powl(10, ctr) - powl(10, ctr - 1)) * ctr;
        lb.push_back(curr + 1);
        ctr++;
    }
    for (int i = 0; i < lb.size(); i++) {
        if (lb[i] > k) {
            ctr = i;
            break;
        }
    }
    for (int i = 1; i < ctr; i++) {
        k -= (powl(10, i) - powl(10, i - 1)) * i;
    }
    long long num = powl(10, ctr - 1) + (k - 1) / ctr, digit = (k - 1) % ctr;
    std::string num_str = std::to_string(num);
    return num_str[digit] - '0';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem1177A() << "\n";
    return 0;
}