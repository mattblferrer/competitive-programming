#include <algorithm>
#include <iostream>
#include <vector>

int main() { 
    int a_1, a_2, a_3, min_a, max_a;
    std::cin >> a_1 >> a_2 >> a_3;
    std::vector<int> a = {a_1, a_2, a_3};
    min_a = *std::min_element(a.begin(), a.end());
    max_a = *std::max_element(a.begin(), a.end());

    std::cout << max_a - min_a;
    
    return 0;
}