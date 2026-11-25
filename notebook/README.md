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

`SECTIONS` entries are paths relative to `cpp_templates/`, whose folders match the notebook's chapters.
To fit a page limit, remove entries from `SECTIONS` or reduce `CODE_FONT_PT`. To print only part of a
file, list the names to keep: `("data_structures/dsu.cpp", "DSU", ["DSU", "RollbackDSU", "OfflineDynamic"])`
keeps just those three components and their doc comments, and `["-name", ...]` keeps everything except those.

The current build fits the 25-page ICPC limit. It leaves out `math/big_integer.cpp`, `math/hex_big_integer.cpp`,
`math/simplex.cpp`, `data_structures/monoids.cpp`, `data_structures/persistent_segment_tree.cpp`, `misc/dlx.cpp`,
`misc/misc.cpp`, `graphs/euler_tour_tree.cpp`, `graphs/cycles.cpp`, `graphs/triangles.cpp`, the modular solvers in
`math/linear_algebra.cpp`, the copy of `mod_sqrt` in `math/polynomial.cpp` (Number Theory prints it), the extra
rerooting examples (`MaxDist`, `PathComposite`), and `SumDSU`, `PotentialDSU`, `FoldDeque`, `Fenwick2D`,
`count_primes`, `subset_convolution`, `cartesian_tree`, `manhattan_mst_edges`, `range_inversions`,
`tree_distance_counts`, `totient_sum`, `wildcard_match`,
`gaussian_gcd`, `two_square_sum`, `sb_path`, `sb_bounds`, `sb_lca`, `sb_ancestor`,
`rational_approx`, `lyndon_factorization`,
`min_plus_convex_convex`, `min_plus_convex_arbitrary`, `min_plus_concave_arbitrary`,
`complement_components` and `multiplicative_sum`.
