a=[1000000007,998244353,1019260817]
b=[147066322,519725264,298770223]
c=[0,0,0]
def qpow(x,y,mod):
    ans=1
    while y:
        if(y%2==1):
            ans=ans*x%mod
        x=x*x%mod
        y=y//2
    return ans


mul=a[0]*a[1]*a[2]
ans=0
for i in range(0,3):
    m=mul//a[i]
    print(qpow(m,a[i]-2,a[i]))
    c[i]=qpow(m,a[i]-2,a[i])*m
    ans=ans+c[i]*b[i]
print(ans%mul)    