# C++ Templates

Every top-level struct and function in this folder, taken from the `// Contents` block at the top of each file.
Each folder is one chapter of the notebook; the contest template `new_file.cpp` sits at the top level for quick access.

- [Contest](#contest): [`new_file.cpp`](new_file.cpp), [`stress_gen.cpp`](contest/stress_gen.cpp), [`safe_hash.cpp`](contest/safe_hash.cpp), [`interactor.cpp`](contest/interactor.cpp), [`interact.py`](contest/interact.py)
- [Data Structures](#data-structures): [`dsu.cpp`](data_structures/dsu.cpp), [`fenwick.cpp`](data_structures/fenwick.cpp), [`sparse_table.cpp`](data_structures/sparse_table.cpp), [`segment_tree.cpp`](data_structures/segment_tree.cpp), [`wavelet.cpp`](data_structures/wavelet.cpp), [`treap.cpp`](data_structures/treap.cpp), [`offline.cpp`](data_structures/offline.cpp), [`misc.cpp`](data_structures/misc.cpp), [`monoids.cpp`](data_structures/monoids.cpp), [`persistent_segment_tree.cpp`](data_structures/persistent_segment_tree.cpp)
- [Graphs](#graphs): [`shortest_paths.cpp`](graphs/shortest_paths.cpp), [`scc.cpp`](graphs/scc.cpp), [`biconnected.cpp`](graphs/biconnected.cpp), [`euler.cpp`](graphs/euler.cpp), [`spanning_trees.cpp`](graphs/spanning_trees.cpp), [`dominator_tree.cpp`](graphs/dominator_tree.cpp), [`np_hard.cpp`](graphs/np_hard.cpp), [`k_shortest_paths.cpp`](graphs/k_shortest_paths.cpp), [`flows.cpp`](graphs/flows.cpp), [`min_cost_flow.cpp`](graphs/min_cost_flow.cpp), [`matching.cpp`](graphs/matching.cpp), [`trees.cpp`](graphs/trees.cpp), [`rerooting.cpp`](graphs/rerooting.cpp), [`link_cut_tree.cpp`](graphs/link_cut_tree.cpp), [`euler_tour_tree.cpp`](graphs/euler_tour_tree.cpp), [`cycles.cpp`](graphs/cycles.cpp), [`triangles.cpp`](graphs/triangles.cpp)
- [Strings](#strings): [`strings.cpp`](strings/strings.cpp)
- [Math](#math): [`modint.cpp`](math/modint.cpp), [`number_theory.cpp`](math/number_theory.cpp), [`combinatorics.cpp`](math/combinatorics.cpp), [`matrix.cpp`](math/matrix.cpp), [`linear_algebra.cpp`](math/linear_algebra.cpp), [`fft.cpp`](math/fft.cpp), [`polynomial.cpp`](math/polynomial.cpp), [`bitmask.cpp`](math/bitmask.cpp), [`big_integer.cpp`](math/big_integer.cpp), [`hex_big_integer.cpp`](math/hex_big_integer.cpp), [`int128.cpp`](math/int128.cpp), [`simplex.cpp`](math/simplex.cpp)
- [Geometry](#geometry): [`geometry.cpp`](geometry/geometry.cpp)
- [DP and Search](#dp-and-search): [`binary_ternary_search.cpp`](dp_search/binary_ternary_search.cpp), [`dp_optimizations.cpp`](dp_search/dp_optimizations.cpp), [`digit_dp.cpp`](dp_search/digit_dp.cpp)
- [Miscellaneous](#miscellaneous): [`sat.cpp`](misc/sat.cpp), [`dlx.cpp`](misc/dlx.cpp), [`misc.cpp`](misc/misc.cpp)

## Contest

### [`new_file.cpp`](new_file.cpp)

Contest starting template: includes, type aliases, constants, `dbg` macro and a multi-test `main`.

### [`contest/stress_gen.cpp`](contest/stress_gen.cpp)

| Name | Description |
| --- | --- |
| `rnd` | random integer in [lo, hi], O(1) |
| `rnd_array` | n random integers in [lo, hi], O(n) |
| `rnd_perm` | random permutation of 1..n, O(n) |
| `rnd_string` | random string of length n using the first k lowercase letters, O(n) |
| `rnd_tree` | random tree on vertices 1..n as n - 1 edges; shape 0 = uniform parents, 1 = path |
| `rnd_graph` | random simple graph on vertices 1..n with m edges (no loops or repeats) |

### [`contest/safe_hash.cpp`](contest/safe_hash.cpp)

| Name | Description |
| --- | --- |
| `SafeHash` | hash for unordered_map / unordered_set that resists anti-hash tests |
| `SafeMap` | unordered_map using SafeHash |
| `SafeSet` | unordered_set using SafeHash |
| `Zobrist` | random 64-bit label per key: XOR / sum of labels hash sets / multisets, with prefix hashes |

### [`contest/interactor.cpp`](contest/interactor.cpp)

| Name | Description |
| --- | --- |
| `rnd` | random integer in [lo, hi], O(1) |
| `wrong` | reject the solution: print the reason to stderr and exit with code 1 |
| `main` | example interactor (guess a hidden number with "? y" queries), for interact.py |

### [`contest/interact.py`](contest/interact.py)

Local runner for interactive problems: `python interact.py SOLUTION INTERACTOR [FIRST_SEED [LAST_SEED]]` joins the
solution to the interactor through pipes, runs the seeds in order and stops at the first one that is rejected,
crashes or times out, printing the transcript of the exchange.

## Data Structures

### [`data_structures/dsu.cpp`](data_structures/dsu.cpp)

| Name | Description |
| --- | --- |
| `DSU` | disjoint set union with path compression and union by size |
| `PotentialDSU` | DSU with potentials: value(u) - value(v) under constraints, for any additive group |
| `PersistentArray` | persistent array (path-copied segment tree), O(log n) get and set |
| `PersistentDSU` | persistent DSU: every merge makes a new version, O(log^2 n) per operation |
| `RollbackDSU` | DSU with undo, example structure for OfflineDynamic below; D needs Op, snapshot() |
| `SumDSU` | RollbackDSU with component sums and point adds, for OfflineDynamic |
| `OfflineDynamic` | segment tree over time |

### [`data_structures/fenwick.cpp`](data_structures/fenwick.cpp)

| Name | Description |
| --- | --- |
| `Fenwick` | Fenwick tree (0-indexed) |
| `RangeFenwick` | Fenwick tree with range update, point query (0-indexed) |
| `Fenwick2D` | 2D Fenwick tree over points known in advance: point add, rectangle sum |
| `rect_add_rect_sum` | offline rectangle adds, then rectangle sums, mod a modulus (sweep with Fenwick trees), O((n + q) log n) |

### [`data_structures/sparse_table.cpp`](data_structures/sparse_table.cpp)

| Name | Description |
| --- | --- |
| `MinOp` | example idempotent op (min) for SparseTable |
| `SparseTable` | static range query for idempotent ops (min, max, gcd), O(1) |
| `SparseTable2D` | static rectangle query for idempotent ops |

### [`data_structures/segment_tree.cpp`](data_structures/segment_tree.cpp)

| Name | Description |
| --- | --- |
| `Monoid` | example monoid (sum) for SegTree |
| `SegTree` | iterative segment tree, point update, query on [l, r) |
| `Spec` | example lazy spec (range add, range sum) for LazySegTree |
| `LazySegTree` | lazy segment tree (iterative), range update and query on [l, r) |
| `MinCount` | copy of MinCount from monoids.cpp, for rect_union_area |
| `AddMinCount` | copy of AddMinCount from monoids.cpp, for rect_union_area |
| `rect_union_area` | area of the union of axis-parallel rectangles, O(n log n) |
| `SegTree2D` | 2D segment tree (iterative), point update |
| `DynamicSegTree` | implicit segment tree on any integer range [lo, hi) |
| `SegTreeBeats` | segment tree beats on [l, r): range chmin, chmax and add with sum, max and min queries |
| `SortableSegTree` | sequence of (key, value) pairs: point set, sort a range by key, fold a range |
| `MergeSegTree` | sparse segment trees sharing a node pool: point add, merge, split at a position, query on [l, r) |

### [`data_structures/wavelet.cpp`](data_structures/wavelet.cpp)

| Name | Description |
| --- | --- |
| `WaveletMatrix` | wavelet matrix: static order statistics on subarrays, online; values can be any integers |
| `MergeSortTree` | merge sort tree: static counting of values in a range, online |

### [`data_structures/treap.cpp`](data_structures/treap.cpp)

| Name | Description |
| --- | --- |
| `ImplicitTreap` | implicit treap over a lazy spec: insert/erase anywhere, range update, reverse and fold |
| `IndexedSet` | set with order statistics: s.find_by_order(k) (0-indexed iterator) |

### [`data_structures/offline.cpp`](data_structures/offline.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `hilbert_order` | position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow) |
| `mo` | Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r) |
| `range_inversions` | number of inversions in each a[l, r), using mo above and a Fenwick tree |
| `binomial_prefix_sums` | sum of C(n, i) over i <= k for each query {n, k}, Mo's algorithm on the points (n, k) |
| `cdq_dominance` | offline 2D dominance sums with point updates (CDQ divide and conquer), O(n log^2 n) |
| `mo_updates` | Mo's algorithm with point updates; queries are {l, r, t} over [l, r) after t updates, O(n^(5/3)) |
| `mo_tree` | Mo's algorithm on tree paths; queries are {u, v}, over the vertices of the path u - v |

### [`data_structures/misc.cpp`](data_structures/misc.cpp)

| Name | Description |
| --- | --- |
| `Compressor` | coordinate compression |
| `MinStack` | stack with minimum query |
| `MinQueue` | queue with minimum query |
| `FoldDeque` | deque with the fold of a monoid over all its elements in order (two stacks) |
| `PersistentQueue` | persistent queue: every push and pop makes a new version, O(1) memory per push |
| `MisofTree` | multiset of integers in [0, 2^BITS) |
| `RangeMode` | static range mode, online: a mode of a[l, r) and its count (sqrt decomposition), O(sqrt n) per query |
| `IntervalMap` | interval map (Chtholly tree): assign a value on [l, r) and iterate over the runs, O(log runs) amortized |

### [`data_structures/monoids.cpp`](data_structures/monoids.cpp)

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
| `Rev` | any monoid with op reversed: folds a range right to left |
| `NoUpdate` | any monoid as a lazy spec with no updates (for LazySegTree, ImplicitTreap) |
| `AddMin` | range add, range min (AddMax: range max) |
| `AddMinCount` | range add, range min with count (area of a union of rectangles) |
| `SetAdd` | range assign and range add, range sum / min / max |
| `AffineSum` | range x -> ax + b, range sum |
| `AddSumSq` | range add, range sum and sum of squares |
| `PolyAddSum` | range add of a degree-K polynomial in the index, range sum |
| `XorSum` | range xor, range sum |
| `BitRuns` | range assign / flip on a 0-1 array, count of ones and longest run |
| `SetMaxSub` | range assign, maximum subarray sum |

### [`data_structures/persistent_segment_tree.cpp`](data_structures/persistent_segment_tree.cpp)

| Name | Description |
| --- | --- |
| `Monoid` | example monoid (sum) for PersistentSegTree |
| `PersistentSegTree` | persistent segment tree, point update, query on [l, r) |
| `Spec` | example lazy spec (range add, range sum) for PersistentLazySegTree |
| `PersistentLazySegTree` | persistent lazy segment tree, range update and query on [l, r) |
| `LeqCounter` | counts and sums the values <= x in any subarray, online; values can be any integers |
| `UniqueCounter` | counts distinct values in any subarray, online; uses LeqCounter above |

## Graphs

### [`graphs/shortest_paths.cpp`](graphs/shortest_paths.cpp)

| Name | Description |
| --- | --- |
| `topo_sort` | Kahn's algorithm, O(V + E); returns vertices in topological order |
| `BellmanFord` | single-source shortest paths, negative weights allowed |
| `FloydWarshall` | all-pairs shortest paths; adj[i][j] = weight, 0 means no edge |
| `Dijkstra` | single-source shortest paths, non-negative weights only |
| `zero_one_bfs` | shortest paths from s when every edge weight is 0 or 1 (0-1 BFS), INF if unreachable |
| `min_mean_cycle` | smallest average edge weight over all directed cycles (Karp) |

### [`graphs/scc.cpp`](graphs/scc.cpp)

| Name | Description |
| --- | --- |
| `SCC` | strongly connected components (Tarjan, iterative so deep graphs can't overflow the stack), 0-indexed |
| `TwoSat` | 2-SAT, uses SCC above |
| `complement_components` | connected components of the complement of a simple graph, O(n + m) |

### [`graphs/biconnected.cpp`](graphs/biconnected.cpp)

| Name | Description |
| --- | --- |
| `Biconnected` | bridges, articulation points and biconnected components of an undirected graph |

### [`graphs/euler.cpp`](graphs/euler.cpp)

| Name | Description |
| --- | --- |
| `euler_directed` | Euler path/cycle in a directed graph, as {vertices, edge ids} |
| `euler_undirected` | Euler path/cycle in an undirected graph, as {vertices, edge ids} |

### [`graphs/spanning_trees.cpp`](graphs/spanning_trees.cpp)

| Name | Description |
| --- | --- |
| `kruskal` | minimum spanning forest (Kruskal), edges are {w, u, v} |
| `Arborescence` | minimum spanning arborescence (Chu-Liu/Edmonds) |
| `manhattan_mst_edges` | at most 4n candidate edges {w, i, j} containing a Manhattan MST; pass them to kruskal |

### [`graphs/dominator_tree.cpp`](graphs/dominator_tree.cpp)

| Name | Description |
| --- | --- |
| `dominator_tree` | dominator tree of a directed graph from root (Lengauer-Tarjan), O(E log V) |

### [`graphs/np_hard.cpp`](graphs/np_hard.cpp)

| Name | Description |
| --- | --- |
| `MaxClique` | cliques in a graph on at most N vertices, exponential in the worst case |
| `chromatic_number` | fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets) |
| `steiner_tree` | cheapest connected subgraph containing all terminals (Steiner tree), as {weight, edge ids} |

### [`graphs/k_shortest_paths.cpp`](graphs/k_shortest_paths.cpp)

| Name | Description |
| --- | --- |
| `KShortestWalks` | k shortest walks from s to t (Eppstein with a persistent leftist heap) |
| `SimplePaths` | k shortest simple paths from s to t (Yen's algorithm): no vertex repeats |

### [`graphs/flows.cpp`](graphs/flows.cpp)

| Name | Description |
| --- | --- |
| `Flow` | Dinic's algorithm, O(V^2 E) |
| `GomoryHu` | all-pairs max flow on an undirected graph (Gomory-Hu tree), uses Flow above |

### [`graphs/min_cost_flow.cpp`](graphs/min_cost_flow.cpp)

| Name | Description |
| --- | --- |
| `MinCostFlow` | min cost max flow (successive shortest paths with potentials); negative costs are fine |

### [`graphs/matching.cpp`](graphs/matching.cpp)

| Name | Description |
| --- | --- |
| `HopcroftKarp` | maximum bipartite matching (Hopcroft-Karp); left vertices 0..n-1, right vertices 0..m-1 |
| `hungarian` | minimum cost assignment (Hungarian) of every row to a distinct column |
| `Blossom` | maximum matching in a general graph (Edmonds' blossom) |
| `WeightedBlossom` | maximum weight matching in a general graph (Edmonds' blossom with dual variables), O(n^3) |
| `stable_marriage` | stable marriage (Gale-Shapley), O(n^2): men[i] and women[i] are preference lists |
| `matroid_intersection` | largest common independent set of two matroids given by oracles, O(r n^2) oracle calls |
| `GraphicMatroid` | forests of a graph, as a matroid for matroid_intersection |
| `ColorMatroid` | at most cap[c] elements of each color c (partition matroid), for matroid_intersection |

### [`graphs/trees.cpp`](graphs/trees.cpp)

| Name | Description |
| --- | --- |
| `BinaryLift` | binary lifting on a rooted tree, 0-indexed |
| `LCA` | lowest common ancestor with O(1) queries (sparse table over DFS order), 0-indexed |
| `HLD` | heavy-light decomposition, 0-indexed |
| `CentroidDecomp` | centroid decomposition, 0-indexed; example use: nearest painted vertex |
| `TreeCanon` | tree isomorphism by canonical ids (AHU); compare ids from the same TreeCanon object |
| `tree_diameter` | diameter of a weighted tree; returns {length, path} |
| `dsu_on_tree` | small-to-large on a tree (DSU on tree / sack) |
| `virtual_tree` | virtual tree of the vertices vs, using LCA above; returns {nodes, par} |
| `cartesian_tree` | parent of each index in the Cartesian tree of a (minimum at the root), -1 for the root |
| `tree_distance_counts` | cnt[d] = number of unordered pairs of vertices at distance d, O(n log^2 n); uses multiply (FFT) |

### [`graphs/rerooting.cpp`](graphs/rerooting.cpp)

| Name | Description |
| --- | --- |
| `SumDist` | rerooting DP example: sum of distances from each vertex to all others |
| `rerooting` | answer of a tree DP for every choice of root; returns ans[v] for each v |
| `MaxDist` | rerooting example: distance to the farthest vertex, weighted edges (merge with no inverse) |
| `PathComposite` | rerooting example: sum over all paths of edge maps b x + c applied to vertex values |

### [`graphs/link_cut_tree.cpp`](graphs/link_cut_tree.cpp)

| Name | Description |
| --- | --- |
| `LinkCutTree` | link-cut tree: a forest under link and cut with path and subtree sum queries, 0-indexed |
| `LinkCutPath` | link-cut tree with path folds of any monoid (op need not commute), 0-indexed |

### [`graphs/euler_tour_tree.cpp`](graphs/euler_tour_tree.cpp)

| Name | Description |
| --- | --- |
| `EulerTourTree` | a forest under link and cut, with component sums and subtree add / subtree sum, 0-indexed |

### [`graphs/cycles.cpp`](graphs/cycles.cpp)

| Name | Description |
| --- | --- |
| `directed_cycle` | edge ids of some directed cycle in order, empty if the graph is acyclic |
| `undirected_cycle` | some cycle of an undirected multigraph as {vertices, edge ids}, both empty if it is a forest |
| `FunctionalGraph` | cycles, tails and depths of v -> f[v]; f^k(v) and the distance from u to v, O(log n) |

### [`graphs/triangles.cpp`](graphs/triangles.cpp)

| Name | Description |
| --- | --- |
| `enumerate_triangles` | calls f(a, b, c) once for every triangle of a simple undirected graph, O(E sqrt E) |

## Strings

### [`strings/strings.cpp`](strings/strings.cpp)

| Name | Description |
| --- | --- |
| `prefix_function` | prefix function, O(n) |
| `kmp` | start indices of all occurrences of f in s, O(\|s\| + \|f\|) |
| `Booth` | Booth's algorithm for the lexicographically smallest rotation in O(n) |
| `z_function` | Z function, O(n): z[i] = length of the longest common prefix of s and s[i..]; z[0] = n |
| `Trie` | trie over sequences of any comparable type, L = sequence length |
| `PersistentXorTrie` | persistent binary trie |
| `XorTrie` | binary trie over a multiset: insert, erase, min and max xor |
| `SuffixArray` | suffix array and LCP array |
| `longest_common_substring` | {i, j, len}: a longest common substring s.substr(i, len) == t.substr(j, len), O(n log n) |
| `AhoCorasick` | Aho-Corasick automaton: KMP for many patterns over the alphabet [BASE, BASE + ALPHA) |
| `Eertree` | palindromic tree (eertree) over lowercase letters |
| `RollingHash` | polynomial rolling hash mod 2^61 - 1 with a random base |
| `manacher` | Manacher's algorithm, O(n); returns {d1, d2} |
| `SuffixAutomaton` | suffix automaton over lowercase letters |
| `lyndon_factorization` | Lyndon factorization (Duval): boundaries of the factors, which are nonincreasing Lyndon words, O(n) |

## Math

### [`math/modint.cpp`](math/modint.cpp)

| Name | Description |
| --- | --- |
| `ModInt` | modular integer with a compile-time modulus |

### [`math/number_theory.cpp`](math/number_theory.cpp)

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
| `count_primes` | number of primes <= n (Lucy_Hedgehog), n up to about 1e11, O(n^(3/4)) |
| `totient_sum` | sum of phi(i) for i in [1, n] mod mod, n up to about 1e11, O(n^(2/3)) |
| `gaussian_gcd` | a gcd of two Gaussian integers {re, im} (unique up to units), O(log) |
| `two_square_sum` | all pairs (a, b) of integers >= 0 with a^2 + b^2 = n, n up to ~1e18; uses factorize, gaussian_gcd |
| `sb_path` | Stern-Brocot path from 1/1 to a/b as runs {'L' or 'R', length}, O(log) |
| `sb_bounds` | bounds {p, q, r, s} of the Stern-Brocot node reached by a path: its descendants lie strictly between p/q and r/s |
| `sb_lca` | lowest common ancestor of a/b and c/d in the Stern-Brocot tree, O(log) |
| `sb_ancestor` | ancestor of a/b at depth k in the Stern-Brocot tree (1/1 has depth 0), {-1, -1} if none, O(log) |
| `rational_approx` | closest fractions <= x/y and >= x/y with numerator and denominator in [1, n], O(log) |
| `multiplicative_sum` | sum of a multiplicative f over [1, n] mod any mod below ~3e9 (Min_25 sieve), f(p) a polynomial, n up to ~1e12 |
| `isqrt` | floor(sqrt(n)) for n >= 0, O(1) |
| `sqrt_cf` | continued fraction of sqrt(D): {a0, period}, O(period) |
| `pell` | fundamental solution of x^2 - D y^2 = 1 (or -1) from the continued fraction of sqrt(D), O(period) |
| `pell_general` | all solutions of x^2 - D y^2 = N with 0 <= x <= limit (Lagrange-Matthews-Mollin); uses pell |
| `carmichael` | Carmichael function lambda(n), the largest multiplicative order mod n; uses factorize |
| `mult_order` | multiplicative order of a mod n, -1 if gcd(a, n) != 1; uses carmichael, factorize |
| `segmented_sieve` | calls f(p) for every prime p in [L, R], R up to ~1e12, O((R - L) log log R + sqrt(R)) |
| `floor_blocks` | calls f(q, l, r) for each block [l, r] of i with floor(n / i) = q, O(sqrt(n)) |
| `DuSieve` | Du's sieve: prefix sums of f at every n / i from easy prefix sums of g and f * g, O(n^(2/3)) |
| `mertens` | Mertens function M(x) at every x = n / i, n up to ~1e11, as a DuSieve, O(n^(2/3)) |
| `powerful_sum` | sum of a multiplicative f over [1, n] by the powerful number trick, O(sqrt(n)) calls of G |
| `smooth_numbers` | all B-smooth numbers in [1, n], sorted |
| `multiplicative_sieve` | f(0..n) of any multiplicative f from f(p^k) (linear sieve), O(n) |
| `pythagorean_triples` | calls f(a, b, c) for every (or every primitive) Pythagorean triple with c <= n (Euclid) |
| `hensel_roots` | all roots of a polynomial mod p^k (Hensel lifting, singular roots included) |
| `lattice_circle` | number of integer points with x^2 + y^2 <= n, O(sqrt(n)) |
| `r2` | number of ways to write n as x^2 + y^2 over the integers; uses factorize |

### [`math/combinatorics.cpp`](math/combinatorics.cpp)

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
| `derangements` | derangements (Montmort numbers) d[0..n] mod any mod, O(n) |
| `distinct_subsequences` | number of distinct non-empty subsequences of a sequence mod mod, O(n log n) |

### [`math/matrix.cpp`](math/matrix.cpp)

| Name | Description |
| --- | --- |
| `Matrix` | dense matrix with entries mod MOD |

### [`math/linear_algebra.cpp`](math/linear_algebra.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `gauss_jordan` | reduces a to reduced row echelon form using its first cols columns, returns the rank |
| `solve_linear` | solves A x = b; free variables are set to 0; returns false if there is no solution |
| `gauss_jordan_mod` | reduces a to reduced row echelon form mod a prime p < 2^31 using its first cols columns |
| `solve_linear_mod` | solves A x = b mod a prime p < 2^31; free variables are set to 0; also a basis of A x = 0 |
| `inverse_mod` | inverse of a square matrix mod a prime p < 2^31; returns false if it is singular, O(n^3) |
| `solve_xor` | solves A x = b over GF(2) (XOR equations) with m <= N variables |
| `det_mod` | determinant of a square matrix mod a prime, O(n^3) |
| `count_spanning_trees` | number of spanning trees of a multigraph mod a prime (Kirchhoff), O(n^3) |
| `count_spanning_trees_directed` | number of spanning arborescences rooted at r of a directed multigraph mod a prime, O(n^3) |
| `charpoly_mod` | characteristic polynomial det(xI - A) mod a prime (Hessenberg form), O(n^3) |
| `BitMatrix` | n x m matrix over GF(2) with rows packed into 64-bit words; gauss gives the RREF |
| `det_mod2` | determinant of a square matrix over GF(2), O(n^3 / 64) |
| `inverse_mod2` | inverse of a square matrix over GF(2); false if it is singular, O(n^3 / 64) |
| `solve_mod2` | solves A x = b over GF(2): one solution and a basis of A x = 0, O(n * m * rank / 64) |
| `mul_mod2` | product of an n x m and an m x l matrix over GF(2), O(n * m * l / 64) |
| `XorBasis` | XOR linear basis over values in [0, 2^BITS), BITS <= 62 |
| `PrefixXorBasis` | XOR basis of every prefix: online max subset XOR / membership over a[l, r) |

### [`math/fft.cpp`](math/fft.cpp)

| Name | Description |
| --- | --- |
| `fft` | in-place FFT (inverse FFT if invert, including the 1/n scaling) |
| `multiply` | product of integer polynomials a and b, O((n + m) log(n + m)) |
| `binexp` | a^b mod mod, O(log b) |
| `NTT` | number theoretic transform, each MOD and ROOT pair is its own type |
| `garner` | combine residues mod several primes into the value mod `mod` (0 means mod 2^64) |
| `convolution_any_mod` | product of polynomials a and b mod any modulus below 2^31 |
| `convolution_mod_2_64` | product of polynomials a and b mod 2^64 |
| `wildcard_match` | res[i] = 1 if s[i, i + \|t\|) matches t, where `wild` matches any character |

### [`math/polynomial.cpp`](math/polynomial.cpp)

| Name | Description |
| --- | --- |
| `binexp` | a^b mod mod, O(log b) |
| `mod_sqrt` | a square root of a mod the prime p, -1 if none (copy of the Number Theory one) |
| `NTT` | number theoretic transform, each MOD and ROOT pair is its own type |
| `Poly` | polynomial operations mod MOD, using NTT above; a[i] is the coefficient of x^i |
| `poly_prod` | product f[0] * f[1] * ... * f[k - 1] mod MOD, divide and conquer, O(N log N log k) |
| `poly_divide_real` | long division of real polynomials: returns {quotient, remainder} of a / b |
| `berlekamp_massey` | shortest linear recurrence of s mod a prime (Berlekamp-Massey), O(n^2) |
| `kth_term` | k-th term (0-indexed) of the recurrence s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ..., mod a modulus below 2^31 |
| `kth_term_ntt` | k-th term of a linear recurrence mod an NTT prime (Bostan-Mori), O(d log d log k) |
| `bernoulli_ntt` | Bernoulli numbers B[0..n] mod an NTT prime, with B[1] = -1/2, O(n log n) |
| `bell_ntt` | Bell numbers B[0..n] mod an NTT prime, as exp(e^x - 1), O(n log n) |
| `taylor_shift` | a(x + c) mod MOD (Taylor shift), O(n log n) |
| `stirling1_ntt` | signed Stirling numbers of the first kind s(n, k), k = 0..n, mod an NTT prime, O(n log n) |
| `stirling2_ntt` | Stirling numbers of the second kind S(n, k), k = 0..n, mod an NTT prime, O(n log n) |
| `partition_ntt` | partition numbers p(0..n) mod an NTT prime, O(n log n) |
| `subset_sum_counts` | number of sub-multisets of s with each sum t = 0..T, mod an NTT prime, O(\|s\| + T log T) |
| `shift_samples` | h(a), ..., h(a + m - 1) from h(0), ..., h(n - 1) (shift of sampling points), O((n + m) log(n + m)) |
| `FactorialMod` | n! mod an NTT prime for any n < MOD, block table of (iV)!, O(V) per query |
| `lagrange` | value at x of the unique polynomial through (xs[i], ys[i]) |
| `lagrange_consecutive` | value at x of the unique polynomial with p(i) = ys[i] for i = 0..n-1 |
| `sum_exp_poly` | sum of r^i i^d over 0 <= i < n, or over all i >= 0 (n = -1, r != 1), O(d + (d / log d) log mod) |

### [`math/bitmask.cpp`](math/bitmask.cpp)

| Name | Description |
| --- | --- |
| `sos_subset` | SOS DP: a[mask] becomes the sum of a[sub] over all submasks sub of mask (undone if invert), O(n log n) |
| `sos_superset` | SOS DP: a[mask] becomes the sum of a[sup] over all supermasks sup of mask (undone if invert), O(n log n) |
| `xor_transform` | Walsh-Hadamard transform (inverse if invert, including the 1/n scaling), O(n log n) |
| `pad_to_power` | pads a and b with zeros to a common power of 2 length (at least 1), O(n) |
| `or_convolution` | c[k] = sum of a[i] * b[j] over all i \| j == k, O(n log n) |
| `and_convolution` | c[k] = sum of a[i] * b[j] over all i & j == k, O(n log n) |
| `xor_convolution` | c[k] = sum of a[i] * b[j] over all i ^ j == k, O(n log n) |
| `ranked_zeta` | ranked zeta transform for the subset convolution family (undone if invert), O(n^2 2^n) |
| `subset_convolution` | c[k] = sum of a[i] * b[j] over i \| j == k and i & j == 0, mod a prime, O(n^2 2^n) |
| `subset_exp` | exp of a set power series: sum over partitions of s of the product of a over the blocks, O(n^2 2^n) |
| `subset_log` | log of a set power series, the inverse of subset_exp, O(n^2 2^n) |

### [`math/big_integer.cpp`](math/big_integer.cpp)

| Name | Description |
| --- | --- |
| `BigInt` | arbitrary-precision signed integer in base 1e9 limbs |

### [`math/hex_big_integer.cpp`](math/hex_big_integer.cpp)

| Name | Description |
| --- | --- |
| `HexBigInt` | arbitrary-precision signed hex integer in base 2^28 limbs (7 hex digits each) |

### [`math/int128.cpp`](math/int128.cpp)

| Name | Description |
| --- | --- |
| `to_string128` | decimal string of an __int128 (or unsigned __int128) |
| `parse128` | __int128 from a decimal string with an optional sign |
| `operator<<` | print __int128 and unsigned __int128 with cout or any ostream |
| `operator>>` | read __int128 with cin or any istream |
| `gcd128` | gcd of two __int128 (std::gcd needs gnu++ mode for __int128) |
| `Frac` | exact fraction with __int128 numerator and denominator, always reduced |
| `mulmod` | a * b mod m for m up to ~7.2e18 without __int128 (long double quotient), O(1) |
| `powmod` | a^e mod m for m up to ~7.2e18, using mulmod, O(log e) |

### [`math/simplex.cpp`](math/simplex.cpp)

| Name | Description |
| --- | --- |
| `Simplex` | two-phase simplex: maximize c^T x subject to A x <= b, x >= 0; A is m x n |

## Geometry

### [`geometry/geometry.cpp`](geometry/geometry.cpp)

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
| `seg_intersect` | true if the closed segments ab and cd share a point (touching and collinear overlap count), O(1) |
| `seg_seg_dist` | distance between the segments ab and cd, 0 if they intersect, O(1) |
| `circle_line_inter` | intersection points of the circle (c, r) and the line ab: 0, 1 (tangent), or 2 points |
| `circle_circle_inter` | intersection points of circles (c1, r1) and (c2, r2): 0, 1 (tangent), or 2 points |
| `tangent_points` | points where the tangent lines from p touch the circle (c, r): 0, 1, or 2 points, O(1) |
| `circle_tangents` | common tangent lines of two circles, each as its two touching points, O(1) |
| `circle_polygon_area` | area of the intersection of a circle and a simple polygon, O(n) |
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
| `any_seg_inter` | two segments that intersect, or {-1, -1} if no two do (Shamos-Hoey sweep), O(n log n) |
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
| `circle_union_area` | area of the union of circles {center, radius}, O(n^2 log n) |
| `delaunay_edges` | Delaunay triangulation edges of integer points (they contain a Euclidean MST), O(n log n) |
| `TriangleCounter` | number of points strictly inside triangles of given points, O(n^2 m) build, O(1) per query |

## DP and Search

### [`dp_search/binary_ternary_search.cpp`](dp_search/binary_ternary_search.cpp)

| Name | Description |
| --- | --- |
| `ternary_search_int` | smallest x in [lo, hi] minimizing f, O(log(hi - lo)) calls to f; f must fall, then rise |
| `ternary_search_real` | x in [lo, hi] minimizing a real function that falls and then rises, O(iters) calls to f |
| `parallel_binary_search` | for each query, the first step count after which check(i) holds, O(log steps) replays |
| `brent` | a root of f in [a, b] with f(a), f(b) of opposite signs (Brent's method) |

### [`dp_search/dp_optimizations.cpp`](dp_search/dp_optimizations.cpp)

| Name | Description |
| --- | --- |
| `LineContainer` | dynamic convex hull trick: add lines in any order, query at any x |
| `LiChao` | Li Chao tree on integer x in [lo, hi] |
| `PersistentLiChao` | persistent Li Chao tree for minimum queries on integer x in [lo, hi] |
| `dnc_opt` | divide and conquer DP optimization |
| `knuth_opt` | Knuth optimization, O(n^2) |
| `min_plus_convex_convex` | c[k] = min of a[i] + b[j] over i + j = k for convex a and b (merge of slopes), O(n + m) |
| `min_plus_convex_arbitrary` | c[k] = min of a[i] + b[j] over i + j = k for convex a and any b (monotone minima), O((n + m) log(n + m)) |
| `min_plus_concave_arbitrary` | c[k] = min of a[i] + b[j] over i + j = k for concave a and any b, O((n + m) log^2 (n + m)) |
| `SlopeTrick` | convex piecewise linear function: add \|x - a\| and ramps, prefix / suffix min, shift, merge |
| `aliens` | Aliens trick (WQS binary search): min cost with exactly k items for a cost convex in k |

### [`dp_search/digit_dp.cpp`](dp_search/digit_dp.cpp)

| Name | Description |
| --- | --- |
| `digit_dp_simple` | copy-and-edit digit DP: how many x in [0, n] have digit sum divisible by K, O(len * K * 10) |
| `digits_of` | base-b digits of n >= 0, most significant first (empty for 0), O(log n) |
| `digit_dp` | sum of acc(state) over every x in [0, n], where state comes from feeding x's digits to step |

## Miscellaneous

### [`misc/sat.cpp`](misc/sat.cpp)

| Name | Description |
| --- | --- |
| `SAT` | SAT solver (DPLL with watched literals); variables are 1..n, literal -x means "not x" |

### [`misc/dlx.cpp`](misc/dlx.cpp)

| Name | Description |
| --- | --- |
| `DLX` | exact cover with dancing links (Algorithm X) |

### [`misc/misc.cpp`](misc/misc.cpp)

| Name | Description |
| --- | --- |
| `find_cycle` | Floyd's cycle finding on x0, f(x0), f(f(x0)), ...: returns {mu, lambda} (tail length, cycle length), O(mu + lambda) |
| `lis` | indices of a longest strictly increasing subsequence of a, O(n log n) |
| `date_to_int` | day number (Julian day) of a Gregorian date, O(1) |
| `int_to_date` | Gregorian date of a day number, O(1) |
| `int_to_day` | day of the week of a day number, 0 = Monday, O(1) |
| `cur_time` | current CPU time in seconds, O(1) |
| `simulated_annealing` | simulated annealing example |
| `read_int` | reads the next integer from stdin into x, false at end of input, O(digits) |
| `next_bit_perm` | next larger integer with the same number of set bits; requires x > 0, O(1) |
| `is_square` | true if x is a perfect square, O(1) |
| `simpson` | numeric integral of f over [a, b] by Simpson's rule, O(steps); steps must be even |
| `mex` | mex of a list of non-negative integers, O(k) |
| `grundy` | Sprague-Grundy values of every position of a finite acyclic game, O(V + E) |
| `grundy_line` | Grundy values g[0..n] of a game on integers whose moves go down, from the options' values |
