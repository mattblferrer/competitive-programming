#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int ABC114C() {
    long long n;
    std::cin >> n;
    long long curr;
    long long valid = 0;
    std::vector<long long> unfiltered;

    for (int i = 1; i <= 9; i++) {
        long long ctr = std::pow(3, i);
        while (ctr <= 2 * std::pow(3, i)) {
            std::string base_3 = "";
            long long temp = ctr;
            int rem = 0;
            long long next = 0;

            while (temp != 0) {
                rem = temp % 3;
                temp /= 3;
                base_3 += std::to_string(rem);
            } 
            
            for (int i = 0; i < base_3.length() - 1; i++) {
                char c = base_3[i];
                if (c == '0') {
                    next = next * 10 + 3;
                }
                else if (c == '1') {
                    next = next * 10 + 5;
                }
                else {
                    next = next * 10 + 7;
                }
            }
            unfiltered.push_back(next);
            curr = next;
            ctr++;
        }
    }    
    for (const auto& k: unfiltered) {
        if (k <= n) {
            int digits[3] = {0, 0, 0};
            for (const auto& digit: std::to_string(k)) {
                if (digit == '3') {
                    digits[0] = 1;
                }
                else if (digit == '5') {
                    digits[1] = 1;
                }
                else if (digit == '7') {
                    digits[2] = 1;
                }
            }
            if (digits[0] + digits[1] + digits[2] == 3) {
                valid++;
            }
        }
    }

    return valid;
}

int main() {
    std::cout << ABC114C();
    return 0;
}