#include <cmath>
#include <iostream>
#include <string>

long long sqr_distance(int x_1, int y_1, int x_2, int y_2) {
    return std::pow(x_1 - x_2, 2) + std::pow(y_1 - y_2, 2);
}

bool is_right(int* in) {
    long long d_12 = sqr_distance(in[0], in[1], in[2], in[3]);
    long long d_23 = sqr_distance(in[2], in[3], in[4], in[5]);
    long long d_13 = sqr_distance(in[0], in[1], in[4], in[5]);
    if (d_12 == 0 || d_23 == 0 || d_13 == 0) {  // degenerate
        return false;
    }
    if ((d_12 + d_23 == d_13) || (d_12 + d_13 == d_23) || (d_23 + d_13 == d_12)) {
        return true;
    }
    return false;
}

std::string problem18A() {
    int* in = new int[6];
    bool almost = false;
    for (int i = 0; i < 6; i++) {
        std::cin >> in[i];
    }

    for (int i = 0; i < 6; i++) {
        in[i]--;
        for (int j = -1; j <= 1; j++) {
            if (is_right(in)) {
                if (j == 0) {
                    return "RIGHT";
                }
                almost = true;
            }
            in[i]++;
        }
        in[i] -= 2;
    }   
    if (almost) {
        return "ALMOST";
    }
    return "NEITHER";
}

int main() {
    std::cout << problem18A();
    return 0;
}