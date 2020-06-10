import random
import binascii

max_nonce = 2 ** 32

from hashlib import sha256 
x = random.getrandbits(224)
x = x << 32
flag = False
count = 0
while (not flag):
    x+=1
    count += 1
    if count > max_nonce:
        print("Failed to find the target")
        break
    binx = bin(x)
    hexstr = "{0:0>4X}".format(int(binx,2))
    data = binascii.a2b_hex(hexstr)
    hash = sha256(data)
    hashhex = hash.hexdigest()
    #print(hexstr)
    if hashhex[0:3] == '0'*3:
        flag = True
        print(hexstr)
        print(hashhex)


