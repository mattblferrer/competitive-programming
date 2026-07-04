#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi    first
#define se    second
#define pb    push_back
using uint = uint32_t;
using lng = int64_t;    using ulng = uint64_t;
using lll = __int128_t; using ulll = __uint128_t;
template<typename T>
using indexed_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int INF32 = 0x3f3f3f3f;
constexpr lng INF64 = 0x3f3f3f3f3f3f3f3f;

template<typename T>
constexpr inline bool chmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T>
constexpr inline bool chmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

#ifdef LOCAL
namespace Debug {
    using std::to_string;
    string to_string(bool x) { return x ? "true" : "false"; }
    string to_string(char x) { return string({'\'', x, '\''}); }
    string to_string(lll x) {
        if (x == 0) { return "0"; }
        string s; bool is_neg = x < 0;
        ulll ux = is_neg ? -ulll(x) : ulll(x);
        while (ux > 0) { s += char('0' + ux % 10); ux /= 10; }
        if (is_neg) { s += '-'; }
        std::reverse(s.begin(), s.end());
        return s;
    }
    string to_string(ulll x) {
        if (x == 0) { return "0"; }
        string s;
        while (x > 0) { s += char('0' + x % 10); x /= 10; }
        std::reverse(s.begin(), s.end());
        return s;
    }
    string to_string(std::string_view x) {
        string res; res.reserve(x.size() + 2);
        res += '"'; res += x; res += '"';
        return res;
    }
    string to_string(const char *x) {
        return
            to_string(std::string_view(x));
    }
    string to_string(const string &x) {
        return
            to_string(std::string_view(x));
    }
    template<size_t N>
    string to_string(const bitset<N> &x) { return x.to_string(); }
    template<typename T>
        requires std::is_aggregate_v<T> && (!std::ranges::range<T>)
    && (!requires (ostream &os, const T &x) { os << x; })
        string to_string(const T &x);
    template<typename T>
        requires requires { std::tuple_size<T>::value; } &&
    (!std::ranges::range<T>)
        string to_string(const T &x);
    template<std::ranges::range T>
        requires (!std::is_convertible_v<T, std::string_view>)
    string to_string(const T &x);
    template<typename T, typename C>
    string to_string(const queue<T, C> &x);
    template<typename T, typename C>
    string to_string(const stack<T, C> &x);
    template<typename T, typename C, typename Comp>
    string to_string(const priority_queue<T, C, Comp> &x);
    template<typename T>
        requires (!std::ranges::range<T>) && requires (ostream &os, const T
    &x) {
        os << x;
    }
    string to_string(const T &x) {
        std::stringstream ss; ss << x;
        return ss.str();
    }
    // optional
    struct Any { template<typename T> operator T() const; };
    template<typename T>
        requires std::is_aggregate_v<T> && (!std::ranges::range<T>)
    && (!requires (ostream &os, const T &x) { os << x; })
        string to_string(const T &x) {
        if constexpr (requires { T{Any{}, Any{}, Any{}, Any{}, Any{},
        Any{}, Any{}, Any{}}; }) {
            auto &[a, b, c, d, e, f, g, h] = x; return
                to_string(std::tie(a, b, c, d, e, f, g, h));
        }
        else if constexpr (requires { T{Any{}, Any{}, Any{}, Any{},
        Any{}, Any{}, Any{}}; }) {
            auto &[a, b, c, d, e, f, g] = x; return
                to_string(std::tie(a, b, c, d, e, f, g));
        }
        else if constexpr (requires { T{Any{}, Any{}, Any{}, Any{},
        Any{}, Any{}}; }) {
            auto &[a, b, c, d, e, f] = x; return to_string(std::tie(a,
                b, c, d, e, f));
        }
        else if constexpr (requires { T{Any{}, Any{}, Any{}, Any{},
        Any{}}; }) {
            auto &[a, b, c, d, e] = x; return to_string(std::tie(a, b,
                c, d, e));
        }
        else if constexpr (requires { T{Any{}, Any{}, Any{}, Any{}}; })
        {
            auto &[a, b, c, d] = x; return to_string(std::tie(a, b, c,
                d));
        }
        else if constexpr (requires { T{Any{}, Any{}, Any{}}; }) {
            auto &[a, b, c] = x; return to_string(std::tie(a, b, c));
        }
        else if constexpr (requires { T{Any{}, Any{}}; }) {
            auto &[a, b] = x; return to_string(std::tie(a, b));
        }
        else if constexpr (requires { T{Any{}}; }) {
            auto &[a] = x; return to_string(std::tie(a));
        }
        else { return "{}"; }
    }
    template<typename T>
        requires requires { std::tuple_size<T>::value; } &&
    (!std::ranges::range<T>)
        string to_string(const T &x) {
        string res = "(";
        std::apply([&](const auto &...args) {
            int i = 0; ((res += (i++ ? ", " : ""), res +=
                to_string(args)), ...);}, x);
        return res + ")";
    }
    template<std::ranges::range T>
        requires (!std::is_convertible_v<T, std::string_view>)
    string to_string(const T &x) {
        int i = 0; string res = "{";
        for (auto &&y : x) {
            if (i++ > 0) { res += ", "; }
            res += to_string(y);
        }
        res += "}";
        return res;
    }
    template<typename T, typename C>
    string to_string(const queue<T, C> &x) {
        struct Accessor: queue<T, C> {
            static const C &get(const queue<T, C> &q) {
                return
                    q.* & Accessor::c;
            }
        };
        return to_string(Accessor::get(x));
    }
    template<typename T, typename C>
    string to_string(const stack<T, C> &x) {
        struct Accessor: stack<T, C> {
            static const C &get(const stack<T, C> &q) {
                return
                    q.* & Accessor::c;
            }
        };
        return to_string(Accessor::get(x));
    }
    template<typename T, typename C, typename Comp>
    string to_string(const priority_queue<T, C, Comp> &x) {
        struct Accessor: priority_queue<T, C, Comp> {
            static const C &get(const priority_queue<T, C, Comp> &q) {
                return q.* & Accessor::c;
            }
        };
        return to_string(Accessor::get(x));
    }
    int dep = 0;
    std::string_view indent() {
        static constexpr auto spaces = []() { array<char, 128> v{};
        v.fill(' '); return v; }();
        return std::string_view(spaces.data(), min<int>(2 * dep,
            spaces.size()));
    }
    template<std::ranges::range R, typename ...Args>
    auto slice(R &&ran, int l, int r, Args ...args) {
        auto v = std::forward<R>(ran) | std::views::drop(l) |
            std::views::take(r - l + 1);
        if constexpr (sizeof...(args) == 0) { return v; }
        else {
            return v | std::views::transform([=](auto &&cur) {
                return slice(cur, args...); });
        }
    }
    template<typename ...Args>
    void debugO(const Args &...args) {
        ((cerr << ' ' <<
            to_string(args)), ...); cerr << '\n';
    }
    struct Tracer {
        string v;
        Tracer(string x): v(std::move(x)) {
            cerr << indent() << ">> "
                << v << '\n'; dep++;
        }
        ~Tracer() { dep--; cerr << indent() << "<< " << v << '\n'; }
    };
}
#define debug(...) cerr << Debug::indent() << "\033[1;31m[L" << __LINE__ << "] [" << #__VA_ARGS__ << "]:\033[0m", Debug::debugO(__VA_ARGS__)
#define TRACE_CNCAT(a, b) a##b
#define TRACE_GUARD(a, b) TRACE_CNCAT(a, b)
#define trace(x) Debug::Tracer TRACE_GUARD(_traceGuard, __LINE__)(x)
#else
#define debug(...) void(0)
#define trace(x) void(0)
#endif

void solve(int t) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].fi;
        A[i].se = i;
    }
    vector<lng> B(m);
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    sort(A.begin(), A.end(), greater<pair<int, int>>());

    vector<lng> sums(m);
    vector<vector<int>> ans(m);
    for (int i = 0; i < n; i++) {
        int j_mn = 0;
        for (int j = 1; j < m; j++) {
            if ((sums[j] + A[i].fi) * B[j_mn] < (sums[j_mn] + A[i].fi) * B[j]) {
                j_mn = j;
            }
        }
        sums[j_mn] += A[i].fi;
        ans[j_mn].pb(A[i].se + 1);
    }

    for (auto &v : ans) {
        cout << v.size() << ' ';
        for (int x : v) {
            cout << x << ' ';
        }
        cout << endl;
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve(i);
    }
}