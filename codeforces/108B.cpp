#include <bits/stdc++.h>

std::string problem108B() {
    int n, a_i;
    std::cin >> n;
    std::set<int> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.insert(a_i);
    }
    std::vector<int> a_vec;
    for (int a_i: a) {
        a_vec.push_back(a_i);
    }
    std::sort(a_vec.begin(), a_vec.end(), std::greater());
    for (int i = 0; i < a_vec.size() - 1; i++) {
        if (a_vec[i] < 2 * a_vec[i + 1]) return "YES";
    }
    return "NO";
}

int main() {
    std::cout << problem108B();	

    return 0;
}