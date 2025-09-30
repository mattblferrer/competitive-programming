#include <bits/stdc++.h>

void problem12C() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> tags(n);
    std::map<std::string, int> items;
    for (int i = 0; i < n; i++) {
        std::cin >> tags[i];
    }
    std::sort(tags.begin(), tags.end());
    std::string item;
    for (int i = 0; i < m; i++) {
        std::cin >> item;
        items[item]++;
    }
    std::vector<std::pair<std::string, int>> item_vec;
    for (const auto& pair: items) {
        item_vec.push_back(pair);
    }
    std::sort(item_vec.begin(), item_vec.end(), [](std::pair<std::string, int> a, 
        std::pair<std::string, int> b) {
            return a.second > b.second;
        });
    int a = 0, b = 0;
    for (int i = 0; i < item_vec.size(); i++) {
        a += tags[i] * item_vec[i].second;
        b += tags[n - i - 1] * item_vec[i].second;
    }
    std::cout << a << " " << b;
}

int main() {
    problem12C();
    return 0;
}