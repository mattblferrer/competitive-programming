#include <iostream>

int ABC080C() {
    int n;
    std::cin >> n;
    int** f = new int*[n];
    int** p = new int*[n];
    for (int i = 0; i < n; i++) {
        f[i] = new int[10];
        for (int j = 0; j < 10; j++) {
            std::cin >> f[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        p[i] = new int[11];
        for (int j = 0; j < 11; j++) {
            std::cin >> p[i][j];
        }
    }
    long long max_p = -999999999999;
    for (int i = 1; i < 1024; i++) {  // all possibilities 2^10 except 0
        long long curr_p = 0;
        for (int j = 0; j < n; j++) {
            int open = 0;
            for (int k = 0; k < 10; k++) {
                if (((i >> k) & 1) && f[j][k]) {  // check if both shops open
                    open++;
                }
            }
            curr_p += p[j][open];
        }
        max_p = std::max(max_p, curr_p);
    }
    return max_p;   
}

int main() {
    std::cout << ABC080C();
    return 0;
}