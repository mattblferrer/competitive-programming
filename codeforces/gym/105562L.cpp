#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, X, Y; cin >> N >> M >> X >> Y;

    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < M; i++)
        cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    auto check = [&] (int k) -> bool {
        int i = 0, j = 0;
        int count = (i < k ? Y : X);
        for (j; j < M; j++) {
            if (i >= N)
                return false;
            if (A[i] < B[j] or count - 1 < 0) {
                i++;
                count = (i < k ? Y : X);
                j--;
                continue;
            }
            count--;
        }
        return true;
    };

    if (!check(0)) {
        cout << "impossible";
        return 0;
    }

    int L = 0, R = N;

    while (L < R-1) {
        int M = (L + R) / 2;
        // cout << L << " " << R << endl;
        if (check(M)) {
            L = M;
        } else {
            R = M-1;
        }
    }
    if (check(R)) {
        cout << R;
    } else
        cout << L;
    return 0;
}