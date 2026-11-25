// Contents
//   Point                    2D point / vector
//   dot                      dot product, O(1)
//   cross                    cross product, O(1)
//   norm                     squared length, O(1)
//   abs                      length, O(1)
//   dist                     distance between a and b, O(1)
//   angle                    angle abc at b in radians, in [0, pi], O(1)
//   rotate                   rotate a counter-clockwise by d radians about pivot p, O(1)
//   proj_line                projection of p onto the line ab, O(1)
//   proj_seg                 closest point to p on the segment ab, O(1)
//   dist_pt_line             distance from p to the line ax + by + c = 0, O(1)
//   line_inter               intersection of lines ab and cd (segments if seg), nullopt if there is none
//   circle_line_inter        intersection points of the circle (c, r) and the line ab: 0, 1 (tangent), or 2 points
//   circle_circle_inter      intersection points of circles (c1, r1) and (c2, r2): 0, 1 (tangent), or 2 points
//   polygon_area             area of a simple polygon, O(n)
//   triangle_area            area of a triangle from its side lengths (Heron), O(1)
//   cyclic_quad_area         area of a cyclic quadrilateral (opposite angles sum to 180 degrees) from its side...
//   polygon_centroid         centroid (center of mass) of a simple polygon with nonzero area, O(n)
//   convex_hull              convex hull in counter-clockwise order (monotone chain), O(n log n)
//   on_polygon               true if q is on the boundary of polygon p, O(n)
//   in_polygon               true if q is inside polygon p (for points on the boundary, use on_polygon), O(n)
//   cut_polygon              part of polygon p to the left of the directed line a -> b, O(n)
//   bary                     point with barycentric weights a, b, c in triangle ABC, O(1)
//   trilinear                point with trilinear coordinates a : b : c in triangle ABC, O(1)
//   centroid                 centroid of a triangle, O(1)
//   circumcenter             circumcenter of a non-degenerate triangle, O(1)
//   orthocenter              orthocenter of a non-degenerate triangle, O(1)
//   incenter                 incenter of a triangle, O(1)
//   inradius                 inradius of a triangle from its side lengths, O(1)
//   excenter                 excenter opposite A; cycle the arguments for the other two, O(1)
//   brocard                  first Brocard point of a triangle (CCW); swap B and C for the other one, O(1)
//   symmedian                symmedian point of a triangle, O(1)
//   convex_polygon_inter     intersection of two convex polygons as a convex polygon, O(nm + (n + m) log(n + m))
//   lattice_boundary         number of lattice points on the boundary of a polygon with integer vertices, O(n log C)
//   lattice_interior         number of lattice points strictly inside a polygon with integer vertices (Pick's...
//   min_enclosing_circle     smallest circle containing all points, returned as {center, radius}, O(n) expected
//   furthest_pair            two of the points at the largest distance (diameter, rotating calipers), n >= 1...
//   polygon_width            smallest distance between two parallel lines containing all points between them...
//   closest_pair             two of the points at the smallest distance (line sweep), n >= 2, O(n log n)
//   KDTree                   2D tree for nearest neighbor queries; the tree reorders its own copy of the points
//   Point3                   3D point / vector with arithmetic, dot, cross, and length, O(1) each
//   proj_plane               projection of p onto the plane ax + by + cz + d = 0, O(1)
//   dist_pt_plane            distance from p to the plane ax + by + cz + d = 0, O(1)
//   dist_line_3d             distance between the 3D lines AB and CD, O(1)
//   great_circle_dist        great-circle distance between two points given as latitude and longitude in degrees
//   great_circle_angle       great-circle angle in radians between two 3D vectors, O(1)
//   Point3I                  3D point with integer coordinates, for convex_hull_3d
//   Face                     triangular face of a 3D hull, for convex_hull_3d
//   convex_hull_3d           3D convex hull with integer coordinates, O(n^2)
//   in_convex                true if q is inside or on the convex polygon h (strict hull in CCW order, at least 3...
//   sort_by_angle            sorts p by polar angle around o, counter-clockwise from direction s (default angle 0); atan2 order supported
//   minkowski_sum            Minkowski sum of two convex polygons given as strict hulls in CCW order
//   half_plane_intersection  intersection of half-planes as a CCW polygon
//   polygon_union_area       area of the union of simple polygons, each in CCW order
//   delaunay_edges           Delaunay triangulation edges of integer points (they contain a Euclidean MST), O(n log n)
//   TriangleCounter          number of points strictly inside triangles of given points, O(n^2 m) build, O(1) per query

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ld PI = acosl(-1), EPS = 1e-9;

// 2D point / vector
//   +, -, * scalar, / scalar   vector arithmetic, O(1)
//   ==, <                      exact comparisons (< is by x, then y), O(1)
struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0): x(x), y(y) {}
    Point operator+(const Point &o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
    Point operator*(ld k) const { return {x * k, y * k}; }
    Point operator/(ld k) const { return {x / k, y / k}; }
    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
    bool operator<(const Point &o) const { return x != o.x ? x < o.x : y < o.y; }
};

