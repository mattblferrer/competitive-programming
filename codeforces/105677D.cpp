#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

struct item
{
    ll val;
    ll idx;
}; 

void find_nearest_larger(vector<ll>& results, vector<ll>& input)
{
    int n = results.size();
    deque<item> container;
    for (int i = n - 1; i >= 0; i--)
    {
        ll cur = input[i];
        while (cur >= container.front().val && !container.empty()) container.pop_front();
        if (!container.empty()) results[i] = container.front().idx;
        container.push_front({cur, i});
    }
}

int main(void)
{
    int n;
    cin >> n;
    vector<ll> nums_forward(n);
    vector<ll> nums_backward(n);
    ll input;
    for (int i = 0; i < n; i++)
    {
        cin >> input;
        nums_forward[i] = input;
        nums_backward[n - i - 1] = input;
    }
    vector<ll> forward_results(n, INF), backward_results(n, INF);
    find_nearest_larger(forward_results, nums_forward);
    find_nearest_larger(backward_results, nums_backward);
    ll enlightenment = 0;
    for (int i = 0; i < n; i++) 
    {
        vector<int> nearest;
        ll forward = forward_results[i];
        ll backward = backward_results[n - 1 - i];
        if (forward != INF) nearest.push_back(abs(i - forward));
        if (backward != INF) nearest.push_back(abs(i - (n - 1 - backward)));
        if (nearest.size() == 0) continue;
        enlightenment += *min_element(nearest.begin(), nearest.end());
    }
    cout << enlightenment;


}