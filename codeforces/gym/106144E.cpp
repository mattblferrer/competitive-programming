// 知彼知己，百战不殆
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
template<typename T, typename C = std::less<T>>
using indexed_set = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int INF32 = 0x3f3f3f3f;
constexpr lng INF64 = 0x3f3f3f3f3f3f3f3f;

template<typename T>
constexpr bool chmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T>
constexpr bool chmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

#ifdef LOCAL
namespace Debug {
    using std::to_string;

    inline string escape(char x, char quote) {
        if (x == '\\') { return "\\\\"; }
        if (x == quote) { return string("\\") + x; }
        if (x == '\0') { return "\\0"; }
        if (x == '\a') { return "\\a"; }
        if (x == '\b') { return "\\b"; }
        if (x == '\f') { return "\\f"; }
        if (x == '\n') { return "\\n"; }
        if (x == '\r') { return "\\r"; }
        if (x == '\t') { return "\\t"; }
        if (x == '\v') { return "\\v"; }
        uint ux = static_cast<unsigned char>(x);
        if (32 <= ux && ux < 127) { return string(1, x); }
        static constexpr char hex[] = "0123456789ABCDEF";
        return string{'\\', 'x', hex[ux >> 4], hex[ux & 15]};
    }

    inline string to_string(bool x) { return x ? "true" : "false"; }
    inline string to_string(char x) { return "'" + escape(x, '\'') + "'"; }
    inline string to_string(lll x) {
        if (x == 0) { return "0"; }
        string s; bool neg = x < 0;
        ulll ux = neg ? -ulll(x) : x;
        while (ux > 0) { s += char('0' + ux % 10); ux /= 10; }
        if (neg) { s += '-'; }
        std::reverse(s.begin(), s.end());
        return s;
    }
    inline string to_string(ulll x) {
        if (x == 0) { return "0"; }
        string s;
        while (x > 0) { s += char('0' + x % 10); x /= 10; }
        std::reverse(s.begin(), s.end());
        return s;
    }
    inline string to_string(std::string_view x) {
        string res; res.reserve(x.size() + 2); res += '"';
        for (char c : x) { res += escape(c, '"'); }
        res += '"';
        return res;
    }
    inline string to_string(std::nullptr_t) { return "nullptr"; }
    inline string to_string(const char *x) { return x ? to_string(std::string_view(x)) : "nullptr"; }
    inline string to_string(char *x) { return to_string(static_cast<const char *>(x)); }
    inline string to_string(const string &x) { return to_string(std::string_view(x)); }
    template<size_t N>
    inline string to_string(const bitset<N> &x) { return x.to_string(); }

    template<typename T>
    constexpr bool isTupleLike = []() {
        if constexpr (!requires { std::tuple_size<T>::value; }) { return false; }
        else {
            return[]<size_t ...I>(std::index_sequence<I...>) {
                using std::get;
                return requires(const T & x) { (get<I>(x), ...); };
            }(std::make_index_sequence<std::tuple_size_v<T>>{});
        }}();
        template<typename T>
            requires std::is_aggregate_v<T> && (!std::is_union_v<T>) && (!std::ranges::range<T>)
        && (!isTupleLike<T>) && (!requires (ostream &os, const T &x) { os << x; })
            inline string to_string(const T &x);

        template<typename T>
            requires isTupleLike<T> && (!std::ranges::range<T>) && (!requires (ostream &os, const T &x) { os << x; })
        inline string to_string(const T &x);
        template<std::ranges::range T>
            requires (!std::is_convertible_v<T, std::string_view>)
        inline string to_string(const T &x);
        template<typename T, typename C>
        inline string to_string(const queue<T, C> &x);
        template<typename T, typename C>
        inline string to_string(const stack<T, C> &x);
        template<typename T, typename C, typename Comp>
        inline string to_string(const priority_queue<T, C, Comp> &x);
        template<typename T>
        inline string to_string(const optional<T> &x);
        template<typename ...T>
        inline string to_string(const std::variant<T...> &x);

        template<typename T>
            requires (!std::ranges::range<T>) && requires (ostream &os, const T &x) { os << x; }
        inline string to_string(const T &x) { std::ostringstream ss; ss << x; return ss.str(); }

        template<typename T>
        constexpr bool hasDebugFields = requires(const T & x) {
            requires isTupleLike<std::remove_cvref_t<decltype(debugFields(x))>>;
        };
        template<typename T>
            requires std::is_aggregate_v<T> && (!std::is_union_v<T>) && (!std::ranges::range<T>)
        && (!isTupleLike<T>) && (!requires (ostream &os, const T &x) { os << x; })
            inline string to_string(const T &x) {
            if constexpr (hasDebugFields<T>) { return to_string(debugFields(x)); }
            else if constexpr (std::is_empty_v<T>) { return "{}"; }
            else { return "{...}"; }
        }

