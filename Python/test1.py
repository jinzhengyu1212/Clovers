def f(n):
    ret=1
    for i in range(1,n+1):
        ret*=i
    return ret
A=input().split()
n=int(A[0]); m=int(A[1])
print(int(f(n+m)/f(n)/f(m)))
