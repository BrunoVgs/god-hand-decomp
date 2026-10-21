import json, re, sys, collections
from pathlib import Path
sys.path.insert(0,'scripts'); sys.path.insert(0, 'scripts/sa')
import sa_precheck
funcs = sa_precheck.load_funcs()
cfg = json.loads(Path('compile_config.json').read_text())
carved = {e["name"] for e in cfg["carved_funcs"] if "name" in e}
callee = sys.argv[1] if len(sys.argv) > 1 else 'func_001C28A0'
groups = collections.defaultdict(list)
for n, ins in funcs.items():
    if n in carved or not any(op == 'jal' and a and a[0] == callee for _, op, a in ins):
        continue
    key = []
    for _, op, a in ins:
        a2 = [re.sub(r'0x[0-9A-F]+ >> 16', 'K', x) for x in a]
        if op in ('lui',) and a2 and a2[0] == '$at': a2 = ['$at', 'K']
        if op == 'addiu' and len(a2) == 3 and a2[1] == '$zero': a2 = a2[:2] + ['N']
        if op == 'swc1' and a2[1].endswith('($sp)'): a2 = ['F', 'S']
        key.append(op + ' ' + ','.join(a2))
    groups['\n'.join(key)].append((n, len(ins) * 4))
for k, v in sorted(groups.items(), key=lambda x: -len(x[1])):
    print(len(v), v[0][1], ' '.join(n for n, _ in v))
