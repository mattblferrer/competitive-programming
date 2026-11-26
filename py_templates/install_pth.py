# writes py_templates.pth into this Python's user site-packages, so any script can `from primes import is_prime`;
# run it again after moving the repo or switching Python versions, and delete the printed file to undo it
import pathlib
import site

here = pathlib.Path(__file__).resolve().parent
target = pathlib.Path(site.getusersitepackages())
target.mkdir(parents=True, exist_ok=True)
pth = target / "py_templates.pth"
pth.write_text(str(here) + "\n", encoding="utf-8")
print(f"wrote {pth} -> {here}")
