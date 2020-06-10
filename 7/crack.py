flag = True
x = 0 
while(flag):
    res = (143**x)%191
    res2 = (42**(27*x))%191
    if (res == 178 == res2):
        print(x)
    x+=1 