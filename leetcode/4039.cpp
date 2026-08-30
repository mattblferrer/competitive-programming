class Solution {
public:
    using ll = long long;
    ll power(ll a, ll p, ll m) {
        ll ans = 1;
        while (p > 0) {
            if (p & 1) ans = (ans * a) % m;
            a = (a * a) % m;
            p /= 2;
        }
        return ans;
    }

    int sumDecoded(vector<long long> &nums) {
        ll MOD = 1'000'000'007, n = nums.size();
        ll ans = 0;
        for (ll i = 0; i < n; i++) {
            ll width = nums[i] % 10;
            ll di = nums[i] / 10;
            string nstr = to_string(di);
            ll xi = stoll(nstr.substr(0, width));
            ll yi = stoll(nstr.substr(width, nstr.size() - width));
            ans = (ans + power(xi, yi, MOD)) % MOD;
            cout << xi << " " << yi << "\n";
        }
        return ans;
    }
};