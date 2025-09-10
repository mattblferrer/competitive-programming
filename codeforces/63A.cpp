#include <iostream>
#include <string>
#include <vector>

void problem63A() {
    int n;
    std::cin >> n;
    std::string name, status, c;
    std::vector<std::string> r;
    std::vector<std::string> wc;
    std::vector<std::string> m;

    for (int i = 0; i < n; i++) {
        std::cin >> name >> status;
        if (status == "rat") {
            r.push_back(name);
        }
        else if (status == "woman" || status == "child") {
            wc.push_back(name);
        }
        else if (status == "man") {
            m.push_back(name);
        }
        else {
            c = name;
        }
    }
    for (const auto& n: r) {
        std::cout << n << "\n";
    }
    for (const auto& n: wc) {
        std::cout << n << "\n";
    }
    for (const auto& n: m) { 
        std::cout << n << "\n";
    }
    std::cout << c;
}

int main() {
    problem63A();
    return 0;
}