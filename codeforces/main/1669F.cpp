#include <iostream>

long long problem1669F() {
    long long n;
    std::cin >> n;
    long long* w = new long long[n];
    int left = 0; 
    int right = n - 1;
    long long lc = 0;
    long long rc = 0;
    long long best = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    
    while (left <= right) {
        if (lc < rc) {
            lc += w[left];
            left++;
        }
        else {
            rc += w[right];
            right--;
        }
        if (lc == rc) {
            best = left + (n - 1 - right);
        }
    }

    return best;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1669F() << "\n";	
    }
   

    return 0;
}