// dot product, O(1)
ld dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

// cross product, O(1)
ld cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

// cross product of b - a and c - a; positive if a, b, c turn counter-clockwise, O(1)
ld cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

// squared length, O(1)
ld norm(Point a) { return dot(a, a); }

// length, O(1)
ld abs(Point a) { return hypotl(a.x, a.y); }

// distance between a and b, O(1)
ld dist(Point a, Point b) { return abs(a - b); }

// angle abc at b in radians, in [0, pi], O(1)
ld angle(Point a, Point b, Point c) {
    return fabsl(remainderl(atan2l((a - b).y, (a - b).x) - atan2l((c - b).y, (c - b).x), 2 * PI));
}

// rotate a counter-clockwise by d radians about pivot p, O(1)
Point rotate(Point p, Point a, ld d) {
    Point v = a - p;
    return p + Point(v.x * cosl(d) - v.y * sinl(d), v.x * sinl(d) + v.y * cosl(d));
}

// projection of p onto the line ab, O(1)
Point proj_line(Point p, Point a, Point b) { return a + (b - a) * (dot(p - a, b - a) / norm(b - a)); }

// closest point to p on the segment ab, O(1)
Point proj_seg(Point p, Point a, Point b) {
    if (a == b) return a;
    return a + (b - a) * min<ld>(1, max<ld>(0, dot(p - a, b - a) / norm(b - a)));
}

// distance from p to the line ax + by + c = 0, O(1)
ld dist_pt_line(Point p, ld a, ld b, ld c) { return fabsl(a * p.x + b * p.y + c) / hypotl(a, b); }

// distance from p to the line ab, O(1)
ld dist_pt_line(Point p, Point a, Point b) { return fabsl(cross(a, b, p)) / dist(a, b); }

// intersection of lines ab and cd (segments if seg), nullopt if there is none; collinear segments return their
// point only if they touch at exactly one point, O(1)
optional<Point> line_inter(Point a, Point b, Point c, Point d, bool seg = false) {
    Point ab = b - a, cd = d - c, ac = c - a;
    ld det = -cross(ab, cd), ds = cross(cd, ac), dt = cross(ab, ac);
    if (fabsl(det) < EPS) {
        if (seg && fabsl(ds) < EPS) {
            Point p[] = {a, b, c, d};
            sort(p, p + 4);
            if (dist(p[1], p[2]) < EPS) return p[1];
        }
        return nullopt;
    }
    ld s = ds / det, t = dt / det;
    if (seg && (min(s, t) < -EPS || max(s, t) > 1 + EPS)) return nullopt;
    return a + ab * s;
}

// intersection points of the circle (c, r) and the line ab: 0, 1 (tangent), or 2 points, O(1)
vector<Point> circle_line_inter(Point c, ld r, Point a, Point b) {
    Point p = proj_line(c, a, b);
    ld d = dist(c, p);
    if (d > r + EPS) return {};
    if (d > r - EPS) return {p};
    Point v = (b - a) * (sqrtl(r * r - d * d) / dist(a, b));
    return {p + v, p - v};
}

// intersection points of circles (c1, r1) and (c2, r2): 0, 1 (tangent), or 2 points; identical circles give none, O(1)
vector<Point> circle_circle_inter(Point c1, ld r1, Point c2, ld r2) {
    ld d = dist(c1, c2);
    if (d < EPS || d > r1 + r2 + EPS || d < fabsl(r1 - r2) - EPS) return {};
    ld a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    Point v = (c2 - c1) / d, m = c1 + v * a;
    ld h2 = r1 * r1 - a * a;
    if (h2 < EPS) return {m};
    Point n = Point(-v.y, v.x) * sqrtl(h2);
    return {m + n, m - n};
}

// area of a simple polygon, O(n)
ld polygon_area(const vector<Point> &p) {
    ld a = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++) a += cross(p[j], p[i]);
    return fabsl(a) / 2;
}

// area of a triangle from its side lengths (Heron), O(1)
ld triangle_area(ld a, ld b, ld c) {
    ld s = (a + b + c) / 2;
    return sqrtl(max<ld>(0, s * (s - a) * (s - b) * (s - c)));
}

// area of a cyclic quadrilateral (opposite angles sum to 180 degrees) from its side lengths (Brahmagupta), O(1)
ld cyclic_quad_area(ld a, ld b, ld c, ld d) {
    ld s = (a + b + c + d) / 2;
    return sqrtl(max<ld>(0, (s - a) * (s - b) * (s - c) * (s - d)));
}

// centroid (center of mass) of a simple polygon with nonzero area, O(n)
Point polygon_centroid(const vector<Point> &p) {
    Point ans;
    ld z = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++) {
        ld c = cross(p[j], p[i]);
        ans = ans + (p[j] + p[i]) * c;
        z += c;
    }
    return ans / (3 * z);
}

