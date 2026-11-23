# C++ Templates

Every top-level struct and function in this folder, taken from the `// Contents` block at the top of each file.

- [Contest](#contest): [`new_file.cpp`](new_file.cpp), [`stress_gen.cpp`](stress_gen.cpp), [`safe_hash.cpp`](safe_hash.cpp)
- [Data Structures](#data-structures): [`data_structures.cpp`](data_structures.cpp), [`dsu.cpp`](dsu.cpp), [`segment_tree.cpp`](segment_tree.cpp), [`monoids.cpp`](monoids.cpp), [`persistent_segment_tree.cpp`](persistent_segment_tree.cpp)
- [Graphs](#graphs): [`graph_search.cpp`](graph_search.cpp), [`shortest_paths.cpp`](shortest_paths.cpp), [`graph_algorithms.cpp`](graph_algorithms.cpp), [`flows.cpp`](flows.cpp), [`min_cost_flow.cpp`](min_cost_flow.cpp), [`matching.cpp`](matching.cpp), [`trees.cpp`](trees.cpp)
- [Strings](#strings): [`strings.cpp`](strings.cpp)
- [Math](#math): [`modint.cpp`](modint.cpp), [`big_integer.cpp`](big_integer.cpp), [`hex_big_integer.cpp`](hex_big_integer.cpp), [`number_theory.cpp`](number_theory.cpp), [`combinatorics.cpp`](combinatorics.cpp), [`matrix.cpp`](matrix.cpp), [`linear_algebra.cpp`](linear_algebra.cpp), [`fft.cpp`](fft.cpp), [`polynomial.cpp`](polynomial.cpp), [`bitmask.cpp`](bitmask.cpp)
- [Geometry](#geometry): [`geometry.cpp`](geometry.cpp)
- [DP and Search](#dp-and-search): [`binary_ternary_search.cpp`](binary_ternary_search.cpp), [`dp_optimizations.cpp`](dp_optimizations.cpp)
- [Miscellaneous](#miscellaneous): [`misc.cpp`](misc.cpp)

## Contest

### [`new_file.cpp`](new_file.cpp)

Contest starting template: includes, type aliases, constants, `dbg` macro and a multi-test `main`.

### [`stress_gen.cpp`](stress_gen.cpp)

| Name | Description |
| --- | --- |
| `rnd` | random integer in [lo, hi], O(1) |
| `rnd_array` | n random integers in [lo, hi], O(n) |
| `rnd_perm` | random permutation of 1..n, O(n) |
| `rnd_string` | random string of length n using the first k lowercase letters, O(n) |
| `rnd_tree` | random tree on vertices 1..n as n - 1 edges; shape 0 = uniform parents, 1 = path |
| `rnd_graph` | random simple graph on vertices 1..n with m edges (no loops or repeats) |

### [`safe_hash.cpp`](safe_hash.cpp)

| Name | Description |
| --- | --- |
| `SafeHash` | hash for unordered_map / unordered_set that resists anti-hash tests |
| `SafeMap` | unordered_map using SafeHash |
| `SafeSet` | unordered_set using SafeHash |

## Data Structures

### [`data_structures.cpp`](data_structures.cpp)

| Name | Description |
| --- | --- |
| `IndexedSet` | set with order statistics: s.find_by_order(k) (0-indexed iterator) |
| `Compressor` | coordinate compression |
| `Fenwick` | Fenwick tree (0-indexed) |
| `RangeFenwick` | Fenwick tree with range update, point query (0-indexed) |
| `MinStack` | stack with minimum query |
| `MinQueue` | queue with minimum query |
| `MisofTree` | multiset of integers in [0, 2^BITS) |
| `hilbert_order` | position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow) |
| `mo` | Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r) |
| `MinOp` | example idempotent op (min) for SparseTable |
| `SparseTable` | static range query for idempotent ops (min, max, gcd), O(1) |
| `SparseTable2D` | static rectangle query for idempotent ops |
| `RollbackDSU` | DSU with undo, example structure for OfflineDynamic below; D needs Op, snapshot() |
| `OfflineDynamic` | segment tree over time |
| `ImplicitTreap` | implicit treap: an array supporting insert/erase at any position with range add |
| `WaveletMatrix` | wavelet matrix: static order statistics on subarrays, online; values can be any integers |

### [`dsu.cpp`](dsu.cpp)

| Name | Description |
| --- | --- |
| `DSU` | disjoint set union with path compression and union by size |

### [`segment_tree.cpp`](segment_tree.cpp)

| Name | Description |
| --- | --- |
| `Monoid` | example monoid (sum) for SegTree |
| `SegTree` | iterative segment tree, point update, query on [l, r) |
| `Spec` | example lazy spec (range add, range sum) for LazySegTree |
| `LazySegTree` | lazy segment tree (iterative), range update and query on [l, r) |
| `SegTree2D` | 2D segment tree (iterative), point update |
| `DynamicSegTree` | implicit segment tree on any integer range [lo, hi) |
| `MergeSortTree` | merge sort tree: static counting of values in a range, online |
| `SegTreeBeats` | segment tree beats on [l, r): range chmin, chmax and add with sum, max and min queries |

### [`monoids.cpp`](monoids.cpp)

| Name | Description |
| --- | --- |
| `SumM` | basic monoids: SumM, MinM, MaxM, GcdM, XorM |
| `MinIdx` | min with its leftmost index |
| `MinCount` | min with the number of times it occurs |
| `MaxSub` | maximum subarray sum |
| `Brackets` | unmatched brackets; a range is balanced iff it reduces to {0, 0} |
| `Hash` | polynomial hash and reverse hash (substring equality, palindromes) |
| `AffineComp` | composition of maps x -> ax + b, applied left to right |
| `MatProd` | K x K matrix product, for DP transitions over a segment |
| `AddMin` | range add, range min (AddMax: range max) |
| `AddMinCount` | range add, range min with count (area of a union of rectangles) |
| `SetAdd` | range assign and range add, range sum / min / max |
| `AffineSum` | range x -> ax + b, range sum |
| `AddSumSq` | range add, range sum and sum of squares |
| `PolyAddSum` | range add of a degree-K polynomial in the index, range sum |
| `XorSum` | range xor, range sum |
| `BitRuns` | range assign / flip on a 0-1 array, count of ones and longest run |
| `SetMaxSub` | range assign, maximum subarray sum |

### [`persistent_segment_tree.cpp`](persistent_segment_tree.cpp)

| Name | Description |
| --- | --- |
| `Monoid` | example monoid (sum) for PersistentSegTree |
| `PersistentSegTree` | persistent segment tree, point update, query on [l, r) |
| `Spec` | example lazy spec (range add, range sum) for PersistentLazySegTree |
| `PersistentLazySegTree` | persistent lazy segment tree, range update and query on [l, r) |
| `LeqCounter` | counts values <= x in any subarray, online; values can be any integers |
| `UniqueCounter` | counts distinct values in any subarray, online; uses LeqCounter above |

## Graphs

### [`graph_search.cpp`](graph_search.cpp)

| Name | Description |
| --- | --- |
| `topo_sort` | Kahn's algorithm, O(V + E); returns vertices in topological order |

### [`shortest_paths.cpp`](shortest_paths.cpp)

| Name | Description |
| --- | --- |
| `BellmanFord` | single-source shortest paths, negative weights allowed |
| `FloydWarshall` | all-pairs shortest paths; adj[i][j] = weight, 0 means no edge |
| `Dijkstra` | single-source shortest paths, non-negative weights only |
| `zero_one_bfs` | shortest paths from s when every edge weight is 0 or 1 (0-1 BFS), INF if unreachable |

### [`graph_algorithms.cpp`](graph_algorithms.cpp)

| Name | Description |
| --- | --- |
| `SCC` | strongly connected components (Tarjan), 0-indexed |
| `TwoSat` | 2-SAT, uses SCC above |
| `min_mean_cycle` | smallest average edge weight over all directed cycles (Karp) |
| `Biconnected` | bridges, articulation points and biconnected components of an undirected graph |
| `kruskal` | minimum spanning forest (Kruskal), edges are {w, u, v} |
| `euler_directed` | Euler path/cycle in a directed graph, as a vertex list of length E + 1 |
| `euler_undirected` | Euler path/cycle in an undirected graph, as a vertex list of length E + 1 |
| `Arborescence` | minimum spanning arborescence (Chu-Liu/Edmonds) |
| `dominator_tree` | dominator tree of a directed graph from root (Lengauer-Tarjan), O(E log V) |
| `MaxClique` | cliques in a graph on at most N vertices, exponential in the worst case |
| `chromatic_number` | fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets) |
| `steiner_tree` | weight of the cheapest connected subgraph containing all terminals (Steiner tree) |
| `KShortestWalks` | k shortest walks from s to t (Eppstein with a persistent leftist heap) |
| `SimplePaths` | k shortest simple paths from s to t (Yen's algorithm): no vertex repeats |

### [`flows.cpp`](flows.cpp)

| Name | Description |
| --- | --- |
| `Flow` | Dinic's algorithm, O(V^2 E) |
| `GomoryHu` | all-pairs max flow on an undirected graph (Gomory-Hu tree), uses Flow above |

### [`min_cost_flow.cpp`](min_cost_flow.cpp)

| Name | Description |
| --- | --- |
| `MinCostFlow` | min cost max flow (successive shortest paths with potentials); negative costs are fine |

### [`matching.cpp`](matching.cpp)

| Name | Description |
| --- | --- |
| `HopcroftKarp` | maximum bipartite matching (Hopcroft-Karp); left vertices 0..n-1, right vertices 0..m-1 |
| `hungarian` | minimum cost assignment (Hungarian) of every row to a distinct column |
| `Blossom` | maximum matching in a general graph (Edmonds' blossom) |
| `stable_marriage` | stable marriage (Gale-Shapley), O(n^2): men[i] and women[i] are preference lists |

### [`trees.cpp`](trees.cpp)

| Name | Description |
| --- | --- |
| `BinaryLift` | binary lifting on a rooted tree, 0-indexed |
| `LCA` | lowest common ancestor with O(1) queries (sparse table over DFS order), 0-indexed |
| `HLD` | heavy-light decomposition, 0-indexed |
| `CentroidDecomp` | centroid decomposition, 0-indexed; example use: nearest painted vertex |
| `TreeCanon` | tree isomorphism by canonical ids (AHU); compare ids from the same TreeCanon object |
| `tree_diameter` | diameter of a weighted tree; returns {length, path} |
| `SumDist` | rerooting DP example: sum of distances from each vertex to all others |
| `rerooting` | answer of a tree DP for every choice of root; returns ans[v] for each v |
| `dsu_on_tree` | small-to-large on a tree (DSU on tree / sack) |
| `virtual_tree` | virtual tree of the vertices vs, using LCA above; returns {nodes, par} |
| `LinkCutTree` | link-cut tree: a forest under link and cut with path sum queries, 0-indexed |

## Strings

### [`strings.cpp`](strings.cpp)

| Name | Description |
| --- | --- |
| `prefix_function` | prefix function, O(n) |
| `kmp` | start indices of all occurrences of f in s, O(\|s\| + \|f\|) |
| `Booth` | Booth's algorithm for the lexicographically smallest rotation in O(n) |
| `z_function` | Z function, O(n): z[i] = length of the longest common prefix of s and s[i..]; z[0] = n |
| `Trie` | trie over sequences of any comparable type, L = sequence length |
| `PersistentXorTrie` | persistent binary trie |
| `SuffixArray` | suffix array and LCP array |
| `AhoCorasick` | Aho-Corasick automaton: KMP for many patterns over the alphabet [BASE, BASE + ALPHA) |
| `Eertree` | palindromic tree (eertree) over lowercase letters |
| `RollingHash` | polynomial rolling hash mod 2^61 - 1 with a random base |
| `manacher` | Manacher's algorithm, O(n); returns {d1, d2} |
| `SuffixAutomaton` | suffix automaton over lowercase letters |

## Math

### [`modint.cpp`](modint.cpp)

| Name | Description |
| --- | --- |
| `ModInt` | modular integer with a compile-time modulus |

### [`big_integer.cpp`](big_integer.cpp)

| Name | Description |
| --- | --- |
| `BigInt` | arbitrary-precision signed integer in base 1e9 limbs |

### [`hex_big_integer.cpp`](hex_big_integer.cpp)

| Name | Description |
| --- | --- |
| `HexBigInt` | arbitrary-precision signed hex integer in base 2^28 limbs (7 hex digits each) |

### [`number_theory.cpp`](number_theory.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `modinv_p` | inverse of a mod prime p (Fermat), O(log p) |
| `extended_euclidean` | returns g = gcd(a, b) and sets x, y so that ax + by = g, O(log min(a, b)) |
| `modinv` | inverse of a mod any modulus, -1 if gcd(a, mod) != 1, O(log mod) |
| `discrete_log` | smallest x >= 0 with a^x = b (mod m), -1 if none; baby-step giant-step, O(sqrt(m)) |
| `is_prime` | trial-division primality test, O(sqrt(n)) |
| `sieve` | Sieve of Eratosthenes: prime[i] for 0 <= i <= n, O(n log log n) |
| `sum_of_divisors` | sum of the divisors of n, mod mod, O(sqrt(n)) |
| `miller_rabin` | deterministic Miller-Rabin for any n fitting in ll, O(log n) multiplications |
| `mobius_sieve` | Mobius function mu[0..n], O(n log log n) |
| `gcd_subset_count` | cnt[g] = number of non-empty subsets of a with gcd exactly g, mod mod |
| `divisor_transform` | sum over multiples or divisors of each index (and its inverse), one prime at a time |
| `gcd_convolution` | c[k] = sum of a[i] * b[j] over all gcd(i, j) == k (or lcm(i, j) == k), 1-indexed |
| `totient` | Euler's totient phi(n), O(sqrt n) |
| `mod_solver` | solves a * x = b (mod m), m > 0: returns {x, M} meaning all solutions are x mod M |
| `diophantine` | integers x, y with a * x + b * y = c, nullopt if none; prefers y > 0 |
| `crt` | solves x = b1 (mod m1), x = b2 (mod m2), m1, m2 > 0: returns {x, lcm}, nullopt if none |
| `super_crt` | solves a[i] * x = b[i] (mod m[i]) for every i |
| `josephus` | survivor (0-indexed) among n people when every k-th is removed |
| `spf_sieve` | smallest prime factor of every number up to n (linear sieve); spf[0] = spf[1] = 0, O(n) |
| `factorize_spf` | prime factorization of x >= 1 as {prime, exponent} pairs in increasing order |
| `pollard_rho` | a nontrivial factor of a composite n (Pollard's rho, Brent's variant) |
| `factorize` | prime factors of n >= 1 in increasing order, with repeats; n can be any ll |
| `primitive_root` | smallest primitive root mod prime m, any m fitting in ll; uses factorize above |
| `floor_sum` | sum of floor((a * i + b) / m) for i in [0, n); m > 0, a and b can be negative, O(log m) |
| `mod_sqrt` | a square root of a mod the prime p (Tonelli-Shanks), the smaller of the two |
| `kth_root_floor` | floor(a^(1/k)) for any a < 2^64 and k >= 1, O(k) |
| `kth_root_mod` | some x with x^k = a (mod p) for a prime p, -1 if none (Adleman-Manders-Miller) |
| `bernoulli` | Bernoulli numbers B[0..n] mod a prime p > n + 1, with B[1] = -1/2, O(n^2) |
| `tetration` | a^^b = a^(a^(...^a)) (b copies of a) mod m, with a^^0 = 1 and 0^0 = 1 |
| `count_squarefree` | number of squarefree integers in [1, n], n up to 1e18, O(n^(2/5)) |

### [`combinatorics.cpp`](combinatorics.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `modinv_p` | inverse of a mod prime p (Fermat), O(log p) |
| `comb` | exact nCk without a modulus, O(k); n * C(n - 1, k - 1) must fit in ll |
| `init_fac` | O(n) precompute factorials up to n; mod must be a prime > n |
| `comb_f` | O(1) nCk mod p, requires init_fac(N, mod) with N >= n |
| `comb_m` | O(k) nCk mod p without precomputation, useful when n is huge but k is small |
| `factorial` | exact n! without a modulus (overflows for n > 20), O(n) |
| `lucas` | nCk mod a prime p (Lucas), O(p) once per p, then O(log_p n) per call |
| `CombAny` | nCk mod any m (Granville + CRT), O(m) tables, then O(log n) per query per prime power |
| `OrderTree` | helper for permutations: which of 0..n-1 are still available |
| `perm_to_factoradic` | factoradic digits of a permutation of 0..n-1 |
| `factoradic_to_perm` | inverse of perm_to_factoradic, O(n log n) |
| `kth_permutation` | k-th permutation of 0..n-1 in lexicographic order (0-indexed); k is taken mod n! |

### [`matrix.cpp`](matrix.cpp)

| Name | Description |
| --- | --- |
| `Matrix` | dense matrix with entries mod MOD |

### [`linear_algebra.cpp`](linear_algebra.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `gauss_jordan` | reduces a to reduced row echelon form using its first cols columns, returns the rank |
| `solve_linear` | solves A x = b; free variables are set to 0; returns false if there is no solution |
| `gauss_jordan_mod` | reduces a to reduced row echelon form mod a prime p < 2^31 using its first cols columns |
| `solve_linear_mod` | solves A x = b mod a prime p < 2^31; free variables are set to 0 |
| `inverse_mod` | inverse of a square matrix mod a prime p < 2^31; returns false if it is singular, O(n^3) |
| `solve_xor` | solves A x = b over GF(2) (XOR equations) with m <= N variables |
| `det_mod` | determinant of a square matrix mod a prime, O(n^3) |
| `count_spanning_trees` | number of spanning trees of a multigraph mod a prime (Kirchhoff), O(n^3) |
| `XorBasis` | XOR linear basis over values in [0, 2^BITS), BITS <= 62 |

### [`fft.cpp`](fft.cpp)

| Name | Description |
| --- | --- |
| `fft` | in-place FFT (inverse FFT if invert, including the 1/n scaling) |
| `multiply` | product of integer polynomials a and b, O((n + m) log(n + m)) |
| `binexp` | a^b mod mod, O(log b) |
| `NTT` | number theoretic transform, each MOD and ROOT pair is its own type |
| `garner` | combine residues mod several primes into the value mod `mod` (0 means mod 2^64) |
| `convolution_any_mod` | product of polynomials a and b mod any modulus below 2^31 |
| `convolution_mod_2_64` | product of polynomials a and b mod 2^64 |

### [`polynomial.cpp`](polynomial.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `NTT` | number theoretic transform, each MOD and ROOT pair is its own type |
| `Poly` | polynomial operations mod MOD, using NTT above; a[i] is the coefficient of x^i |
| `poly_divide_real` | long division of real polynomials: returns {quotient, remainder} of a / b |
| `berlekamp_massey` | shortest linear recurrence of s mod a prime (Berlekamp-Massey), O(n^2) |
| `kth_term` | k-th term (0-indexed) of the recurrence s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ..., mod a modulus below 2^31 |
| `kth_term_ntt` | k-th term of a linear recurrence mod an NTT prime (Bostan-Mori), O(d log d log k) |
| `bernoulli_ntt` | Bernoulli numbers B[0..n] mod an NTT prime, with B[1] = -1/2, O(n log n) |
| `bell_ntt` | Bell numbers B[0..n] mod an NTT prime, as exp(e^x - 1), O(n log n) |
| `shift_samples` | h(a), ..., h(a + m - 1) from h(0), ..., h(n - 1) (shift of sampling points), O((n + m) log(n + m)) |
| `FactorialMod` | n! mod an NTT prime for any n < MOD, block table of (iV)!, O(V) per query |
| `lagrange` | value at x of the unique polynomial through (xs[i], ys[i]) |
| `lagrange_consecutive` | value at x of the unique polynomial with p(i) = ys[i] for i = 0..n-1 |

### [`bitmask.cpp`](bitmask.cpp)

| Name | Description |
| --- | --- |
| `sos_subset` | SOS DP: a[mask] becomes the sum of a[sub] over all submasks sub of mask (undone if invert), O(n log n) |
| `sos_superset` | SOS DP: a[mask] becomes the sum of a[sup] over all supermasks sup of mask (undone if invert), O(n log n) |
| `xor_transform` | Walsh-Hadamard transform (inverse if invert, including the 1/n scaling), O(n log n) |
| `pad_to_power` | pads a and b with zeros to a common power of 2 length (at least 1), O(n) |
| `or_convolution` | c[k] = sum of a[i] * b[j] over all i \| j == k, O(n log n) |
| `and_convolution` | c[k] = sum of a[i] * b[j] over all i & j == k, O(n log n) |
| `xor_convolution` | c[k] = sum of a[i] * b[j] over all i ^ j == k, O(n log n) |

## Geometry

### [`geometry.cpp`](geometry.cpp)

| Name | Description |
| --- | --- |
| `Point` | 2D point / vector |
| `dot` | dot product, O(1) |
| `cross` | cross product, O(1) |
| `norm` | squared length, O(1) |
| `abs` | length, O(1) |
| `dist` | distance between a and b, O(1) |
| `angle` | angle abc at b in radians, in [0, pi], O(1) |
| `rotate` | rotate a counter-clockwise by d radians about pivot p, O(1) |
| `proj_line` | projection of p onto the line ab, O(1) |
| `proj_seg` | closest point to p on the segment ab, O(1) |
| `dist_pt_line` | distance from p to the line ax + by + c = 0, O(1) |
| `line_inter` | intersection of lines ab and cd (segments if seg), nullopt if there is none |
| `circle_line_inter` | intersection points of the circle (c, r) and the line ab: 0, 1 (tangent), or 2 points |
| `circle_circle_inter` | intersection points of circles (c1, r1) and (c2, r2): 0, 1 (tangent), or 2 points |
| `polygon_area` | area of a simple polygon, O(n) |
| `triangle_area` | area of a triangle from its side lengths (Heron), O(1) |
| `cyclic_quad_area` | area of a cyclic quadrilateral (opposite angles sum to 180 degrees) from its side lengths (Brahmagupta), O(1) |
| `polygon_centroid` | centroid (center of mass) of a simple polygon with nonzero area, O(n) |
| `convex_hull` | convex hull in counter-clockwise order (monotone chain), O(n log n) |
| `on_polygon` | true if q is on the boundary of polygon p, O(n) |
| `in_polygon` | true if q is inside polygon p (for points on the boundary, use on_polygon), O(n) |
| `cut_polygon` | part of polygon p to the left of the directed line a -> b, O(n) |
| `bary` | point with barycentric weights a, b, c in triangle ABC, O(1) |
| `trilinear` | point with trilinear coordinates a : b : c in triangle ABC, O(1) |
| `centroid` | centroid of a triangle, O(1) |
| `circumcenter` | circumcenter of a non-degenerate triangle, O(1) |
| `orthocenter` | orthocenter of a non-degenerate triangle, O(1) |
| `incenter` | incenter of a triangle, O(1) |
| `inradius` | inradius of a triangle from its side lengths, O(1) |
| `excenter` | excenter opposite A; cycle the arguments for the other two, O(1) |
| `brocard` | first Brocard point of a triangle (CCW); swap B and C for the other one, O(1) |
| `symmedian` | symmedian point of a triangle, O(1) |
| `convex_polygon_inter` | intersection of two convex polygons as a convex polygon, O(nm + (n + m) log(n + m)) |
| `lattice_boundary` | number of lattice points on the boundary of a polygon with integer vertices, O(n log C) |
| `lattice_interior` | number of lattice points strictly inside a polygon with integer vertices (Pick's theorem), O(n log C) |
| `min_enclosing_circle` | smallest circle containing all points, returned as {center, radius}, O(n) expected |
| `furthest_pair` | two of the points at the largest distance (diameter, rotating calipers), n >= 1, O(n log n) |
| `polygon_width` | smallest distance between two parallel lines containing all points between them (rotating calipers), O(n log n) |
| `closest_pair` | two of the points at the smallest distance (line sweep), n >= 2, O(n log n) |
| `KDTree` | 2D tree for nearest neighbor queries; the tree reorders its own copy of the points |
| `Point3` | 3D point / vector with arithmetic, dot, cross, and length, O(1) each |
| `proj_plane` | projection of p onto the plane ax + by + cz + d = 0, O(1) |
| `dist_pt_plane` | distance from p to the plane ax + by + cz + d = 0, O(1) |
| `dist_line_3d` | distance between the 3D lines AB and CD, O(1) |
| `great_circle_dist` | great-circle distance between two points given as latitude and longitude in degrees |
| `great_circle_angle` | great-circle angle in radians between two 3D vectors, O(1) |
| `Point3I` | 3D point with integer coordinates, for convex_hull_3d |
| `Face` | triangular face of a 3D hull, for convex_hull_3d |
| `convex_hull_3d` | 3D convex hull with integer coordinates, O(n^2) |
| `in_convex` | true if q is inside or on the convex polygon h (strict hull in CCW order, at least 3 vertices), O(log n) |
| `sort_by_angle` | sorts p by polar angle around o, counter-clockwise from direction s (default angle 0); atan2 order supported |
| `minkowski_sum` | Minkowski sum of two convex polygons given as strict hulls in CCW order |
| `half_plane_intersection` | intersection of half-planes as a CCW polygon |
| `polygon_union_area` | area of the union of simple polygons, each in CCW order |

## DP and Search

### [`binary_ternary_search.cpp`](binary_ternary_search.cpp)

| Name | Description |
| --- | --- |
| `ternary_search_int` | smallest x in [lo, hi] minimizing f, O(log(hi - lo)) calls to f; f must fall, then rise |
| `ternary_search_real` | x in [lo, hi] minimizing a real function that falls and then rises, O(iters) calls to f |

### [`dp_optimizations.cpp`](dp_optimizations.cpp)

| Name | Description |
| --- | --- |
| `LineContainer` | dynamic convex hull trick: add lines in any order, query at any x |
| `LiChao` | Li Chao tree on integer x in [lo, hi] |
| `PersistentLiChao` | persistent Li Chao tree for minimum queries on integer x in [lo, hi] |
| `dnc_opt` | divide and conquer DP optimization |
| `knuth_opt` | Knuth optimization, O(n^2) |

## Miscellaneous

### [`misc.cpp`](misc.cpp)

| Name | Description |
| --- | --- |
| `SAT` | SAT solver (DPLL with watched literals); variables are 1..n, literal -x means "not x" |
| `find_cycle` | Floyd's cycle finding on x0, f(x0), f(f(x0)), ...: returns {mu, lambda} (tail length, cycle length), O(mu + lambda) |
| `lis` | indices of a longest strictly increasing subsequence of a, O(n log n) |
| `date_to_int` | day number (Julian day) of a Gregorian date, O(1) |
| `int_to_date` | Gregorian date of a day number, O(1) |
| `int_to_day` | day of the week of a day number, 0 = Monday, O(1) |
| `cur_time` | current CPU time in seconds, O(1) |
| `simulated_annealing` | simulated annealing example |
| `Simplex` | two-phase simplex: maximize c^T x subject to A x <= b, x >= 0; A is m x n |
| `read_int` | reads the next integer from stdin into x, false at end of input, O(digits) |
| `next_bit_perm` | next larger integer with the same number of set bits; requires x > 0, O(1) |
| `is_square` | true if x is a perfect square, O(1) |
| `simpson` | numeric integral of f over [a, b] by Simpson's rule, O(steps); steps must be even |
| `DLX` | exact cover with dancing links (Algorithm X) |
