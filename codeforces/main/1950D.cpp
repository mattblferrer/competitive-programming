#include <bitset>
#include <iostream>
#include <set>
#include <string>

void problem1950D() {
    const int limit = 33;  // 2^5 + 1
    int* bd = new int[limit];  // binary decimals
    std::set<int> bdp;  // binary decimal products

    for (int i = 0; i < limit; i++) {
        int binary = std::stoi(std::bitset<6>(i).to_string());
        bd[i] = binary;
        bdp.insert(binary);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < limit; j++) {
            for (const auto& k: bdp) {
                if (bd[j] * k < 100000) {
                    bdp.insert(bd[j] * k);
                }
            }
        }
    }
        
    int t, n;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> n;
        if (bdp.count(n)) {
            std::cout << "YES\n";
        }
        else {
            std::cout << "NO\n";
        }
    }
}

int main() {
    problem1950D();
    
    return 0;
}