# Team Notebook

A printable team reference document (ICPC-style) generated from [`cpp_templates/`](../cpp_templates):
landscape, three columns, with an index of every struct and function on the first page.

- `notebook.pdf`: the built notebook
- `build.py`: generator, with the settings at the top (team name, paper size, page limit, which templates go in and in what order)
- `notebook_template.tex`: page layout
- `content/contest.tex`: compile commands, pragmas, complexity guide, debugging checklist
- `content/theory.tex`: formulas and facts (useful primes, combinatorics, number theory, graph theory, games, geometry)

## Building

Needs Python 3 and a LaTeX distribution with `latexmk` (TeX Live or MiKTeX).

```sh
python notebook/build.py
```

Rebuild after changing a template so the notebook stays in sync. The script:

- drops each file's `#include` / `using` header lines that the contest template already prints once
- removes blank lines (set `COMPACT = False` to keep them)
- condenses the code (set `CONDENSE = False` to skip): indents by `INDENT` spaces per level instead of 4, and
  moves lines that only close braces (`}`, `};`, `});`) to the end of the line above when that fits in a column.
  Only whitespace changes, the templates themselves are untouched, and if `g++` is installed every file is
  syntax-checked before and after so a condensed file that stops compiling fails the build
- warns about templates missing from `SECTIONS` and about going over `PAGE_LIMIT`

`SECTIONS` entries are paths relative to `cpp_templates/`, whose folders match the notebook's chapters, and
each `.cpp` entry names the components it prints: `("data_structures/dsu.cpp", "DSU", ["DSU", "RollbackDSU",
"OfflineDynamic"])` prints those three with their doc comments (plus any comment-only notes in the file).
Anything not named stays out, so adding a template to `cpp_templates/` doesn't change the notebook until its
name is added to `SECTIONS`. To fit a page limit, drop names or entries from `SECTIONS` or reduce `CODE_FONT_PT`.

## Contents

The current build fits the 25-page ICPC limit. It prints exactly these, in this order (keep this table in step
with `SECTIONS`); every other template file and component is left out.

