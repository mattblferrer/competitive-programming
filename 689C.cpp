#include <bits/stdc++.h>

long long problem689C() {
    long long m;
    std::cin >> m;
    long long curr_m, curr_k, left = 0, right = pow(10, 16);
    while (left < right) {
        long long mid = (left + right) / 2;
        curr_m = 0;
        for (long long k = 2; k < 500000; k++) {
            curr_k = mid / pow(k, 3);
            if (curr_k == 0) break;
            curr_m += curr_k;
        }
        if (curr_m >= m) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    curr_m = 0;
    for (long long k = 2; k < 500000; k++) {
        curr_k = right / pow(k, 3);
        if (curr_k == 0) break;
        curr_m += curr_k;
    }
    if (curr_m == m) return right;
    return -1;
}

int main() {
    std::cout << problem689C();	
    return 0;
}