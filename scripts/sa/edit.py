"""edit.py FILE: apply (old,new) pairs from stdin python literal list; fail if any old not found exactly once."""
import sys, ast
f = sys.argv[1]; s = open(f).read()
for old, new in ast.literal_eval(sys.stdin.read()):
    n = s.count(old)
    if n != 1:
        sys.exit(f"{f}: expected 1 match, got {n}: {old[:60]!r}")
    s = s.replace(old, new)
open(f, 'w').write(s)
print("ok", f)
