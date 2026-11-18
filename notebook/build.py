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
from pathlib import Path

# ---------------------------------------------------------------- settings
TEAM_NAME = "Team Notebook"
SUBTITLE = "github.com/mattblferrer/competitive-programming"
PAPER = "a4paper"  # or "letterpaper"
PAGE_LIMIT = 25  # ICPC regionals usually allow 25 single-sided pages
CODE_FONT_PT = (6.1, 6.6)  # font size, line spacing for code
COMPACT = True  # drop blank lines from the code (the template keeps its own)

# (section title, [entries]); an entry is a .cpp in cpp_templates/ or a .tex in content/,
# either bare or as (file, title). A .cpp entry can also be (file, title, [names]) to print
# only the components (structs/functions with their doc comments) that define those names.
# Templates not listed here are reported, not included.
SECTIONS = [
    ("Contest", [
        ("new_file.cpp", "Template"),
        ("contest.tex", "Commands and Checklist"),
        ("stress_gen.cpp", "Stress Test Generator"),
        ("safe_hash.cpp", "Safe Hash"),
    ]),
    ("Data Structures", [
        ("data_structures.cpp", "Data Structures"),
        ("dsu.cpp", "DSU"),
        ("segment_tree.cpp", "Segment Trees"),
    ]),
    ("Graphs", [
        ("graph_search.cpp", "Topological Sort"),
        ("shortest_paths.cpp", "Shortest Paths"),
        ("graph_algorithms.cpp", "Graph Algorithms"),
        ("flows.cpp", "Max Flow"),
        ("min_cost_flow.cpp", "Min-Cost Flow"),
        ("matching.cpp", "Matching"),
        ("trees.cpp", "Trees"),
    ]),
    ("Strings", [
        ("strings.cpp", "Strings"),
    ]),
    ("Math", [
        ("modint.cpp", "ModInt"),
        ("number_theory.cpp", "Number Theory"),
        ("combinatorics.cpp", "Combinatorics"),
        ("matrix.cpp", "Matrix"),
        ("linear_algebra.cpp", "Linear Algebra", ["binexp", "gauss_jordan", "solve_linear", "det_mod", "count_spanning_trees", "XorBasis"]),
        ("fft.cpp", "FFT / NTT"),
        ("polynomial.cpp", "Polynomials"),
        ("bitmask.cpp", "Bitmask Transforms"),
    ]),
    ("Geometry", [
        ("geometry.cpp", "Geometry"),
    ]),
    ("DP and Search", [
        ("binary_ternary_search.cpp", "Binary and Ternary Search"),
        ("dp_optimizations.cpp", "DP Optimizations"),
    ]),
    ("Miscellaneous", [
        ("misc.cpp", "SAT Solver", ["SAT"]),
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
    define any name in wanted, plus whatever comes before the first block."""
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
    kept = [b for b in rest if set(top_level_names("\n".join(b))) & set(wanted)]
    found = {n for b in kept for n in top_level_names("\n".join(b))}
    missing = [n for n in wanted if n not in found]
    if missing:
        sys.exit(f"error: {fname} has no top-level {', '.join(missing)} (listed in SECTIONS)")
    return "\n".join(head + [l for b in kept for l in b]).strip("\n") + "\n"


def compact(text):
    """Remove blank lines (they cost about a tenth of the pages)."""
    return "\n".join(l for l in text.splitlines() if l.strip()) + "\n"


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
            raw = path.read_text()
            code = raw if fname == HEADER_FILE else strip_preamble(raw, shared)
            if only:
                code = keep_only(code, only, fname)
            if COMPACT and fname != HEADER_FILE:
                code = compact(code)
            (src_dir / fname).write_text(code, newline="\n")
            names = ", ".join(tex_escape(n) for n in top_level_names(code) if fname != HEADER_FILE)
            toc.append(rf"\tocentry{{{tex_escape(title)}}}{{{label}}}{{{names}}}")
            body.append(rf"\codefile{{{tex_escape(title)}}}{{{tex_escape(fname)}}}{{{label}}}"
                        rf"{{src/{fname}}}")

    for path in sorted(TEMPLATES.glob("*.cpp")):
        if path.name not in listed:
            print(f"note: cpp_templates/{path.name} is not in SECTIONS, so it was left out")

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
