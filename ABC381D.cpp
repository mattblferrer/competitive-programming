#include <iostream>
#include <map>

int ABC381D() {
    int n;
    std::cin >> n;
    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int max_l = 0;
    for (int start = 1; start <= 2; start++) {
        std::map<int, int> seen;
        int left = start;
        
        for (int i = start; i < n; i += 2) {
            if (a[i] == a[i - 1]) {
                if (seen.count(a[i])) {
                    left = std::max(left, seen[a[i]] + 2);
                }
                seen[a[i]] = i;
                max_l = std::max(max_l, i - left + 2);
            }
            else {
                seen.clear();
                left = i + 2;
            }
        }
    }
    
    return max_l;
}

int main() { 
    std::cout << ABC381D();
    return 0;
}