| Chapter | File | Printed |
| --- | --- | --- |
| Contest | [`new_file.cpp`](../cpp_templates/new_file.cpp) | whole file |
|  | `content/contest.tex` | whole file |
|  | [`contest/stress_gen.cpp`](../cpp_templates/contest/stress_gen.cpp) | `rng`, `rnd`, `rnd_array`, `rnd_perm`, `rnd_string`, `rnd_tree`, `rnd_graph`, `main` |
|  | [`contest/safe_hash.cpp`](../cpp_templates/contest/safe_hash.cpp) | `SafeHash`, `SafeMap`, `SafeSet` |
| Data Structures | [`data_structures/dsu.cpp`](../cpp_templates/data_structures/dsu.cpp) | `DSU`, `RollbackDSU`, `OfflineDynamic` |
|  | [`data_structures/fenwick.cpp`](../cpp_templates/data_structures/fenwick.cpp) | `Fenwick`, `RangeFenwick` |
|  | [`data_structures/sparse_table.cpp`](../cpp_templates/data_structures/sparse_table.cpp) | `MinOp`, `SparseTable`, `SparseTable2D` |
|  | [`data_structures/segment_tree.cpp`](../cpp_templates/data_structures/segment_tree.cpp) | `Monoid`, `SegTree`, `Spec`, `LazySegTree`, `SegTree2D`, `DynamicSegTree`, `SegTreeBeats` |
|  | [`data_structures/wavelet.cpp`](../cpp_templates/data_structures/wavelet.cpp) | `WaveletMatrix`, `MergeSortTree` |
|  | [`data_structures/treap.cpp`](../cpp_templates/data_structures/treap.cpp) | `ImplicitTreap`, `IndexedSet` |
|  | [`data_structures/offline.cpp`](../cpp_templates/data_structures/offline.cpp) | `hilbert_order`, `mo` |
|  | [`data_structures/misc.cpp`](../cpp_templates/data_structures/misc.cpp) | `Compressor`, `MinStack`, `MinQueue`, `MisofTree` |
| Graphs | [`graphs/shortest_paths.cpp`](../cpp_templates/graphs/shortest_paths.cpp) | `topo_sort`, `BellmanFord`, `FloydWarshall`, `Dijkstra`, `zero_one_bfs`, `min_mean_cycle` |
|  | [`graphs/scc.cpp`](../cpp_templates/graphs/scc.cpp) | `SCC`, `TwoSat` |
|  | [`graphs/biconnected.cpp`](../cpp_templates/graphs/biconnected.cpp) | `Biconnected` |
|  | [`graphs/euler.cpp`](../cpp_templates/graphs/euler.cpp) | `euler_directed`, `euler_undirected` |
|  | [`graphs/spanning_trees.cpp`](../cpp_templates/graphs/spanning_trees.cpp) | `kruskal`, `Arborescence` |
|  | [`graphs/dominator_tree.cpp`](../cpp_templates/graphs/dominator_tree.cpp) | `dominator_tree` |
|  | [`graphs/np_hard.cpp`](../cpp_templates/graphs/np_hard.cpp) | `MaxClique`, `chromatic_number`, `steiner_tree` |
|  | [`graphs/k_shortest_paths.cpp`](../cpp_templates/graphs/k_shortest_paths.cpp) | `KShortestWalks`, `SimplePaths` |
|  | [`graphs/flows.cpp`](../cpp_templates/graphs/flows.cpp) | `Flow`, `GomoryHu` |
|  | [`graphs/min_cost_flow.cpp`](../cpp_templates/graphs/min_cost_flow.cpp) | `MinCostFlow` |
|  | [`graphs/matching.cpp`](../cpp_templates/graphs/matching.cpp) | `HopcroftKarp`, `hungarian`, `Blossom`, `stable_marriage` |
|  | [`graphs/trees.cpp`](../cpp_templates/graphs/trees.cpp) | `BinaryLift`, `LCA`, `HLD`, `CentroidDecomp`, `TreeCanon`, `tree_diameter`, `dsu_on_tree`, `virtual_tree` |
|  | [`graphs/rerooting.cpp`](../cpp_templates/graphs/rerooting.cpp) | `SumDist`, `rerooting` |
|  | [`graphs/link_cut_tree.cpp`](../cpp_templates/graphs/link_cut_tree.cpp) | `LinkCutTree` |
| Strings | [`strings/strings.cpp`](../cpp_templates/strings/strings.cpp) | `prefix_function`, `kmp`, `Booth`, `z_function`, `Trie`, `PersistentXorTrie`, `SuffixArray`, `AhoCorasick`, `Eertree`, `RollingHash`, `manacher`, `SuffixAutomaton` |
| Math | [`math/modint.cpp`](../cpp_templates/math/modint.cpp) | `ModInt`, `mint` |
|  | [`math/number_theory.cpp`](../cpp_templates/math/number_theory.cpp) | `binexp`, `modinv_p`, `extended_euclidean`, `modinv`, `discrete_log`, `is_prime`, `sieve`, `sum_of_divisors`, `miller_rabin`, `mobius_sieve`, `gcd_subset_count`, `divisor_transform`, `gcd_convolution`, `totient`, `mod_solver`, `diophantine`, `crt`, `super_crt`, `josephus`, `spf_sieve`, `factorize_spf`, `pollard_rho`, `factorize`, `primitive_root`, `floor_sum`, `mod_sqrt`, `kth_root_floor`, `kth_root_mod`, `bernoulli`, `tetration`, `count_squarefree` |
|  | [`math/combinatorics.cpp`](../cpp_templates/math/combinatorics.cpp) | `binexp`, `modinv_p`, `comb`, `init_fac`, `comb_f`, `comb_m`, `factorial`, `lucas`, `CombAny`, `OrderTree`, `perm_to_factoradic`, `factoradic_to_perm`, `kth_permutation` |
|  | [`math/matrix.cpp`](../cpp_templates/math/matrix.cpp) | `Matrix` |
|  | [`math/linear_algebra.cpp`](../cpp_templates/math/linear_algebra.cpp) | `binexp`, `gauss_jordan`, `solve_linear`, `det_mod`, `count_spanning_trees`, `XorBasis` |
|  | [`math/fft.cpp`](../cpp_templates/math/fft.cpp) | `fft`, `multiply`, `binexp`, `NTT`, `garner`, `convolution_any_mod`, `convolution_mod_2_64` |
|  | [`math/polynomial.cpp`](../cpp_templates/math/polynomial.cpp) | `binexp`, `NTT`, `Poly`, `poly_divide_real`, `berlekamp_massey`, `kth_term`, `kth_term_ntt`, `bernoulli_ntt`, `bell_ntt`, `shift_samples`, `FactorialMod`, `lagrange`, `lagrange_consecutive` |
|  | [`math/bitmask.cpp`](../cpp_templates/math/bitmask.cpp) | `sos_subset`, `sos_superset`, `xor_transform`, `pad_to_power`, `or_convolution`, `and_convolution`, `xor_convolution` |
| Geometry | [`geometry/geometry.cpp`](../cpp_templates/geometry/geometry.cpp) | `Point`, `dot`, `cross`, `norm`, `abs`, `dist`, `angle`, `rotate`, `proj_line`, `proj_seg`, `dist_pt_line`, `line_inter`, `circle_line_inter`, `circle_circle_inter`, `polygon_area`, `triangle_area`, `cyclic_quad_area`, `polygon_centroid`, `convex_hull`, `on_polygon`, `in_polygon`, `cut_polygon`, `bary`, `trilinear`, `centroid`, `circumcenter`, `orthocenter`, `incenter`, `inradius`, `excenter`, `brocard`, `symmedian`, `convex_polygon_inter`, `lattice_boundary`, `lattice_interior`, `min_enclosing_circle`, `furthest_pair`, `polygon_width`, `closest_pair`, `KDTree`, `Point3`, `proj_plane`, `dist_pt_plane`, `dist_line_3d`, `great_circle_dist`, `great_circle_angle`, `Point3I`, `Face`, `convex_hull_3d`, `in_convex`, `sort_by_angle`, `minkowski_sum`, `half_plane_intersection`, `polygon_union_area` |
| DP and Search | [`dp_search/binary_ternary_search.cpp`](../cpp_templates/dp_search/binary_ternary_search.cpp) | `ternary_search_int`, `ternary_search_real`, `main` |
|  | [`dp_search/dp_optimizations.cpp`](../cpp_templates/dp_search/dp_optimizations.cpp) | `LineContainer`, `LiChao`, `PersistentLiChao`, `dnc_opt`, `knuth_opt` |
| Miscellaneous | [`misc/sat.cpp`](../cpp_templates/misc/sat.cpp) | `SAT` |
| Theory | `content/theory.tex` | whole file |
