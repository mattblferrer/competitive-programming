#include <algorithm>
#include <iostream> 
#include <vector>

long long problem1934A() { 
    long long n, a_i;
    std::cin >> n;
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    } 
    std::sort(a.begin(), a.end());
    long long s = a.size() - 1;
    long long s_1 = a[s] - a[0];
    long long s_2 = a[s - 1] - a[0];
    long long s_3 = a[s - 1] - a[1];
    long long s_4 = a[s] - a[1];
    long long sum = s_1 + s_2 + s_3 + s_4;
    return sum;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1934A() << "\n";
    }
    return 0;
}