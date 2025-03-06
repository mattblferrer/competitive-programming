#include <algorithm>
#include <iostream>
#include <map>

long long ABC206C() {
    long long n, pairs;
    std::cin >> n;
    int* a = new int[n];
    std::map<int, int> a_map;

    for (int i = 0; i < n; i++) {  
        std::cin >> a[i];
    }
    std::sort(a, a + n);
    for (int i = 0; i < n; i++) {  
        a_map[a[i]] = i + 1;
    }

    pairs = 0;
    for (int i = 0; i < n; i++) {
        pairs += n - a_map[a[i]];
    }
    return pairs;
}   

int main() { 
    std::cout << ABC206C();
    return 0;
}