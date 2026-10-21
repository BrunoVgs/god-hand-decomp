import re
from collections import defaultdict, Counter
rows=[]
for l in open('progress/batch_log.md'):
    p=[x.strip() for x in l.strip().strip('|').split('|')]
    if len(p)==8 and re.match(r'\d{4}-\d\d-\d\dT',p[0]): rows.append(p)
def secs(t):
    t=t.strip()
    m=re.match(r'group ~?(\d+)s/(\d+)',t)
    if m: return int(m[1])/int(m[2])
    m=re.match(r'\(group with \w+, ~(\d+)s\)',t)
    if m: return int(m[1])/2
    m=re.match(r'~?(\d+(?:\.\d+)?)s?(?:\s*\+.*|\+perm)?$',t)
    if m: return float(m[1])
    return None
fn=defaultdict(lambda: {'t':0.0,'unk':0,'rows':0,'final':None,'m2c':set(),'bytes':0})
for r in rows:
    st=r[3].split()[0].rstrip(':,')
    if st in('batch','permuter'): continue
    st={'non-matching':'NM','hard-tail':'hard-tail','matched':'matched'}[st]
    d=fn[r[1]]; s=secs(r[5]); d['rows']+=1; d['final']=st; d['bytes']=int(r[2]) if r[2].isdigit() else d['bytes']
    d['m2c'].add('yes' if r[6].startswith(('yes','m2c')) else 'no')
    if s is None: d['unk']+=1
    else: d['t']+=s
cls=defaultdict(list)
for n,d in fn.items(): cls[d['final']].append((n,d))
tot=sum(d['t'] for d in fn.values())
print(f"functions {len(fn)}, known time {tot/3600:.2f} h")
for k in ('matched','NM','hard-tail'):
    L=cls[k]; known=[d for n,d in L if d['unk']==0 or d['t']>0]
    t=sum(d['t'] for n,d in L)
    print(f"{k:9s} n={len(L):3d} timed={len(known):3d} total={t/60:6.0f} min share={100*t/tot:4.1f}% avg={t/max(1,len(known)):5.0f}s median={sorted(d['t'] for d in known)[len(known)//2]:4.0f}s bytes={sum(d['bytes'] for n,d in L)}")
print("untimed rows:", sum(d['unk'] for d in fn.values()))
# m2c
sv={l.split('\t')[0]:l.rstrip('\n').split('\t') for l in open('build/sa/survey.tsv')}
se={l.split('\t')[0]:l.rstrip('\n').split('\t') for l in open('build/sa/survey_err.tsv')}
used=[n for n,d in fn.items() if 'yes' in d['m2c']]
print("m2c draft used (log):",len(used),"of",len(fn))
def reason(n):
    v=sv.get(n); 
    if not v: return 'not surveyed'
    if v[1]=='clean': return 'clean draft available'
    m=se.get(n,v)[2]
    if 'jtbl' in m: return 'jump table (m2c crash)'
    if 'vu0' in m: return 'VU0 (lqc2/sqc2/vsub)'
    if 'ldl' in m: return 'unaligned 64-bit ldl/ldr/sdl/sdr (struct copy)'
    if 'mmi' in m or 'por' in m: return 'MMI (por)'
    if re.search(r'unset:.*(t0|t1|t2|t3|a4|a5|a6|a7)',m): return 'EE args 5-8 in t0-t3/a4-a7 read as unset'
    if 'unk:' in m: return 'other unknown insn ('+m.split('unk:')[1]+')'
    return 'other unset reg ('+m+')'
allr=Counter(reason(n) for n in fn)
print("survey over all functions:"); [print(f"  {v:3d} {k}") for k,v in allr.most_common()]
nou=Counter(reason(n) for n,d in fn.items() if 'yes' not in d['m2c'])
print("functions written without m2c, by survey result:"); [print(f"  {v:3d} {k}") for k,v in nou.most_common()]
# time on bad outcome by reason
tb=defaultdict(float)
for n,d in fn.items():
    if d['final']!='matched': tb[reason(n)]+=d['t']
print("NM+hard-tail time by m2c result (min):", {k:round(v/60) for k,v in sorted(tb.items(),key=lambda x:-x[1])})
# matched time split by m2c used vs clean-not-used
for lab,sel in [('matched, m2c used',lambda n,d:d['final']=='matched' and 'yes' in d['m2c']),('matched, hand',lambda n,d:d['final']=='matched' and 'yes' not in d['m2c'])]:
    L=[d['t'] for n,d in fn.items() if sel(n,d) and d['t']>0]
    print(f"{lab}: n={len(L)} avg={sum(L)/max(1,len(L)):.0f}s")

print("\n== wall-clock calibrated ==")
import datetime as dt
def ts(s): return dt.datetime.strptime(s,'%Y-%m-%dT%H:%M:%SZ')
groups=defaultdict(list)
for r in rows:
    st=r[3].split()[0].rstrip(':,')
    if st in('batch','permuter'): continue
    groups[r[0]].append(r)
keys=sorted(groups)
wall=defaultdict(float); skipped=0
for prev,cur in zip(keys,keys[1:]):
    gap=(ts(cur)-ts(prev)).total_seconds()
    if gap>45*60: skipped+=gap; continue
    g=groups[cur]; est=[secs(r[5]) or 0 for r in g]; S=sum(est)
    for r,e in zip(g,est):
        wall[r[1]]+= gap*(e/S if S else 1/len(g))
W=sum(wall.values())
print(f"wall attributed {W/3600:.2f} h (gaps >45 min skipped: {skipped/60:.0f} min)")
for k in ('matched','NM','hard-tail'):
    L=[wall[n] for n,d in cls[k]]
    print(f"{k:9s} n={len(L):3d} total={sum(L)/60:5.0f} min share={100*sum(L)/W:4.1f}% avg={sum(L)/len(L):4.0f}s")
bad=sum(wall[n] for n,d in fn.items() if d['final']!='matched')
print(f"NM+hard-tail total {bad/60:.0f} min ({100*bad/W:.0f}%)")
tbw=defaultdict(float)
for n,d in fn.items():
    if d['final']!='matched': tbw[reason(n)]+=wall[n]
print("NM+hard-tail wall by m2c result (min):", {k:round(v/60) for k,v in sorted(tbw.items(),key=lambda x:-x[1])})
