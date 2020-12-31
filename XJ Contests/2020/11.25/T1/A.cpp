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
const int N=200005;
int n,dep[N],fa[N][20],fac[N],ifac[N],Base[N];
vector<int> v[N];
int C(int n,int m){
    return mul(fac[n],mul(ifac[n-m],ifac[m]));
}

void dfs(int u){
    for(auto &to : v[u]){
        if(to==fa[u][0]) continue;
        dep[to]=dep[u]+1;
        fa[to][0]=u;
        for(int i=1;i<20;i++) fa[to][i]=fa[fa[to][i-1]][i-1];
        dfs(to);
    }
}

void init(){
    n=read();
    Base[0]=1; Base[1]=qpow(2,MOD-2);
    for(int i=2;i<=n;i++) Base[i]=mul(Base[i-1],Base[1]);
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=2;i<=n;i++) Base[i]=mul(Base[i-1],Base[1]);
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y),v[y].push_back(x);
    }
    dep[1]=1; dfs(1);
}

int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}

void solve(){
    int Q=read();
    while(Q--){
        int x=read(),y=read();
        int lca=LCA(x,y);
        int dis1=dep[x]-dep[lca],dis2=dep[y]-dep[lca];
        int ret=C(dis1+dis2,dis1);
        printf("%lld\n",mul(ret,Base[dis1+dis2]));
    }
}

int main()
{
    init();
    solve();
    return 0;
}