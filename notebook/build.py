"""Build the team notebook PDF from cpp_templates/ and the hand-written pages in content/.

    python notebook/build.py            build notebook/notebook.pdf
    python notebook/build.py --tex      only write notebook/build/notebook.tex

Requires pdflatex + latexmk (TeX Live / MiKTeX). Edit the settings below to change the
team name, paper size, page limit, or which templates go in and in what order.
"""

import re
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

# ---------------------------------------------------------------- settings
TEAM_NAME = "Team Notebook"
SUBTITLE = "github.com/mattblferrer/competitive-programming"
PAPER = "a4paper"  # or "letterpaper"
PAGE_LIMIT = 25  # ICPC regionals usually allow 25 single-sided pages
CODE_FONT_PT = (6.1, 6.6)  # font size, line spacing for code
COMPACT = True  # drop blank lines from the code (the template keeps its own)
CONDENSE = True  # put lines that only close braces ("}", "};", "});") at the end of the line above
INDENT = 2  # spaces per indent level in the printed code (the templates use 4); None keeps 4

# (section title, [entries]); an entry is a .cpp path relative to cpp_templates/ (whose folders match these
# chapters) or a .tex in content/, either bare or as (file, title). A .cpp entry can also be (file, title, [names])
# to print only the components (structs/functions with their doc comments) that define those names, or
# ["-name", ...] to print every component except those.
# Templates not listed here are reported, not included.
SECTIONS = [
    ("Contest", [
        ("new_file.cpp", "Template"),
        ("contest.tex", "Commands and Checklist"),
        ("contest/stress_gen.cpp", "Stress Test Generator"),
        ("contest/safe_hash.cpp", "Safe Hash"),
    ]),
    ("Data Structures", [
        ("data_structures/dsu.cpp", "DSU", ["DSU", "RollbackDSU", "OfflineDynamic"]),
        ("data_structures/fenwick.cpp", "Fenwick Trees", ["-Fenwick2D", "-rect_add_rect_sum"]),
        ("data_structures/sparse_table.cpp", "Sparse Tables"),
        ("data_structures/segment_tree.cpp", "Segment Trees", ["-MinCount", "-AddMinCount", "-rect_union_area",
                                                                "-SortableSegTree"]),
        ("data_structures/wavelet.cpp", "Wavelet Matrix and Merge Sort Tree"),
        ("data_structures/treap.cpp", "Treap and Ordered Set"),
        ("data_structures/offline.cpp", "Mo's Algorithm", ["-range_inversions"]),
        ("data_structures/misc.cpp", "Other Structures", ["-FoldDeque", "-RangeMode"]),
    ]),
    ("Graphs", [
        ("graphs/shortest_paths.cpp", "Topological Sort and Shortest Paths"),
        ("graphs/scc.cpp", "SCC and 2-SAT", ["-complement_components"]),
        ("graphs/biconnected.cpp", "Biconnected Components"),
        ("graphs/euler.cpp", "Euler Paths"),
        ("graphs/spanning_trees.cpp", "Spanning Trees", ["-manhattan_mst_edges"]),
        ("graphs/dominator_tree.cpp", "Dominator Tree"),
        ("graphs/np_hard.cpp", "Cliques, Coloring and Steiner Tree"),
        ("graphs/k_shortest_paths.cpp", "K Shortest Paths"),
        ("graphs/flows.cpp", "Max Flow"),
        ("graphs/min_cost_flow.cpp", "Min-Cost Flow"),
        ("graphs/matching.cpp", "Matching", ["-WeightedBlossom"]),
        ("graphs/trees.cpp", "Trees", ["-cartesian_tree", "-tree_distance_counts"]),
        ("graphs/rerooting.cpp", "Rerooting", ["SumDist", "rerooting"]),  # MaxDist, PathComposite: more examples
        ("graphs/link_cut_tree.cpp", "Link-Cut Tree", ["-LinkCutPath"]),
    ]),
    ("Strings", [
        ("strings/strings.cpp", "Strings", ["-lyndon_factorization", "-XorTrie", "-longest_common_substring"]),
    ]),
    ("Math", [
        ("math/modint.cpp", "ModInt"),
        ("math/number_theory.cpp", "Number Theory", ["-count_primes", "-totient_sum", "-gaussian_gcd", "-two_square_sum",
                                                     "-sb_path", "-sb_bounds", "-sb_lca", "-sb_ancestor", "-rational_approx",
                                                     "-multiplicative_sum"]),
        ("math/combinatorics.cpp", "Combinatorics", ["-derangements", "-distinct_subsequences"]),
        ("math/matrix.cpp", "Matrix"),
        ("math/linear_algebra.cpp", "Linear Algebra", ["binexp", "gauss_jordan", "solve_linear", "det_mod",
                                                       "count_spanning_trees", "XorBasis"]),
        ("math/fft.cpp", "FFT / NTT", ["-wildcard_match"]),
        ("math/polynomial.cpp", "Polynomials", ["binexp", "NTT", "Poly", "poly_divide_real", "berlekamp_massey",
                                                "kth_term", "kth_term_ntt", "bernoulli_ntt", "bell_ntt", "shift_samples",
                                                "FactorialMod", "lagrange", "lagrange_consecutive"]),  # mod_sqrt: Number Theory
        ("math/bitmask.cpp", "Bitmask Transforms", ["-ranked_zeta", "-subset_convolution", "-subset_exp",
                                                    "-subset_log"]),
    ]),
    ("Geometry", [
        ("geometry/geometry.cpp", "Geometry", ["-delaunay_edges", "-TriangleCounter"]),
    ]),
    ("DP and Search", [
        ("dp_search/binary_ternary_search.cpp", "Binary and Ternary Search"),
        ("dp_search/dp_optimizations.cpp", "DP Optimizations", ["-min_plus_convex_convex", "-min_plus_convex_arbitrary",
                                                                "-min_plus_concave_arbitrary"]),
    ]),
    ("Miscellaneous", [
        ("misc/sat.cpp", "SAT Solver"),
    ]),
    ("Theory", [
        ("theory.tex", "Formulas and Facts"),
    ]),
]
# ------------------------------------------------------------------------

