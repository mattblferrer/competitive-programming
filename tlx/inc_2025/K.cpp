#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string S; cin >> S;

    map<char,int> cnt;
    vector<pair<string,int>> even, odd;

    for (char c : S) {
        cnt[c]++;
    }

    for (auto it = cnt.begin(); it != cnt.end(); it++) {
        string c = "";
        c += it->first;
        int freq = it->second;
        if (freq % 2 == 0) {
            even.push_back({c, freq});
        } else {
            odd.push_back({c, freq});
        }
    }

    int N = max(1, (int)odd.size());
    cout << N << endl;
    string m = "";
    if (odd.size() > 0) {
        m = "";
        for (int i = 0; i < odd[0].second; i++) {
            m += odd[0].first;
        }
    }
    string s = "";
    for (int i = 0; i < even.size(); i++) {
        auto [c, freq] = even[i];
        for (int j = 0; j < freq/2; j++) {
            s += c;
        }
    }
    string e = s; 
    reverse(e.begin(), e.end());
    cout << s << m << e << endl;
    for (int i = 1; i < N; i++) {
        auto [c, freq] = odd[i];
        string t = "";
        for (int j = 0; j < freq; j++) {
            t += c;
        }
        cout << t << endl;
    }

    


    return 0;
}