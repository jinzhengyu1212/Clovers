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
const int MOD=924844033;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
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
const int N=400005;
const int M=1005;

namespace FFT{
    int rev[N<<2],G[N<<2],IG[N<<2];
    int init(int n){
        int len=1;
        while(len<n) len<<=1;
        for(int i=1;i<len;i++) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
        for(int i=1;i<=len;i<<=1){
            G[i]=qpow(5,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
        return len;
    }
    void ntt(int *a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==-1 ? IG[h<<1] : G[h<<1]);
            for(int i=0;i<len;i+=(h<<1)){
                int tmp1,tmp2,w=1;
                for(int j=i;j<i+h;j++,Mul(w,wn)){
                    tmp1=a[j],tmp2=mul(w,a[j+h]);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) Mul(a[i],invlen);
        }
    }
    void multi(int *a,int *b,int n,int m){
        int len=init(n+m+1);
        ntt(a,len,1); ntt(b,len,1);
        for(int i=0;i<len;i++) Mul(a[i],b[i]);
        ntt(a,len,-1);
    }
}
int n,sz[N],t[N];
vector<int> v[N];
void dfs(int u,int f){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs(to,u); sz[u]+=sz[to];
    }
    if(f!=-1) t[sz[u]]++, t[n-sz[u]]++;
}

int fac[N],f[N<<2],g[N<<2],ifac[N];
int C(int n,int m){return mul(fac[n],mul(ifac[n-m],ifac[m]));}
void init(){
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1,-1);
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    for(int i=0;i<=n;i++) ifac[i]=qpow(fac[i],MOD-2);
}

int ans[N];
void solve(){
    for(int i=0;i<=n;i++) g[i]=ifac[i];
    for(int i=1;i<=n;i++) f[n-i]=mul(fac[i],t[i]);
    FFT::multi(f,g,n,n);
    for(int i=1;i<=n;i++) ans[i]=mul(ifac[i],f[n-i]);
    for(int i=1;i<=n;i++) printf("%d\n",sub(mul(n,C(n,i)),ans[i]));
}

int main()
{
    init(); solve();
    return 0;
}