ROOT = Path(__file__).resolve().parent
TEMPLATES = ROOT.parent / "cpp_templates"
CONTENT = ROOT / "content"
BUILD = ROOT / "build"
HEADER_FILE = "new_file.cpp"  # its preamble is printed once, so other files drop those lines

PREAMBLE_LINE = re.compile(r"^(#include|using |const |mt19937)|^\s*$")
TOP_LEVEL_NAME = [
    re.compile(r"^(?:struct|class)\s+(\w+)"),
    re.compile(r"^(?!return\b|else\b)[\w:<>,]+(?:<[^()]*>)?[\s*&]+(\w+)\s*\([^;]*$"),
]


def tex_escape(s):
    return "".join({"_": r"\_", "&": r"\&", "%": r"\%", "#": r"\#", "$": r"\$",
                    "{": r"\{", "}": r"\}", "~": r"\textasciitilde{}",
                    "^": r"\textasciicircum{}", "\\": r"\textbackslash{}"}.get(c, c) for c in s)


def shared_preamble():
    """Lines of the contest template that come before the first function."""
    lines = (TEMPLATES / HEADER_FILE).read_text().splitlines()
    return {l.strip() for l in lines if PREAMBLE_LINE.match(l) and l.strip()}


def strip_contents(text):
    """Drop the "// Contents" block at the top of a template (the notebook has its own index)."""
    lines = text.splitlines()
    if not lines or not lines[0].startswith("// Contents"):
        return text
    i = 0
    while i < len(lines) and lines[i].strip():
        i += 1
    while i < len(lines) and not lines[i].strip():
        i += 1
    return "\n".join(lines[i:]) + "\n"


def strip_preamble(text, shared):
    """Drop the leading #include/using/const lines that the contest template already has.

    The header region is the run of leading comment and preamble lines; anything else in it
    (a file description, an extra #include, a file-specific constant) is kept.
    """
    lines = text.splitlines()
    i = 0
    kept = []
    while i < len(lines) and (PREAMBLE_LINE.match(lines[i]) or lines[i].startswith("//")):
        if lines[i].strip() not in shared:
            kept.append(lines[i])
        i += 1
    while kept and not kept[-1].strip():
        kept.pop()
    body = lines[i:]
    if kept:
        body = kept + [""] + body
    return "\n".join(body).strip("\n") + "\n"


