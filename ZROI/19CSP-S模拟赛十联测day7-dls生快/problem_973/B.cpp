/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=500005;
ll n,a,b;
ll qpow(ll x,ll y){
    ll ret=1; 
    while(y){
        if(y&1) ret=mul(ret,x); 
        x=mul(x,x); 
        y>>=1;
        if(ret>=n||(y&&x>=n)) return -1; 
    } 
    return ret;
}

bool check(ll mid,int rnd){
    ll x1=mid/rnd,x2=mid%rnd;
    ll tmp1=qpow(x1+1,rnd-x2);
    ll tmp2=qpow(x1+2,x2);
    if(tmp1==-1||tmp2==-1) return 1;
    else return (double)tmp1*tmp2>=n;
}

int main()
{
    int T=read();
    while(T--){
        n=read(); a=read(); b=read();
        ll ans=INF;
        for(int rnd=1;rnd<=40;rnd++){
            ll l=1,r=n-1,mid,best;
            while(l<=r){
                mid=(l+r)>>1;
                if(check(mid,rnd)) r=mid-1,best=mid;
                else l=mid+1;
            }
            checkmin(ans,best*a+rnd*b);
        }
    }
    return 0;
}