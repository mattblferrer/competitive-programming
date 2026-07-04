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

// T: O(1) or O(log(n)), M: O(1)
template<int MOD>
struct ModInt {
    // T: O(n^(1/2))
    static constexpr bool isPrime() {
        if (MOD <= 1) { return false; }
        if (MOD == 2 || MOD == 3) { return true; }
        if (MOD % 2 == 0 || MOD % 3 == 0) { return false; }
        for (lng i = 5; i * i <= MOD; i += 6) {
            if (MOD % i == 0 || MOD % (i + 2) == 0) { return false; }
        }
        return true;
    }
    static constexpr bool is_prime = ModInt::isPrime();
    int n;
    template<typename T = int>
        requires std::is_integral_v<T> || std::is_same_v<T, lll> ||
    std::is_same_v<T, ulll>
        constexpr ModInt(T N = 0) {
        if constexpr (std::is_signed_v<T> || std::is_same_v<T, lll>) {
            n = N % MOD; n += (n < 0) * MOD;
        }
        else { n = N % MOD; }
    }
    explicit constexpr operator int() const { return n; }
    static constexpr ModInt init(int N) {
        ModInt res; res.n = N; return
            res;
    }
    template<typename T>
        requires std::is_integral_v<T> || std::is_same_v<T, lll> ||
    std::is_same_v<T, ulll>
        constexpr ModInt &operator=(T N) {
        if constexpr (std::is_signed_v<T> || std::is_same_v<T, lll>) {
            n = N % MOD; n += (n < 0) * MOD;
        }
        else { n = N % MOD; }
        return *this;
    }
    constexpr ModInt &operator++() {
        n++; n -= (n == MOD) * MOD; return
            *this;
    }
    constexpr ModInt &operator--() {
        n += (n == 0) * MOD; n--; return
            *this;
    }
    constexpr ModInt operator++(int) {
        ModInt res = *this; ++*this;
        return res;
    }
    constexpr ModInt operator--(int) {
        ModInt res = *this; --*this;
        return res;
    }
    constexpr ModInt &operator+=(ModInt o) {
        n += o.n; n -= (n >= MOD)
            * MOD; return *this;
    }
    constexpr ModInt &operator-=(ModInt o) {
        n -= o.n; n += (n < 0) *
            MOD; return *this;
    }
    constexpr ModInt &operator*=(ModInt o) {
        n = lng(n) * o.n % MOD;
        return *this;
    }
    constexpr ModInt &operator/=(ModInt o) { return *this *= inv(o); }
    constexpr ModInt operator+() const { return *this; }
    constexpr ModInt operator-() const {
        return init((n != 0) * (MOD -
            n));
    }
    friend constexpr ModInt operator+(ModInt a, ModInt b) {
        a += b;
        return a;
    }
    friend constexpr ModInt operator-(ModInt a, ModInt b) {
        a -= b;
        return a;
    }
    friend constexpr ModInt operator*(ModInt a, ModInt b) {
        a *= b;
        return a;
    }
    friend constexpr ModInt operator/(ModInt a, ModInt b) {
        a /= b;
        return a;
    }
    // T: O(log(n))
    friend constexpr ModInt inv(ModInt a) {
        assert(a != 0);
        if constexpr (is_prime) { return pow(a, MOD - 2); }
        int n = a.n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            int q = n / b;
            n = std::exchange(b, n - q * b);
            x = std::exchange(y, x - q * y);
        }
        return init(x + (x < 0) * MOD);
    }
    // T: O(log(n))
    friend constexpr ModInt pow(ModInt a, lng b) {
        ulng ub = b < 0 ? -ulng(b) : ulng(b);
        if (b < 0) { a = inv(a); }
        ModInt res = 1;
        for (; ub > 0; ub >>= 1, a *= a) { if (ub & 1) { res *= a; } }
        return res;
    }
    // T: O(log(n))
    friend constexpr ModInt sqrt(ModInt a) {
        assert(is_prime);
        if (a == 0 || MOD == 2) { return a; }
        if (pow(a, (MOD - 1) / 2) != 1) { return init(-1); }
        ModInt b = 1;
        while (pow(b * b - a, (MOD - 1) / 2) == 1) { b++; }
        struct Node {
            ModInt x, y, w;
            constexpr Node(ModInt X = 0, ModInt Y = 0, ModInt W = 0):
                x(X), y(Y), w(W) {
            }
            constexpr Node operator*(const Node &o) const {
                return Node(x * o.x + y * o.y * w, x * o.y + y * o.x,
                    w);
            }
        };
        Node res(1, 0, b * b - a), cur(b, 1, b * b - a);
        for (int p = (MOD + 1) / 2; p > 0; p >>= 1, cur = cur * cur) {
            if (p & 1) { res = res * cur; }
        }
        return init(min(res.x.n, MOD - res.x.n));
    }
    explicit constexpr operator bool() const { return n != 0; }
    constexpr bool operator!() const { return n == 0; }
    friend constexpr auto operator<=>(const ModInt &a, const ModInt &b)
        = default;
    friend istream &operator>>(istream &is, ModInt &a) {
        lng b; is >>
            b; a = ModInt(b); return is;
    }
    friend ostream &operator<<(ostream &os, ModInt a) {
        return os <<
            a.n;
    }
};
using mint1 = ModInt<1'000'000'007>;
using mint2 = ModInt<1'000'000'009>;

void solve(int t) {
    string s;
    cin >> s;
    int n = s.size();

    int ans = INF32;
    for (int l = 1; l <= n; l++) {
        mint1 x1 = 31, X1 = 1, hash1 = 0;
        mint2 x2 = 29, X2 = 1, hash2 = 0;
        for (int i = l - 1; i >= 0; i--) {
            hash1 += (s[i] - 'a' + 1) * X1; X1 *= x1;
            hash2 += (s[i] - 'a' + 1) * X2; X2 *= x2;
        }
        X1 /= x1; X2 /= x2;
        map<pair<int, int>, vector<int>> M;
        M[{hash1.n, hash2.n}].pb(0);
        for (int i = l; i < n; i++) {
            hash1 -= (s[i - l] - 'a' + 1) * X1;
            hash1 *= x1;
            hash1 += s[i] - 'a' + 1;
            hash2 -= (s[i - l] - 'a' + 1) * X2;
            hash2 *= x2;
            hash2 += s[i] - 'a' + 1;
            // debug(i, s[i]);
            M[{hash1.n, hash2.n}].pb(i - l + 1);
        }

        // debug(M);

        int mx_cnt = 0;
        for (auto &[sh, I] : M) {
            int cnt = 0, prv = -INF32;
            for (int i : I) {
                if (i - prv >= l) {
                    cnt++;
                    prv = i;
                }
            }
            chmax(mx_cnt, cnt);
        }

        // debug(l, mx_cnt, n - mx_cnt * (l - 1) + l);

        chmin(ans, n - mx_cnt * (l - 1) + l);
    }

    cout << ans << endl;

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