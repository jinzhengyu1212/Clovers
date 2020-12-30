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
const int N=300005;
const int B=300000;
int n,m,t[2][N<<1],w[N];
vector<int> v[N];

int fa[N][20],dep[N];
void dfs1(int u){
    for(auto &to : v[u]){
        if(to==fa[u][0]) continue;
        fa[to][0]=u;
        for(int i=1;i<20;i++) fa[to][i]=fa[fa[to][i-1]][i-1];
        dep[to]=dep[u]+1; dfs1(to);
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}

struct node{
    int typ,flag,which;
};
vector<node> P[N];
void init(){
    n=read(); m=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y),v[y].push_back(x);
    }
    dep[1]=1; dfs1(1);
    for(int i=1;i<=n;i++) w[i]=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        int lca=LCA(x,y),dis=dep[x]+dep[y]-dep[lca]*2;
        P[x].push_back({dep[x],1,0});
        P[fa[lca][0]].push_back({dep[x],-1,0});
        P[y].push_back({dep[y]-dis+B,1,1});
        P[lca].push_back({dep[y]-dis+B,-1,1});
    }
}

int ans[N];
void dfs2(int u){
    int pre=t[0][dep[u]+w[u]]+t[1][dep[u]-w[u]+B];
    for(auto &to : v[u]){
        if(to==fa[u][0]) continue;
        dfs2(to);    
    }
    for(auto &now : P[u]){
        t[now.which][now.typ]+=now.flag;
    }
    ans[u]=t[0][dep[u]+w[u]]+t[1][dep[u]-w[u]+B]-pre;
}

int main()
{
    init();
    dfs2(1);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}