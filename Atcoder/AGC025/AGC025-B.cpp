#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;

int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=ret*x%MOD;
        x=x*x%MOD;
        y>>=1;
    }
    return ret;
}

int fac[1000005];
int C(int n,int m){
    if(n<m) return 0;
    return fac[n]*qpow(fac[m],MOD-2)%MOD*qpow(fac[n-m],MOD-2)%MOD;
}
int A,B,k,n;
signed main()
{
    scanf("%lld%lld%lld%lld",&n,&A,&B,&k);
    fac[0]=0;
    int ans=0; fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%MOD;
    for(int i=0;i<=n;i++){
        int x=i;
        if((k-A*i)%B!=0||k<A*i) continue;
        int y=(k-A*i)/B;
        ans=(ans+C(n,x)*C(n,y)%MOD)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}