// convex hull in counter-clockwise order (monotone chain), O(n log n)
// strict by default; with keep_collinear, also keeps input points in the middle of hull edges
// (if all points are collinear, returns them sorted)
vector<Point> convex_hull(vector<Point> p, bool keep_collinear = false) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    ld lim = keep_collinear ? -EPS : EPS;
    vector<Point> h(2 * n);
    for (int i = 0; i < n; h[k++] = p[i++])
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    if (k == 2 * n - 1) return p;  // nothing popped: all points are collinear
    h.resize(k - 1);
    return h;
}

// true if q is on the boundary of polygon p, O(n)
bool on_polygon(Point q, const vector<Point> &p) {
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        if (dist(proj_seg(q, p[j], p[i]), q) < EPS) return true;
    return false;
}

// true if q is inside polygon p (for points on the boundary, use on_polygon), O(n)
bool in_polygon(Point q, const vector<Point> &p) {
    bool in = false;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        if ((p[i].y > q.y) != (p[j].y > q.y) && q.x < (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x)
            in = !in;
    return in;
}

// part of polygon p to the left of the directed line a -> b, O(n)
vector<Point> cut_polygon(const vector<Point> &p, Point a, Point b) {
    vector<Point> res;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++) {
        ld c1 = cross(a, b, p[j]), c2 = cross(a, b, p[i]);
        if (c1 > -EPS) res.push_back(p[j]);
        if ((c1 > EPS && c2 < -EPS) || (c1 < -EPS && c2 > EPS)) res.push_back(*line_inter(p[j], p[i], a, b));
    }
    return res;
}

// point with barycentric weights a, b, c in triangle ABC, O(1)
Point bary(Point A, Point B, Point C, ld a, ld b, ld c) { return (A * a + B * b + C * c) / (a + b + c); }

// point with trilinear coordinates a : b : c in triangle ABC, O(1)
Point trilinear(Point A, Point B, Point C, ld a, ld b, ld c) {
    return bary(A, B, C, dist(B, C) * a, dist(C, A) * b, dist(A, B) * c);
}

// centroid of a triangle, O(1)
Point centroid(Point A, Point B, Point C) { return bary(A, B, C, 1, 1, 1); }

// circumcenter of a non-degenerate triangle, O(1)
Point circumcenter(Point A, Point B, Point C) {
    ld a = norm(B - C), b = norm(C - A), c = norm(A - B);
    return bary(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}

// orthocenter of a non-degenerate triangle, O(1)
Point orthocenter(Point A, Point B, Point C) { return A + B + C - circumcenter(A, B, C) * 2; }

// incenter of a triangle, O(1)
Point incenter(Point A, Point B, Point C) { return bary(A, B, C, dist(B, C), dist(C, A), dist(A, B)); }

// inradius of a triangle from its side lengths, O(1)
ld inradius(ld a, ld b, ld c) { return triangle_area(a, b, c) / ((a + b + c) / 2); }

// excenter opposite A; cycle the arguments for the other two, O(1)
Point excenter(Point A, Point B, Point C) {
    return bary(A, B, C, -dist(B, C), dist(C, A), dist(A, B));
}

// first Brocard point of a triangle (CCW); swap B and C for the other one, O(1)
Point brocard(Point A, Point B, Point C) {
    ld a = dist(B, C), b = dist(C, A), c = dist(A, B);
    return bary(A, B, C, c / b * a, a / c * b, b / a * c);
}

// symmedian point of a triangle, O(1)
Point symmedian(Point A, Point B, Point C) { return bary(A, B, C, norm(B - C), norm(C - A), norm(A - B)); }

// intersection of two convex polygons as a convex polygon, O(nm + (n + m) log(n + m))
vector<Point> convex_polygon_inter(const vector<Point> &a, const vector<Point> &b) {
    vector<Point> pts;
    for (Point p : a) if (in_polygon(p, b) || on_polygon(p, b)) pts.push_back(p);
    for (Point p : b) if (in_polygon(p, a) || on_polygon(p, a)) pts.push_back(p);
    for (int i = 0, n = a.size(), I = n - 1; i < n; I = i++) {
        for (int j = 0, m = b.size(), J = m - 1; j < m; J = j++) {
            auto p = line_inter(a[i], a[I], b[j], b[J], true);
            if (p) pts.push_back(*p);
        }
    }
    return convex_hull(pts);
}

// number of lattice points on the boundary of a polygon with integer vertices, O(n log C)
ll lattice_boundary(const vector<pll> &p) {
    ll ans = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        ans += gcd(llabs(p[i].first - p[j].first), llabs(p[i].second - p[j].second));
    return ans;
}

// number of lattice points strictly inside a polygon with integer vertices (Pick's theorem), O(n log C)
ll lattice_interior(const vector<pll> &p) {
    ll area2 = 0;
    for (int i = 0, n = p.size(), j = n - 1; i < n; j = i++)
        area2 += p[j].first * p[i].second - p[i].first * p[j].second;
    return (llabs(area2) - lattice_boundary(p) + 2) / 2;
}

// smallest circle containing all points, returned as {center, radius}, O(n) expected
pair<Point, ld> min_enclosing_circle(vector<Point> p) {
    shuffle(p.begin(), p.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));
    Point c;
    ld r = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (dist(c, p[i]) <= r + EPS) continue;
        c = p[i];
        r = 0;
        for (int j = 0; j < i; j++) {
            if (dist(c, p[j]) <= r + EPS) continue;
            c = (p[i] + p[j]) / 2;
            r = dist(c, p[i]);
            for (int k = 0; k < j; k++) {
                if (dist(c, p[k]) <= r + EPS) continue;
                c = circumcenter(p[i], p[j], p[k]);
                r = dist(c, p[i]);
            }
        }
    }
    return {c, r};
}

