#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define mk make_pair
using namespace std;
const int N=500005;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}

int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}
int n,fac[N],a[N];
int C(int x,int y){
    return mul(fac[x],mul(qpow(fac[y],MOD-2),qpow(fac[x-y],MOD-2)));
}

signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+n+1);
    fac[0]=1;
    for(int i=1;i<=n+n;i++) fac[i]=mul(i,fac[i-1]);
    int sum=0;
    for(int i=1;i<=n;i++){
        sum=add(sum,(a[n+n-i+1]-a[i])%MOD);
    }
    printf("%d\n",mul(C(n+n,n),sum));
    return 0;
}