def keep_only(text, wanted, fname):
    """Keep the top-level blocks (a column-0 comment after a blank line starts one) that
    define any name in wanted, plus whatever comes before the first block. If every name in
    wanted starts with "-", keep every block except the ones that define those names."""
    blocks = [[]]
    prev = ""
    for line in text.splitlines():
        if line.startswith("//") and not prev.strip() and blocks[-1]:
            blocks.append([])
        blocks[-1].append(line)
        prev = line
    head, rest = blocks[0], blocks[1:]
    if head and head[0].startswith("//"):  # the file starts with a block, not a header
        head, rest = [], blocks
    if all(w.startswith("-") for w in wanted):
        drop = {w[1:] for w in wanted}
        kept = [b for b in rest if not set(top_level_names("\n".join(b))) & drop]
        found = {n for b in rest for n in top_level_names("\n".join(b))}
        missing = [n for n in drop if n not in found]
    else:
        kept = [b for b in rest if set(top_level_names("\n".join(b))) & set(wanted)]
        found = {n for b in kept for n in top_level_names("\n".join(b))}
        missing = [n for n in wanted if n not in found]
    if missing:
        sys.exit(f"error: {fname} has no top-level {', '.join(missing)} (listed in SECTIONS)")
    return "\n".join(head + [l for b in kept for l in b]).strip("\n") + "\n"


def compact(text):
    """Remove blank lines (they cost about a tenth of the pages)."""
    return "\n".join(l for l in text.splitlines() if l.strip()) + "\n"


def code_columns():
    """Characters per code line before listings wraps it, from the page layout in
    notebook_template.tex (5 mm side margins, 3 mm column gaps, 3 columns) and the code font
    (Inconsolata, 0.5 em per character)."""
    paper_mm = {"a4paper": 297, "letterpaper": 279.4}[PAPER]  # landscape width
    column_pt = (paper_mm - 2 * 5 - 2 * 3) / 3 / 25.4 * 72.27
    return int(column_pt / (0.5 * CODE_FONT_PT[0]))


CLOSERS = re.compile(r"\}[})\];,]*")  # a line that only closes: "}", "};", "});", "}}", "},"