// two of the points at the largest distance (diameter, rotating calipers), n >= 1, O(n log n)
// compares squared distances, so exact for integer coordinates up to ~1e9
pair<Point, Point> furthest_pair(const vector<Point> &pts) {
    vector<Point> h = convex_hull(pts);
    int k = h.size();
    if (k < 3 || fabsl(cross(h[0], h[1], h[2])) < EPS) return {h[0], h.back()};  // collinear: hull is sorted
    pair<Point, Point> res = {h[0], h[1]};
    for (int i = 0, j = 1; i < k; i++) {
        int ni = (i + 1) % k;
        while (cross(h[i], h[ni], h[(j + 1) % k]) > cross(h[i], h[ni], h[j])) j = (j + 1) % k;
        for (Point q : {h[i], h[ni]}) if (norm(q - h[j]) > norm(res.first - res.second)) res = {q, h[j]};
    }
    return res;
}

// smallest distance between two parallel lines containing all points between them (rotating calipers), O(n log n)
ld polygon_width(const vector<Point> &pts) {
    vector<Point> h = convex_hull(pts);
    int k = h.size();
    if (k <= 2) return 0;
    ld d = HUGE_VALL;
    for (int i = 0, j = 1; i < k; i++) {
        int ni = (i + 1) % k;
        while (cross(h[i], h[ni], h[(j + 1) % k]) > cross(h[i], h[ni], h[j])) j = (j + 1) % k;
        d = min(d, dist_pt_line(h[j], h[i], h[ni]));
    }
    return d;
}

// two of the points at the smallest distance (line sweep), n >= 2, O(n log n)
// compares squared distances, so exact for integer coordinates up to ~1e9
pair<Point, Point> closest_pair(vector<Point> p) {
    sort(p.begin(), p.end(), [](const Point &a, const Point &b) { return a.y < b.y; });
    set<Point> box;
    pair<Point, Point> res = {p[0], p[1]};
    ld best = HUGE_VALL;  // squared
    for (int l = 0, i = 0; i < (int)p.size(); i++) {
        ld d = sqrtl(best);
        while (p[i].y - p[l].y > d) box.erase(p[l++]);
        for (auto it = box.lower_bound(Point(p[i].x - d, -HUGE_VALL)); it != box.end() && it->x <= p[i].x + d; it++)
            if (norm(p[i] - *it) < best) best = norm(p[i] - *it), res = {*it, p[i]};
        box.insert(p[i]);
    }
    return res;
}

// 2D tree for nearest neighbor queries; the tree reorders its own copy of the points
//   KDTree(p)          build from p, O(n log n)
//   knn(x, y, k, r)    the k nearest points to (x, y) within radius r (r < 0 means any), nearest first; O(k log k log n) typical
struct KDTree {
    vector<Point> p;
    priority_queue<pair<ld, int>> pq;
    int k = 1;
    ld qx = 0, qy = 0, prune = 0;

    KDTree(const vector<Point> &pts): p(pts) { build(0, p.size(), false); }

    void build(int l, int r, bool by_x) {
        if (l >= r) return;
        int m = (l + r) / 2;
        nth_element(p.begin() + l, p.begin() + m, p.begin() + r, [&](const Point &a, const Point &b) {
            return by_x ? a.x < b.x : a.y < b.y;
        });
        build(l, m, !by_x);
        build(m + 1, r, !by_x);
    }

    void dfs(int l, int r, bool by_x) {
        if (l >= r) return;
        int m = (l + r) / 2;
        ld dx = qx - p[m].x, dy = qy - p[m].y, delta = by_x ? dx : dy, d = dx * dx + dy * dy;
        if (d <= prune && ((int)pq.size() < k || d < pq.top().first)) {
            pq.push({d, m});
            if ((int)pq.size() > k) pq.pop();
        }
        int nl = l, nr = m, fl = m + 1, fr = r;
        if (delta > 0) swap(nl, fl), swap(nr, fr);
        dfs(nl, nr, !by_x);
        d = delta * delta;
        if (d <= prune && ((int)pq.size() < k || d < pq.top().first)) dfs(fl, fr, !by_x);
    }

