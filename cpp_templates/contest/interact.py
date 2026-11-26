"""Runs an interactive solution against a local interactor (see interactor.cpp), relaying and logging every line.

usage: python interact.py SOLUTION INTERACTOR [FIRST_SEED [LAST_SEED]] [--timeout SEC] [-v]

SOLUTION and INTERACTOR are commands (quote them if they take arguments, e.g. "python sol.py"); the interactor
gets the seed as its last argument. Seeds FIRST..LAST are run in order (default 1..1), stopping at the first
failure with its transcript: "> " lines went from the solution to the interactor, "< " lines back. A run fails
if the interactor exits nonzero, the solution exits nonzero, or the pair takes longer than --timeout seconds (a
solution that forgets to flush usually shows up as a timeout). -v prints the transcript of every run.
"""

import argparse
import os
import shlex
import subprocess
import sys
import threading
import time


def command(cmd, *extra):
    if os.name == "nt":  # Windows takes a command line string; shlex would eat the backslashes in paths
        return " ".join([cmd, *extra])
    return shlex.split(cmd) + list(extra)


def start(cmd):
    return subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                            text=True, bufsize=1)


def run(sol_cmd, inter_cmd, seed, timeout):
    """Returns (ok, verdict, transcript lines, solution stderr, interactor stderr)."""
    inter = start(command(inter_cmd, str(seed)))
    sol = start(command(sol_cmd))
    log, errs, lock = [], {}, threading.Lock()

    def relay(src, dst, tag):
        for line in iter(src.readline, ""):
            with lock:
                log.append(tag + line.rstrip("\n"))
            try:
                dst.write(line)
                dst.flush()
            except OSError:  # the other side has exited
                break
        try:
            dst.close()
        except OSError:
            pass

    def drain(name, src):
        errs[name] = src.read()

    threads = [threading.Thread(target=relay, args=(sol.stdout, inter.stdin, "> "), daemon=True),
               threading.Thread(target=relay, args=(inter.stdout, sol.stdin, "< "), daemon=True),
               threading.Thread(target=drain, args=("sol", sol.stderr), daemon=True),
               threading.Thread(target=drain, args=("inter", inter.stderr), daemon=True)]
    for t in threads:
        t.start()
    deadline = time.monotonic() + timeout
    verdict = None
    try:
        inter.wait(timeout=timeout)
        if inter.returncode != 0:  # a rejected solution may still be waiting for input, so don't wait for it
            verdict = f"rejected by the interactor (exit code {inter.returncode})"
        else:
            sol.wait(timeout=max(0.0, deadline - time.monotonic()))
            if sol.returncode != 0:
                verdict = f"solution crashed (exit code {sol.returncode})"
    except subprocess.TimeoutExpired:
        verdict = f"time limit exceeded ({timeout} s)"
    for p in (inter, sol):
        if p.poll() is None:
            p.kill()
            p.wait()
    for t in threads:
        t.join(timeout=1)
    return verdict is None, verdict or "OK", log, errs.get("sol", ""), errs.get("inter", "")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("solution")
    ap.add_argument("interactor")
    ap.add_argument("first", nargs="?", type=int, default=1)
    ap.add_argument("last", nargs="?", type=int)
    ap.add_argument("--timeout", type=float, default=5.0)
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()
    last = args.first if args.last is None else args.last
    for seed in range(args.first, last + 1):
        ok, verdict, log, sol_err, inter_err = run(args.solution, args.interactor, seed, args.timeout)
        msg = inter_err.strip().splitlines()
        print(f"seed {seed}: {verdict}" + (f" ({msg[-1]})" if msg else ""))
        if args.verbose or not ok:
            print("\n".join(log))
            if sol_err.strip():
                print("--- solution stderr ---\n" + sol_err.rstrip())
            if inter_err.strip():
                print("--- interactor stderr ---\n" + inter_err.rstrip())
        if not ok:
            sys.exit(1)


if __name__ == "__main__":
    main()
