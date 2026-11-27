"""Update the solve counts table in the root README.md.

Counts come from the solutions tracked in this repo: one problem per unique
path with the extension removed, so 1.py and 1.cpp count once.

Usage (from anywhere):
    python .scripts/update_solve_counts.py            # update README.md
    python .scripts/update_solve_counts.py --dry-run  # show changes only
"""

import argparse
import datetime
import subprocess
import sys
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"

SOLUTION_EXTS = {".py", ".cpp", ".c", ".java", ".js", ".kt", ".rs"}

# README row name -> folders whose solutions are counted.
LOCAL_SOURCES = {
    "Atcoder": ["atcoder"],
    "Baekjoon Online Judge": ["baekjoon"],
    "Codeforces": ["codeforces/main", "codeforces/gym", "codeforces/acmsguru"],
    "CSES": ["cses"],
    "Hackerrank": ["hackerrank"],
    "Kattis": ["kattis"],
    "Leetcode": ["leetcode"],
    "Project Euler": ["project_euler"],
    "Sphere": ["spoj"],
    "TLX": ["tlx"],
    "VNOI": ["vnoi"],
    "Yosupo Library Checker": ["yosupo"],
}

# Folders inside the sources above that hold helpers, not solutions.
EXCLUDED_DIRS = ["project_euler/Other"]


def tracked_files():
    out = subprocess.run(
        ["git", "ls-files"], cwd=ROOT, capture_output=True, text=True, check=True
    ).stdout
    return [PurePosixPath(line) for line in out.splitlines()]


def count_local(files, folders):
    problems = set()
    for f in files:
        if f.suffix not in SOLUTION_EXTS:
            continue
        s = str(f)
        if not any(s.startswith(d + "/") for d in folders):
            continue
        if any(s.startswith(d + "/") for d in EXCLUDED_DIRS):
            continue
        problems.add(str(f.with_suffix("")))
    return len(problems)


def split_row(line):
    return [c.strip() for c in line.strip().strip("|").split("|")]


def render_table(rows):
    widths = [max(len(r[i]) for r in rows) for i in range(len(rows[0]))]
    lines = []
    for k, row in enumerate(rows):
        if k == 1:  # separator row
            row = ["-" * w for w in widths]
        lines.append("| " + " | ".join(c.ljust(w) for c, w in zip(row, widths)) + " |")
    return lines


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--dry-run", action="store_true", help="print changes without writing")
    args = parser.parse_args()

    text = README.read_text(encoding="utf-8", newline="")
    eol = "\r\n" if "\r\n" in text else "\n"
    lines = text.splitlines()
    start = next(i for i, l in enumerate(lines) if l.startswith("| Online Judge"))
    end = start
    while end < len(lines) and lines[end].startswith("|"):
        end += 1
    rows = [split_row(l) for l in lines[start:end]]

    files = tracked_files()
    changes = []
    total = 0
    for row in rows[2:]:
        name, _, old = row
        if name == "**Total**":
            continue
        new = old
        if name in LOCAL_SOURCES:
            new = str(count_local(files, LOCAL_SOURCES[name]))
        else:
            print(f"{name}: no source configured, keeping {old}", file=sys.stderr)
        row[2] = new
        total += int(new)
        if new != old:
            changes.append(f"{name}: {old} -> {new}")

    total_row = next(r for r in rows if r[0] == "**Total**")
    if total_row[2] != str(total):
        changes.append(f"Total: {total_row[2]} -> {total}")
    total_row[2] = str(total)

    lines[start:end] = render_table(rows)

    today = datetime.date.today()
    date_str = f"{today:%B} {today.day}, {today.year}"
    for i, l in enumerate(lines):
        if l.startswith("Solve counts updated as of"):
            lines[i] = f"Solve counts updated as of {date_str}"

    print("\n".join(changes) if changes else "No count changes.")
    if args.dry_run:
        return
    README.write_text(eol.join(lines) + eol, encoding="utf-8", newline="")
    print(f"Wrote {README.relative_to(ROOT)} (dated {date_str})")


if __name__ == "__main__":
    main()
