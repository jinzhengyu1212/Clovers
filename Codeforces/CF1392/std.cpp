#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int qpow(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}
const int N=4000005;
int n,m;
int fac[N],inv[N];
int C[N];//C(n,i)

int main()
{
    scanf("%d%d",&n,&m);
    fac[0]=1;
    for(int i=1;i<=n+m;i++) fac[i]=mul(fac[i-1],i);
    inv[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) inv[i]=mul(inv[i+1],i+1);
    for(int i=0;i<=n;i++) 
        C[i]=mul(fac[n],mul(inv[i],inv[n-i]));
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int tmp=mul(C[i],mul(m+i,mul(fac[i-1],inv[i])));
        if(i&1) ans=add(ans,tmp);
        else ans=sub(ans,tmp);
    }
    cout<<mul(ans,add(mul(n,qpow(m+1,MOD-2)),1))<<endl;
    return 0;
}