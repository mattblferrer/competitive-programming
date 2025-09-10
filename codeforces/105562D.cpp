#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    long long party_count;
    cin >> party_count;
    vector<long long> party_descending(party_count);
    long long party_sum = 0;
    long long party_max = 0;
    for (int i = 0; i < party_count; i++)
    {
        cin >> party_descending[i];
        party_sum += party_descending[i];
        party_max = max(party_max, party_descending[i]);
    }
    sort(party_descending.begin(), party_descending.end());
    reverse(party_descending.begin(), party_descending.end());
    long long super_sum = party_sum + party_max - 1;
    int majority = party_sum / 2 + 1;
    vector<vector<long long>> dp(party_count, vector<long long>(super_sum, 0));
    dp[0][0] = 1;
    for (int i = 0; i < party_count; i++)
    {
        long long cur_number = party_descending[i];
        dp[i][cur_number]++;
        for (int j = 0; j < super_sum; j++)
        {
            if (i == 0) break;
            dp[i][j] = dp[i - 1][j];
            if (j - cur_number >= 0) dp[i][j] += dp[i - 1][j - cur_number];
        }
    }

    long long total_count = 0;
    for (int i = 1; i < party_count; i++)
    {
        long long cur_number = party_descending[i];
        for (int j = majority - cur_number; j < majority; j++)
        {
            total_count += dp[i - 1][j];
        }
    }

    total_count += (party_descending[0] >= majority) ? 1 : 0;
    cout << total_count;
}