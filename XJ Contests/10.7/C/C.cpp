#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const int MOD=(int)1e9+7;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int bl[N],prime[N],mu[N],tot=0;
inline void init(){
    mu[1]=1;
    for(int i=2;i<N;i++) bl[i]=1;
    for(int i=2;i<N;i++){
        if(bl[i]) prime[++tot]=i,mu[i]=(MOD-1);
        for(int j=1;j<=tot;j++){
            if(i*prime[j]>N-1) break;
            bl[i*prime[j]]=0;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=mul(mu[i],mu[prime[j]]);
        }
    }
}
 
inline int calc(ll x){
    int ret=0;
    for(register ll l=1,r=1;l<=x;l=r+1){
        r=x/(x/l);
        ret=add(ret,mul(x/l%MOD,(r-l+1)%MOD));
    }
    return ret;
}
 
signed main(){
    ll n; int ans=0;
    scanf("%lld",&n);
    init();
    for(register ll i=1;i*i<=n;++i){
        ans=add(ans,mul(mu[i],calc(n/i/i)));
    }
    printf("%d\n",ans);
    return 0;
}