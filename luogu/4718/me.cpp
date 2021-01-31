/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
ll _abs(ll x){return x<0 ? -x : x;}
ll mul(ll a,ll b,ll mod){
	return (a*b-(ll)((long double)a/mod*b)*mod+mod)%mod;
}
ll qpow(ll a,ll b,ll mod){
    ll ret=1;
    while(b){
        if(b&1) ret=mul(ret,a,mod);
        a=mul(a,a,mod); 
        b>>=1;
    }
    return ret;
}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline ll read(){
    ll x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=500005;
const int M=1005;
#define ull unsigned long long
int Rand(){return rand()&32767;}
ll ran(ll l,ll r){
    ull ret=((ull)Rand()<<15)+Rand();
    return ret%(r-l+1)+l;
}
ll mx;
namespace PollardRho{
    ll gcd(ll x,ll y){return (!y) ? x : gcd(y,x%y);}
    bool MR(ll n){
        if(n<3) return n==2;
        ll a=n-1,b=0;
        while(a%2==0) a/=2,b++;
        for(int i=1,j;i<=8;i++){
            ll x=ran(1,n-2),v=qpow(x,a,n);
            if(v==1||v==n-1) continue;
            for(j=0;j<b;j++){
                v=mul(v,v,n);
                if(v==n-1) break;
            }
            if(j>=b) return 0;
        }
        return 1;
    }
    ll f(ll x,ll c,ll n){return (mul(x,x,n)+c)%n;}
    ll PH(ll n){
        if(MR(n)) return n;
        ll s=0,t=0;
        ll c=ran(1,n-1);
        int step=0,h=1; ll val=1;
        for(h=1;;h<<=1,s=t,val=1){
            for(step=1;step<=h;step++){
                t=f(t,c,n); 
                val=mul(val,_abs(s-t),n);
                if(step%127==0){
                    ll d=gcd(val,n);
                    if(d>1) return d;
                }
            }
            ll d=gcd(val,n);
            if(d>1) return d;
        }
    }
    void fac(ll n){
        if(n<=mx||n<2) return;
        if(MR(n)){
            mx=max(mx,n);
            return;
        }
        ll p=PH(n);
        while(n%p==0) n/=p;
        fac(p); fac(n);
    }
}

ll n;
int main()
{
    srand(time(0));
    int T=read();
    while(T--){
        n=read();
        mx=0; PollardRho::fac(n);
        if(mx==n) puts("Prime");
        else printf("%lld\n",mx);
    }
    return 0;
}