#include <iostream>
#include <vector>

long long ARC174D() {
    long long n;
    std::cin >> n;

    long long count = 0;
    long long a = 100;
    long long b = 10;
    std::vector<long long> start = {1};
    std::vector<long long> end = {1};
    for (int i = 0; i < 9; i++) {
        start.push_back(a - 2*b);
        end.push_back(a - 2*b);
        start.push_back(a - b);
        end.push_back(a + b - 1);
        a *= 100;
        b *= 10;
    }
    for (unsigned long long i = 0; i < start.size(); i++) {
        if (n > end[i]) {
            count += end[i] - start[i] + 1;
        }
        else if (n >= start[i]) {
            count += n - start[i] + 1;
        }
    }
    return count;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << ARC174D() << "\n";
    }
    return 0;
}