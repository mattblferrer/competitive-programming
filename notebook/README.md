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

To fit a page limit, remove entries from `SECTIONS` or reduce `CODE_FONT_PT`. To print only part of a
file, list the names to keep: `("misc.cpp", "SAT Solver", ["SAT"])` keeps just the `SAT` struct and
its doc comment.

The current build fits the 25-page ICPC limit. It leaves out `big_integer.cpp`, `hex_big_integer.cpp`,
`persistent_segment_tree.cpp`, and everything in `misc.cpp` except the SAT solver.
