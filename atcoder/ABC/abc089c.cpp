#include <iostream>
#include <string>

long long ABC089C() {
    long long n;
    long long counts[5] = {0, 0, 0, 0, 0};
    std::string s_i;
    long long c = 0;  // number of combinations
    
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        if (s_i[0] == 'M') {
            counts[0]++;
        }
        else if (s_i[0] == 'A') {
            counts[1]++;
        }
        else if (s_i[0] == 'R') {
            counts[2]++;
        }
        else if (s_i[0] == 'C') {
            counts[3]++;
        }
        else if (s_i[0] == 'H') {
            counts[4]++;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = j + 1; k < 5; k++) {
                c += counts[i] * counts[j] * counts[k];
            }
        }
    }
    return c;
}

int main() {  
    std::cout << ABC089C();
    return 0;
}