    vector<Point> knn(ld x, ld y, int k_ = 1, ld r = -1) {
        qx = x;
        qy = y;
        k = k_;
        prune = r < 0 ? HUGE_VALL : r * r;
        dfs(0, p.size(), false);
        vector<Point> v;
        while (!pq.empty()) {
            v.push_back(p[pq.top().second]);
            pq.pop();
        }
        reverse(v.begin(), v.end());
        return v;
    }
};

// 3D point / vector with arithmetic, dot, cross, and length, O(1) each
struct Point3 {
    ld x, y, z;
    Point3(ld x = 0, ld y = 0, ld z = 0): x(x), y(y), z(z) {}
    Point3 operator+(const Point3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
    Point3 operator-(const Point3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
    Point3 operator*(ld k) const { return {x * k, y * k, z * k}; }
    ld dot(const Point3 &o) const { return x * o.x + y * o.y + z * o.z; }
    Point3 cross(const Point3 &o) const { return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x}; }
    ld abs() const { return sqrtl(dot(*this)); }
};

// projection of p onto the line ab, O(1)
Point3 proj_line(Point3 p, Point3 a, Point3 b) {
    Point3 d = b - a;
    return a + d * ((p - a).dot(d) / d.dot(d));
}

// projection of p onto the plane ax + by + cz + d = 0, O(1)
Point3 proj_plane(Point3 p, ld a, ld b, ld c, ld d) {
    Point3 n(a, b, c);
    return p - n * ((n.dot(p) + d) / n.dot(n));
}

// distance from p to the plane ax + by + cz + d = 0, O(1)
ld dist_pt_plane(Point3 p, ld a, ld b, ld c, ld d) {
    return fabsl(a * p.x + b * p.y + c * p.z + d) / sqrtl(a * a + b * b + c * c);
}

// distance between the 3D lines AB and CD, O(1)
ld dist_line_3d(Point3 A, Point3 B, Point3 C, Point3 D) {
    Point3 u = B - A, v = D - C, w = A - C, n = u.cross(v);
    if (n.abs() < EPS) return w.cross(v).abs() / v.abs();  // parallel
    return fabsl(w.dot(n)) / n.abs();
}

// great-circle distance between two points given as latitude and longitude in degrees, O(1)
ld great_circle_dist(ld lat1, ld lon1, ld lat2, ld lon2, ld r) {
    ld k = PI / 180;
    lat1 *= k; lon1 *= k; lat2 *= k; lon2 *= k;
    ld c = sinl(lat1) * sinl(lat2) + cosl(lat1) * cosl(lat2) * cosl(lon1 - lon2);
    return r * acosl(max<ld>(-1, min<ld>(1, c)));
}

// great-circle angle in radians between two 3D vectors, O(1)
ld great_circle_angle(Point3 a, Point3 b) { return atan2l(a.cross(b).abs(), a.dot(b)); }

// 3D convex hull with integer coordinates, O(n^2)
// requires points[0..2] to be non-collinear and no four points to be coplanar; returns triangular faces (outward normal q)
struct Point3I {
    ll x, y, z;
    Point3I operator-(const Point3I &o) const { return {x - o.x, y - o.y, z - o.z}; }
    Point3I cross(const Point3I &o) const { return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x}; }
    ll dot(const Point3I &o) const { return x * o.x + y * o.y + z * o.z; }
};
struct Face { array<int, 3> p; Point3I q; };

vector<Face> convex_hull_3d(const vector<Point3I> &pts) {
    int n = pts.size();
    vector<Face> faces;
    vector<vector<char>> dead(n, vector<char>(n, true));
    auto add_face = [&](int a, int b, int c) {
        faces.push_back({{a, b, c}, (pts[b] - pts[a]).cross(pts[c] - pts[a])});
        dead[a][b] = dead[b][c] = dead[c][a] = false;
    };
    add_face(0, 1, 2);
    add_face(0, 2, 1);
    for (int i = 3; i < n; i++) {
        vector<Face> keep;
        for (Face &f : faces) {
            if ((pts[i] - pts[f.p[0]]).dot(f.q) > 0) {
                for (int j = 0; j < 3; j++) dead[f.p[j]][f.p[(j + 1) % 3]] = true;
            } else {
                keep.push_back(f);
            }
        }
        faces.clear();
        for (Face &f : keep) {
            for (int j = 0; j < 3; j++) {
                int a = f.p[j], b = f.p[(j + 1) % 3];
                if (dead[b][a]) add_face(b, a, i);
            }
        }
        faces.insert(faces.end(), keep.begin(), keep.end());
    }
    return faces;
}

