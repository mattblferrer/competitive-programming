#include <iostream>
#include <set>
#include <string>

std::string ABC109B() {
    std::set<std::string> seen;
    int n;
    std::cin >> n;
    std::string prev, curr;
    std::cin >> prev;
    seen.insert(prev);
    
    for (int i = 0; i < n - 1; i++) {
        std::cin >> curr;
        if (seen.count(curr) > 0) {
            return "No";
        }
        if (prev.back() != curr.front()) {
            return "No";
        }
        prev = curr;
        seen.insert(curr);
    }
    return "Yes";
}

int main() {
    std::cout << ABC109B();
    return 0;
}