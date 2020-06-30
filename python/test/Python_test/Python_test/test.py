

def countbit1(n):
    count = 0;
    #n = 0xfffff
    for i in range(32):
        #print('i value is ',i)
        flag = n & (0x1 << i)
        #print('flag value is ',flag)
        if flag >= 1:
            count = count +1
    print('the bit 1 number  is : ',count)


countbit1(100)