// true if q is inside or on the convex polygon h (strict hull in CCW order, at least 3 vertices), O(log n)
bool in_convex(Point q, const vector<Point> &h) {
    int n = h.size();
    if (cross(h[0], h[1], q) < -EPS || cross(h[0], h[n - 1], q) > EPS) return false;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (cross(h[0], h[m], q) >= 0) l = m;
        else r = m;
    }
    return cross(h[l], h[l + 1], q) >= -EPS;
}

// sorts p by polar angle around o, counter-clockwise from direction s: angles in [0, 2 pi), or (0, 2 pi] if s_last
// (points in direction s go last); points equal to o count as direction (1, 0), like atan2(0, 0) = 0; ties nearest first
// default: from angle 0 up to 2 pi, points equal to o first; atan2 order (-pi, pi]: sort_by_angle(p, o, {-1, 0}, true)
// exact for integer coordinates up to ~1e9, O(n log n)
void sort_by_angle(vector<Point> &p, Point o = Point(), Point s = Point(1, 0), bool s_last = false) {
    auto dir = [&](const Point &a) { return a == o ? Point(1, 0) : a - o; };
    auto half = [&](const Point &u) {  // 0: angle from s in [0, pi) ((0, pi] if s_last), 1: the rest
        ld c = cross(s, u), d = dot(s, u);
        return c > 0 || (c == 0 && (s_last ? d < 0 : d > 0)) ? 0 : 1;
    };
    sort(p.begin(), p.end(), [&](const Point &a, const Point &b) {
        Point u = dir(a), v = dir(b);
        if (half(u) != half(v)) return half(u) < half(v);
        ld c = cross(u, v);
        return c != 0 ? c > 0 : norm(a - o) < norm(b - o);
    });
}

// Minkowski sum of two convex polygons given as strict hulls in CCW order, as a CCW polygon, O(n + m)
vector<Point> minkowski_sum(vector<Point> a, vector<Point> b) {
    auto to_lowest = [](vector<Point> &p) {
        int s = 0;
        for (int i = 1; i < (int)p.size(); i++) {
            if (p[i].y < p[s].y || (p[i].y == p[s].y && p[i].x < p[s].x)) s = i;
        }
        rotate(p.begin(), p.begin() + s, p.end());
    };
    to_lowest(a);
    to_lowest(b);
    int n = a.size(), m = b.size();
    a.push_back(a[0]);
    a.push_back(a[1 % n]);
    b.push_back(b[0]);
    b.push_back(b[1 % m]);
    vector<Point> res;
    for (int i = 0, j = 0; i < n || j < m; ) {
        res.push_back(a[i] + b[j]);
        ld c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if (c >= 0 && i < n) i++;
        if (c <= 0 && j < m) j++;
    }
    return res;
}