        template<typename T>
            requires isTupleLike<T> && (!std::ranges::range<T>) && (!requires (ostream &os, const T &x) { os << x; })
        inline string to_string(const T &x) {
            string res = "(";
            [&] <size_t ...I>(std::index_sequence<I...>) {
                using std::get;
                ((res += (I ? ", " : ""), res += to_string(get<I>(x))), ...);
            }(std::make_index_sequence<std::tuple_size_v<T>>{});
            res += ')';
            return res;
        }
        template<std::ranges::range T>
            requires (!std::is_convertible_v<T, std::string_view>)
        inline string to_string(const T &x) {
            if constexpr (!std::ranges::range<const T>) {
                auto v = x;
                return to_string(std::ranges::subrange(v));
            }
            else {
                int i = 0; string res = "{";
                for (auto &&y : x) {
                    if (i++ > 0) { res += ", "; }
                    res += to_string(y);
                }
                res += "}";
                return res;
            }
        }
        template<typename T, typename C>
        inline string to_string(const queue<T, C> &x) {
            struct Accessor: queue<T, C> {
                static const C &get(const queue<T, C> &q) { return q.* & Accessor::c; }
            };
            return to_string(Accessor::get(x));
        }
        template<typename T, typename C>
        inline string to_string(const stack<T, C> &x) {
            struct Accessor: stack<T, C> {
                static const C &get(const stack<T, C> &q) { return q.* & Accessor::c; }
            };
            return to_string(Accessor::get(x));
        }
        template<typename T, typename C, typename Comp>
        inline string to_string(const priority_queue<T, C, Comp> &x) {
            struct Accessor: priority_queue<T, C, Comp> {
                static const C &get(const priority_queue<T, C, Comp> &q) { return q.* & Accessor::c; }
            };
            return to_string(Accessor::get(x));
        }
        template<typename T>
        inline string to_string(const optional<T> &x) { return x ? to_string(*x) : "nullopt"; }
        template<typename ...T>
        inline string to_string(const std::variant<T...> &x) {
            if (x.valueless_by_exception()) { return "valueless_by_exception"; }
            return std::visit([](const auto &y) { return to_string(y); }, x);
        }

        inline int dep = 0;
        inline std::string_view indent() {
            static constexpr auto spaces = []() { array<char, 128> v{}; v.fill(' '); return v; }();
            return std::string_view(spaces.data(), 2 * std::clamp(dep, 0, int(spaces.size() / 2)));
        }
        template<std::ranges::range R, typename ...Args>
        auto slice(R &&ran, int l, int r, Args ...args) {
            assert(0 <= l && l <= lng(r) + 1);
            auto v = std::forward<R>(ran) | std::views::drop(l) | std::views::take(lng(r) - l + 1);
            if constexpr (sizeof...(args) == 0) { return v; }
            else { return v | std::views::transform([=](auto &&cur) { return slice(cur, args...); }); }
        }

        template<typename ...Args>
        void debugO(const Args &...args) { ((cerr << ' ' << to_string(args)), ...); cerr << '\n'; }
        struct Tracer {
            Tracer(const Tracer &) = delete;
            Tracer(Tracer &&) = delete;
            Tracer &operator=(const Tracer &) = delete;
            Tracer &operator=(Tracer &&) = delete;

            string v;
            Tracer(string x): v(std::move(x)) { cerr << indent() << ">> " << v << '\n'; dep++; }
            ~Tracer() { dep--; cerr << indent() << "<< " << v << '\n'; }
        };
}

#define debug(...) cerr << Debug::indent() << "\033[1;31m[L" << __LINE__ << "] [" << #__VA_ARGS__ << "]:\033[0m", Debug::debugO(__VA_ARGS__)
#define TRACE_CNCAT(a, b) a##b
#define TRACE_GUARD(a, b) TRACE_CNCAT(a, b)
#define trace(x) Debug::Tracer TRACE_GUARD(traceGuard, __COUNTER__)(x)
#else
#define debug(...) void(0)
#define trace(x) void(0)
#endif

vector<pair<int, int>> di_dj = {{0, -1},{0, 1},{1, 0}};

void solve(int t) {
    trace(to_string(t));

    int n, m, k;
    cin >> n >> m >> k;
    vector grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector redu(n - k + 1, vector<int>(m));
    for (int j = 0; j < m; j++) {
        int cur = 0;
        for (int i = 0; i < k; i++) {
            cur += grid[i][j] == '.';
        }
        redu[0][j] = cur == k;
        for (int i = k; i < n; i++) {
            cur += grid[i][j] == '.';
            cur -= grid[i - k][j] == '.';
            redu[i - k + 1][j] = cur == k;
        }
    }

    debug(redu);

    int ans = 0;
    vector vst(n - k + 1, vector<bool>(m));
    queue<pair<int, int>> q;
    vst[0][0] = true;
    q.push({0, 0});
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (auto [di, dj] : di_dj) {
            if (i + di < 0 || i + di >= n - k + 1 || j + dj < 0 || j + dj >= m) {
                continue;
            }

            if (!redu[i + di][j + dj] || vst[i + di][j + dj]) {
                continue;
            }

            chmax(ans, i + di);
            vst[i + di][j + dj] = true;
            q.push({i + di, j + dj});
        }
    }
    ans += k;

    cout << ans << endl;

    return;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve(i);
    }

    return 0;
}