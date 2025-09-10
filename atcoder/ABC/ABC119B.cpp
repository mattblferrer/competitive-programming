#include <bits/stdc++.h>

double ABC119B() {
    int n;
    std::cin >> n;
    double x_i, total = 0;
    std::string u_i;
    for (int i = 0; i < n; i++) {
        std::cin >> x_i >> u_i;
        if (u_i == "JPY") total += x_i;
        else total += x_i * 380000;
    }
    return total;
}

int main() {
    std::cout << ABC119B();
    return 0;
}