def condense(text, width):
    """Narrow the indentation to INDENT spaces per level, and move each closing-brace-only line
    to the end of the line above when that line has no comment, is not a # directive, and stays
    within width. Only whitespace changes, which the assert checks."""
    out = []
    for line in text.splitlines():
        body = line.lstrip(" ")
        lead = len(line) - len(body)
        if INDENT is not None:
            line = " " * (lead // 4 * INDENT + lead % 4) + body
        prev = out[-1] if out else ""
        if (out and CLOSERS.fullmatch(body.rstrip()) and "//" not in prev and "/*" not in prev
                and not prev.lstrip().startswith("#") and not prev.endswith("\\")
                and len(prev) + 1 + len(body.rstrip()) <= width):
            out[-1] = prev + " " + body.rstrip()
        else:
            out.append(line)
    res = "\n".join(out) + "\n"
    assert re.sub(r"\s", "", res) == re.sub(r"\s", "", text), "condense changed more than whitespace"
    return res


def check_condensed(pairs):
    """Syntax-check each file before and after condensing (with the contest template's preamble
    in front) and fail if condensing broke one that compiled. Skipped without g++."""
    gxx = shutil.which("g++")
    if not gxx or not pairs:
        if not gxx:
            print("note: g++ not found, so condensed code was not compile-checked")
        return
    header = (TEMPLATES / HEADER_FILE).read_text()
    header = header[:header.index("#endif") + len("#endif")] + "\n"
    with tempfile.TemporaryDirectory() as tmp:
        def compiles(name, code):
            path = Path(tmp) / name
            path.write_text(header + code)
            return subprocess.run([gxx, "-std=c++20", "-fsyntax-only", str(path)],
                                  capture_output=True).returncode == 0

        jobs = [(f"{i}_{w}.cpp", code) for i, pair in enumerate(pairs) for w, code in zip("ab", pair[1:])]
        with ThreadPoolExecutor() as ex:
            ok = list(ex.map(lambda job: compiles(*job), jobs))
    broken = [fname for i, (fname, _, _) in enumerate(pairs) if ok[2 * i] and not ok[2 * i + 1]]
    if broken:
        sys.exit(f"error: condensing broke {', '.join(broken)} (compiles before, not after)")


def top_level_names(text):
    names = []
    for line in text.splitlines():
        for pat in TOP_LEVEL_NAME:
            m = pat.match(line)
            if m and m.group(1) not in ("main", "operator") and m.group(1) not in names:
                names.append(m.group(1))
                break
    return names


def label_for(name):
    return "sec:" + re.sub(r"\W", "-", name)


def build_tex():
    shared = shared_preamble()
    src_dir = BUILD / "src"
    src_dir.mkdir(parents=True, exist_ok=True)

    listed = set()
    toc = []
    body = []
    condensed = []  # (file name, code before, code after)
    width = code_columns()
    for section, entries in SECTIONS:
        toc.append(rf"\tocsection{{{tex_escape(section)}}}")
        body.append(rf"\section{{{tex_escape(section)}}}")
        for entry in entries:
            fname, title, only = (tuple(entry) + (None,))[:3] if isinstance(entry, tuple) \
                else (entry, entry, None)
            label = label_for(fname)
            if fname.endswith(".tex"):
                if not (CONTENT / fname).exists():
                    sys.exit(f"error: {CONTENT / fname} not found (listed in SECTIONS)")
                toc.append(rf"\tocentry{{{tex_escape(title)}}}{{{label}}}{{}}")
                body.append(rf"\phantomsection\label{{{label}}}\input{{../content/{fname}}}")
                continue
            path = TEMPLATES / fname
            if not path.exists():
                sys.exit(f"error: {path} not found (listed in SECTIONS)")
            listed.add(fname)
            raw = strip_contents(path.read_text())
            code = raw if fname == HEADER_FILE else strip_preamble(raw, shared)
            if only:
                code = keep_only(code, only, fname)
            if COMPACT and fname != HEADER_FILE:
                code = compact(code)
            if CONDENSE and fname != HEADER_FILE:
                condensed.append((fname, code, condense(code, width)))
                code = condensed[-1][2]
            (src_dir / fname).parent.mkdir(parents=True, exist_ok=True)
            (src_dir / fname).write_text(code, newline="\n")
            names = ", ".join(tex_escape(n) for n in top_level_names(code) if fname != HEADER_FILE)
            toc.append(rf"\tocentry{{{tex_escape(title)}}}{{{label}}}{{{names}}}")
            body.append(rf"\codefile{{{tex_escape(title)}}}{{{tex_escape(Path(fname).name)}}}{{{label}}}"
                        rf"{{src/{fname}}}")

    check_condensed(condensed)
    for path in sorted(TEMPLATES.rglob("*.cpp")):
        rel = path.relative_to(TEMPLATES).as_posix()
        if rel not in listed:
            print(f"note: cpp_templates/{rel} is not in SECTIONS, so it was left out")

    template = (ROOT / "notebook_template.tex").read_text()
    tex = (template
           .replace("%%PAPER%%", PAPER)
           .replace("%%TEAM%%", tex_escape(TEAM_NAME))
           .replace("%%SUBTITLE%%", tex_escape(SUBTITLE))
           .replace("%%CODEFONT%%", f"\\fontsize{{{CODE_FONT_PT[0]}}}{{{CODE_FONT_PT[1]}}}")
           .replace("%%TOC%%", "\n".join(toc))
           .replace("%%BODY%%", "\n".join(body)))
    out = BUILD / "notebook.tex"
    out.write_text(tex, newline="\n")
    return out


def compile_pdf(tex):
    if not shutil.which("latexmk"):
        sys.exit("error: latexmk not found; install TeX Live or MiKTeX, or use --tex")
    res = subprocess.run(["latexmk", "-pdf", "-interaction=nonstopmode", "-halt-on-error",
                          tex.name], cwd=BUILD, capture_output=True, text=True)
    log = BUILD / "notebook.log"
    if res.returncode != 0:
        print(res.stdout[-3000:])
        sys.exit(f"error: LaTeX failed, see {log}")
    shutil.copy(BUILD / "notebook.pdf", ROOT / "notebook.pdf")
    m = re.search(r"Output written on .*?\((\d+) pages?", log.read_text(errors="replace"))
    pages = int(m.group(1)) if m else None
    print(f"wrote {ROOT / 'notebook.pdf'} ({pages} pages)")
    if pages and pages > PAGE_LIMIT:
        print(f"warning: {pages} pages is over the {PAGE_LIMIT}-page limit; "
              "drop entries from SECTIONS or shrink CODE_FONT_PT")


if __name__ == "__main__":
    tex = build_tex()
    if "--tex" in sys.argv:
        print(f"wrote {tex}")
    else:
        compile_pdf(tex)
