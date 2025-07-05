#include <bits/stdc++.h>

double calc(double g, double n, double p) {
    double ans = 0, suff = 1;
    for (double i = 0; i < p - 1; i++) {
        suff *= (n - i) / (g + n - i - 1);
    }
    ans = (g / (g + n) * suff) * p;
    return ans;
}

double problemE() {
    double n, p;
    std::cin >> n >> p;
    int left = -1, right = n;
    
    while (right - left > 1) {
        double g = (left + right) / 2, h = g + 1;
        double g_ans = calc(g, n, p), h_ans = calc(h, n, p);
        if (g_ans >= h_ans) right = g;
        else left = g;
    }
    return calc(right, n, p);
}

int main() {
    std::cout << problemE();
    return 0;
}