#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string s;
    cin >> n;
    getline(cin, s);
    vector<string> names(n);
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        names[i] = s;
    }
    vector<pair<string, string>> names_sort(n);
    for (int i = 0; i < n; i++) {
        string st = "";
        bool cap = false;
        for (char c: names[i]) {
            if (c >= 'A' && c <= 'Z') cap = true;
            if (cap) st += c;
        }
        names_sort[i] = {st, names[i]};
    }
    sort(names_sort.begin(), names_sort.end());
    for (int i = 0; i < n; i++) {
        cout << names_sort[i].second << "\n";
    }

    return 0;
}