// intersection of half-planes as a CCW polygon, each {a, b} keeping the points to the left of a -> b, O(n log n)
// clipped to the square |x|, |y| <= box; returns an empty list if the intersection is empty or has zero area
vector<Point> half_plane_intersection(vector<pair<Point, Point>> lines, ld box = 1e9) {
    lines.push_back({Point(-box, -box), Point(box, -box)});
    lines.push_back({Point(box, -box), Point(box, box)});
    lines.push_back({Point(box, box), Point(-box, box)});
    lines.push_back({Point(-box, box), Point(-box, -box)});
    struct Half { Point p, d; ld ang; };  // d is a unit direction, so outside tests measure real distance
    vector<Half> hs;
    for (auto &[a, b] : lines) {
        Point d = (b - a) / dist(a, b);
        hs.push_back({a, d, atan2l(d.y, d.x)});
    }
    sort(hs.begin(), hs.end(), [](const Half &x, const Half &y) { return x.ang < y.ang; });
    auto out = [](const Half &h, Point q) { return cross(h.d, q - h.p) < -EPS; };
    auto inter = [](const Half &s, const Half &t) { return s.p + s.d * (cross(t.p - s.p, t.d) / cross(s.d, t.d)); };
    deque<Half> dq;
    for (const Half &h : hs) {
        while (dq.size() >= 2 && out(h, inter(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
        while (dq.size() >= 2 && out(h, inter(dq[0], dq[1]))) dq.pop_front();
        if (!dq.empty() && fabsl(cross(h.d, dq.back().d)) < EPS) {
            if (dot(h.d, dq.back().d) < 0) return {};  // opposite directions facing away from each other
            if (out(h, dq.back().p)) dq.back() = h;  // same direction: keep the more restrictive one
            continue;
        }
        dq.push_back(h);
    }
    while (dq.size() > 2 && out(dq[0], inter(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
    while (dq.size() > 2 && out(dq[dq.size() - 1], inter(dq[0], dq[1]))) dq.pop_front();
    if (dq.size() < 3) return {};
    vector<Point> res;
    for (int i = 0; i < (int)dq.size(); i++) {  // lines meeting at one point would otherwise repeat a vertex
        Point q = inter(dq[i], dq[(i + 1) % dq.size()]);
        if (res.empty() || dist(q, res.back()) > EPS) res.push_back(q);
    }
    if (res.size() > 1 && dist(res[0], res.back()) <= EPS) res.pop_back();
    if (res.size() < 3 || polygon_area(res) < EPS) return {};
    return res;
}

// area of the union of simple polygons, each in CCW order; they may overlap freely and need not be convex, O(N^2 log N) for N total edges
// for each edge, finds the parts not covered by another polygon; those parts are exactly the boundary of the union
ld polygon_union_area(const vector<vector<Point>> &poly) {
    auto sgn = [](ld v) { return (v > EPS) - (v < -EPS); };
    int k = poly.size();
    ld area = 0;
    for (int i = 0; i < k; i++) {
        for (int v = 0, sv = poly[i].size(); v < sv; v++) {
            Point A = poly[i][v], B = poly[i][(v + 1) % sv];
            if (A == B) continue;
            vector<pair<ld, int>> segs = {{0, 0}, {1, 0}};  // {position along AB, change in cover count}
            for (int j = 0; j < k; j++) {
                if (j == i) continue;
                for (int u = 0, su = poly[j].size(); u < su; u++) {
                    Point C = poly[j][u], D = poly[j][(u + 1) % su];
                    int sc = sgn(cross(A, B, C)), sd = sgn(cross(A, B, D));
                    if (sc != sd) {
                        if (min(sc, sd) < 0) {
                            ld sa = cross(C, D, A), sb = cross(C, D, B);
                            segs.push_back({sa / (sa - sb), sgn(sc - sd)});
                        }
                    } else if (sc == 0 && j < i && dot(B - A, D - C) > 0) {  // shared edges count for only one polygon
                        segs.push_back({dot(C - A, B - A) / norm(B - A), 1});
                        segs.push_back({dot(D - A, B - A) / norm(B - A), -1});
                    }
                }
            }
            sort(segs.begin(), segs.end());
            for (auto &s : segs) s.first = min<ld>(max<ld>(s.first, 0), 1);
            ld visible = 0;
            int cnt = segs[0].second;
            for (int j = 1; j < (int)segs.size(); j++) {
                if (cnt == 0) visible += segs[j].first - segs[j - 1].first;
                cnt += segs[j].second;
            }
            area += cross(A, B) * visible;
        }
    }
    return area / 2;
}

// Delaunay triangulation of integer points (Guibas-Stolfi divide and conquer on quad-edges): its edges as index pairs;
// a repeated point is joined to its first copy and collinear points to their neighbours on the line. A Euclidean MST
// only uses these edges (pass them to kruskal with squared lengths); exact for |coordinates| up to ~5e8, O(n log n)
vector<pair<int, int>> delaunay_edges(const vector<pll> &pts) {
    int n = pts.size();
    vector<int> ord(n), id;
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return pts[a] < pts[b]; });
    vector<pll> p;  // distinct points in (x, y) order, and id = their index in pts
    vector<pair<int, int>> res;
    for (int i : ord) {
        if (!p.empty() && pts[i] == p.back()) res.push_back({id.back(), i});
        else p.push_back(pts[i]), id.push_back(i);
    }
    // quad-edge: edge e owns nodes 4e..4e+3 (e, rot, sym, rot of sym); nxt = onext, org = origin of primal nodes
    vector<int> nxt, org;
    vector<char> dead;
    auto rot = [](int e) { return (e & ~3) | ((e + 1) & 3); };
    auto rotinv = [](int e) { return (e & ~3) | ((e + 3) & 3); };
    auto sym = [](int e) { return e ^ 2; };
    auto oprev = [&](int e) { return rot(nxt[rot(e)]); };
    auto lnext = [&](int e) { return rot(nxt[rotinv(e)]); };
    auto dest = [&](int e) { return org[e ^ 2]; };
    auto make_edge = [&](int a, int b) {
        int e = nxt.size();
        nxt.insert(nxt.end(), {e, e + 3, e + 2, e + 1});
        org.insert(org.end(), {a, -1, b, -1});
        dead.push_back(0);
        return e;
    };
    auto splice = [&](int a, int b) {
        int x = rot(nxt[a]), y = rot(nxt[b]);
        swap(nxt[a], nxt[b]);
        swap(nxt[x], nxt[y]);
    };
    auto connect = [&](int a, int b) {  // new edge from dest(a) to org(b), with a, e, b sharing a left face
        int e = make_edge(dest(a), org[b]);
        splice(e, lnext(a));
        splice(sym(e), b);
        return e;
    };
    auto remove = [&](int e) {
        splice(e, oprev(e));
        splice(sym(e), oprev(sym(e)));
        dead[e >> 2] = 1;
    };
    auto ccw = [&](int a, int b, int c) {
        return (__int128)(p[b].first - p[a].first) * (p[c].second - p[a].second) -
               (__int128)(p[b].second - p[a].second) * (p[c].first - p[a].first) > 0;
    };
    auto in_circle = [&](int a, int b, int c, int d) {  // d strictly inside the circle through ccw a, b, c
        __int128 m[3][3];
        int q[3] = {a, b, c};
        for (int i = 0; i < 3; i++) {
            __int128 x = p[q[i]].first - p[d].first, y = p[q[i]].second - p[d].second;
            m[i][0] = x, m[i][1] = y, m[i][2] = x * x + y * y;
        }
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]) > 0;
    };
    auto right_of = [&](int x, int e) { return ccw(x, dest(e), org[e]); };
    auto left_of = [&](int x, int e) { return ccw(x, org[e], dest(e)); };
    // triangulates p[l, r), returns {ccw hull edge out of the leftmost point, cw hull edge out of the rightmost}
    auto rec = [&](auto &self, int l, int r) -> pair<int, int> {
        if (r - l == 2) {
            int a = make_edge(l, l + 1);
            return {a, sym(a)};
        }
        if (r - l == 3) {
            int a = make_edge(l, l + 1), b = make_edge(l + 1, l + 2);
            splice(sym(a), b);
            if (ccw(l, l + 1, l + 2)) {
                connect(b, a);
                return {a, sym(b)};
            }
            if (ccw(l, l + 2, l + 1)) {
                int c = connect(b, a);
                return {sym(c), c};
            }
            return {a, sym(b)};  // collinear
        }
        int mid = (l + r) / 2;
        auto [ldo, ldi] = self(self, l, mid);
        auto [rdi, rdo] = self(self, mid, r);
        while (true) {  // lower common tangent of the two halves
            if (left_of(org[rdi], ldi)) ldi = lnext(ldi);
            else if (right_of(org[ldi], rdi)) rdi = nxt[sym(rdi)];
            else break;
        }
        int base = connect(sym(rdi), ldi);
        if (org[ldi] == org[ldo]) ldo = sym(base);
        if (org[rdi] == org[rdo]) rdo = base;
        auto valid = [&](int e) { return right_of(dest(e), base); };
        while (true) {  // zip the halves together upward, deleting edges that fail the empty-circle test
            int lc = nxt[sym(base)], rc = oprev(base);
            if (valid(lc)) {
                while (in_circle(dest(base), org[base], dest(lc), dest(nxt[lc]))) {
                    int t = nxt[lc];
                    remove(lc);
                    lc = t;
                }
            }
            if (valid(rc)) {
                while (in_circle(dest(base), org[base], dest(rc), dest(oprev(rc)))) {
                    int t = oprev(rc);
                    remove(rc);
                    rc = t;
                }
            }
            bool vl = valid(lc), vr = valid(rc);
            if (!vl && !vr) break;
            if (!vl || (vr && in_circle(dest(lc), org[lc], org[rc], dest(rc)))) base = connect(rc, sym(base));
            else base = connect(sym(base), sym(lc));
        }
        return {ldo, rdo};
    };
    if (p.size() >= 2) rec(rec, 0, p.size());
    for (int e = 0; e < (int)dead.size(); e++) if (!dead[e]) res.push_back({id[org[4 * e]], id[org[4 * e + 2]]});
    return res;
}

// number of points of B strictly inside the triangle A[a] A[b] A[c], for many queries; |coordinates| up to 1e9
// in (x, y) order (as if rotated slightly, so no two x are equal), below[i][j] counts the B points strictly between
// A[i] < A[j] and strictly below the segment, on[i][j] those on it; a triangle is its upper chain minus its lower one
//   TriangleCounter(A, B)   precompute, O(|A|^2 |B|)
//   count(a, b, c)          points strictly inside A[a] A[b] A[c] (0 if degenerate), O(1)
struct TriangleCounter {
    vector<pll> A;
    vector<vector<int>> below, on;
    vector<int> same;  // number of B points equal to A[i]

    static ll cross(pll o, pll a, pll b) {
        return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
    }

    TriangleCounter(const vector<pll> &A, const vector<pll> &B): A(A), below(A.size(), vector<int>(A.size())), on(below), same(A.size()) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            for (const pll &q : B) same[i] += q == A[i];
            for (int j = 0; j < n; j++) {
                if (!(A[i] < A[j])) continue;
                for (const pll &q : B) {
                    if (!(A[i] < q && q < A[j])) continue;
                    ll c = cross(A[i], A[j], q);
                    if (c < 0) below[i][j]++;
                    else if (c == 0) on[i][j]++;
                }
            }
        }
    }

    int count(int a, int b, int c) const {
        if (A[b] < A[a]) swap(a, b);
        if (A[c] < A[b]) swap(b, c);
        if (A[b] < A[a]) swap(a, b);
        ll s = cross(A[a], A[c], A[b]);
        if (s == 0) return 0;
        if (s > 0) return below[a][b] + below[b][c] - below[a][c] - on[a][c];  // b above the segment a c
        return below[a][c] - below[a][b] - below[b][c] - on[a][b] - on[b][c] - same[b];
    }
};
