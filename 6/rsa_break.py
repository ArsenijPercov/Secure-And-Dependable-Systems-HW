n = 44331583
e = 15852553
sqrt_n = 6658
res = []
for i in range (1,sqrt_n+1):
    j = n/i
    if j%1 == 0:
        res.append((i-1)*(j-1))
keys = []
for i in range(len(res)):
    for j in range (1,int(res[i])):
        if (e*j)%res[i]==1:
            keys.append(j)
cipher = [21556870,12228498,25056229,38800351,19503311,12228498,38800351,
24444405,35051831,24444405,30059578,38800351,5811028,12228498,
27948437,12228498,1365184,24444405,38800351,18162318,14922283,
27948437,23749280,12351750,42881586]
clear = []
for i in cipher:
    x = ((i**keys[0])%n)
    clear.append(x)
    print(chr(x))

