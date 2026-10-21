"""fam_tail.py FN...: template + retail tail values, order-search the middle six tail stores."""
import os, re, subprocess, sys
os.makedirs('build/sa', exist_ok=True)
sys.path.insert(0, 'scripts/sa')
import fam_sig
NAMES = {0x5EC: ('int', 'EM_WORK_5EC'), 0x5E8: ('int', 'EM_WORK_5E8'), 0x5E4: ('int', 'EM_WORK_5E4'),
         0x5F0: ('int', 'EM_WORK_5F0'), 0x5F6: ('short', 'EM_WORK_5F6'), 0x60C: ('unsigned char', 'EM_SUB_KIND')}
for fn in sys.argv[1:]:
    lst = subprocess.run(['python3', 'scripts/sa/lst.py', fn], capture_output=True, text=True).stdout
    # values of regs loaded after the last func_001FD9D8 call
    tailtxt = lst[lst.rindex('func_001FD9D8'):]
    regs = {'$zero': 0}
    for m in re.finditer(r'addiu\s+(\$\w+), \$zero, (-?0x\w+)', tailtxt):
        regs[m[1]] = int(m[2], 16)
    vals = {}
    for m in re.finditer(r'(sw|sh|sb)\s+(\$\w+), 0x(\w+)\(\$s0\)', tailtxt):
        off = int(m[3], 16)
        if off in NAMES:
            vals[off] = regs.get(m[2])
    src = open(f'build/sa/fg_{fn}.c').read()
    a = src.index('    *(unsigned char *)(p + EM_SUB_KIND)'); b = src.index('    *(short *)(p + EM_TARGET)')
    blk = ''.join(f'    *({NAMES[o][0]} *)(p + {NAMES[o][1]}) = {vals[o]};\n' for o in sorted(NAMES))
    src = src[:a] + '/*ORDER*/\n' + blk + '/*END*/\n' + src[b:]
    open(f'build/sa/ft_{fn}.c', 'w').write(src)
    r = subprocess.run(['python3', 'scripts/sa/order_search.py', f'build/sa/ft_{fn}.c', fn, '--compiler', 'sn-2.95.3-136'],
                       capture_output=True, text=True)
    best = re.search(r'best (v\d+) \((\d+)\)', r.stdout)
    print(fn, {hex(k): v for k, v in vals.items()}, best.group(0) if best else r.stdout[-500:] + r.stderr[-500:])
    if best and best[2] == '0':
        subprocess.run(['cp', 'build/sa/order_best.c', f'build/sa/win_{fn}.c'])
