#include <bits/stdc++.h>

bool isPalindrome(int hh, int mm) {
    std::string h_str = std::to_string(hh);
    std::string m_str = std::to_string(mm);
    if (h_str.length() == 1) h_str = '0' + h_str;
    if (m_str.length() == 1) m_str = '0' + m_str;
    std::reverse(m_str.begin(), m_str.end());
    return h_str == m_str;
}

void problem108A() {
    std::string time;
    std::cin >> time;
    int hh, mm;
    hh = stoi(time.substr(0, 2));
    mm = stoi(time.substr(3, 2));

    do  {
        mm++;
        if (mm == 60) {
            mm = 0;
            hh++;
        }
        if (hh == 24) hh = 0;
    } while (!isPalindrome(hh, mm));
    if (hh < 10) std::cout << '0' << hh << ':';
    else std::cout << hh << ':';
    if (mm < 10) std::cout << '0' << mm;
    else std::cout << mm;
}

int main() {
    problem108A();	

    return 0;
}