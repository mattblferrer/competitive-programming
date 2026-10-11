#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    string t1, t2;
    getline(cin, t1);
    getline(cin, t2);
    if (t1 == t2) {
        cout << "7 days\n";
        return;
    }
    string w_str1 = t1.substr(0, 3), w_str2 = t2.substr(0, 3);  // weekday string 
    int h1 = stoi(t1.substr(4, 2)), h2 = stoi(t2.substr(4, 2));  // hours
    int m1 = stoi(t1.substr(7, 2)), m2 = stoi(t2.substr(7, 2));  // mins

    vector<string> days = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    int w1, w2;  // weekday number
    for (int i = 0; i < 7; i++) {
        if (w_str1 == days[i]) w1 = i;
        if (w_str2 == days[i]) w2 = i;
    }

    int total1 = w1 * 24 * 60 + h1 * 60 + m1, total2 = w2 * 24 * 60 + h2 * 60 + m2;
    if (total1 > total2) total2 += 7 * 24 * 60;  // offset by one week

    // calculate number of days, hrs, and mins
    int diff = total2 - total1;
    vector<int> output(3);
    output[2] = diff % 60;
    diff /= 60;
    output[1] = diff % 24;
    diff /= 24;
    output[0] = diff;

    // process, print output
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (output[i] != 0) count++;
    }
    string ans = "";
    int processed = 0;
    for (int i = 0; i < 3; i++) {
        if (output[i] != 0) {
            ans += to_string(output[i]) + ' ';
            if (i == 0) ans += "day";
            else if (i == 1) ans += "hour";
            else if (i == 2) ans += "minute";
            if (output[i] > 1) ans += 's';
            processed++;
        }
        if ((processed == 1) && (count == 2)) ans += " and ";
        else if ((processed < 3) && (count == 3)) ans += ", ";
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}