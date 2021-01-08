/*
the vast starry sky,
bright for those who chase the light.
*/
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
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
int n,m,p,fa[N];
vector<pii> L[N];
struct Day{
    int from,to,cost,id;
    bool operator < (const Day &rhs) const{
        return cost<rhs.cost;
    }
}D[N];
struct DSU{
    int fa[N],sz[N];
    void init(){for(int i=1;i<=n;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){
        x=getfather(x); y=getfather(y);
        fa[x]=y;
    }
    bool same(int x,int y){return getfather(x)==getfather(y);}
}T1,T2;
vector<int> v[N];
int dep[N],Fa[N][20],dfn[N],tot=0,out[N];
ll ans=0;
void dfs(int u){
    dfn[u]=++tot;
    for(auto &to : v[u]){
        dep[to]=dep[u]+1;
        Fa[to][0]=u;
        for(int i=1;i<20;i++) Fa[to][i]=Fa[Fa[to][i-1]][i-1];
        dfs(to);
    }
    out[u]=tot;
}
bool isfa(int x,int y){return dfn[x]<=dfn[y]&&out[x]>=out[y];}
bool inchain(int x,int y,int lca,int pos){
    return (isfa(pos,x)&&isfa(lca,pos))||(isfa(pos,y)&&isfa(lca,pos));
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[Fa[x][i]]>=dep[y]) x=Fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
vector<int> G[N];
vector<int> Block;
int inBlock[N],top=0,lca,sz[N];
void makeBlock(int x,int y){
    lca=LCA(x,y); int prex=x,prey=y; top=0;
    x=T2.getfather(x),y=T2.getfather(y);
    while(x!=y){
        if(dep[x]>dep[y]){
            int F=T2.getfather(fa[x]);
            if(T1.same(x,F)) T2.unite(x,F),x=T2.getfather(x);
            else{
                int xx=T1.getfather(x);
                if(!inBlock[xx]) Block.push_back(xx);
                sz[xx]+=dep[prex]-dep[x]+1;
                inBlock[xx]=1;
                prex=fa[x]; x=F;
            }
        }
        else{
            int F=T2.getfather(fa[y]);
            if(T1.same(y,F)) T2.unite(y,F),y=T2.getfather(y);
            else{
                int yy=T1.getfather(y);
                if(!inBlock[yy]) Block.push_back(yy);
                sz[yy]+=dep[prey]-dep[y]+1;
                inBlock[yy]=1;
                prey=fa[y]; y=F;
            }
        }
    }
    int xx=T1.getfather(x);
    if(!inBlock[xx]) Block.push_back(xx); 
    inBlock[xx]=1;
    sz[xx]+=dep[prex]+dep[prey]-2*dep[lca]+1;
}
void processedge(int ti,int from,int to){
    for(auto &E : L[ti]){
        int x=E.first,y=E.second;
        if(!inchain(from,to,lca,x)||!inchain(from,to,lca,y)) continue;
        int xx=T1.getfather(x),yy=T1.getfather(y);
        G[xx].push_back(y); G[yy].push_back(x);
    }
}
map<int,int> mp;
vector<int> T;
void link(int x,int w){
    mp.clear();
    for(auto &u : G[x]){
        if(T1.same(u,x)) continue;
        u=T1.getfather(u);
        if(!mp.count(u)) mp[u]=1;
        else mp[u]++;
    }
    int ad=0;
    for(auto &u : T){
        if(mp[u]!=1ll*sz[x]*sz[u]&&!T1.same(x,u)){
            T1.unite(u,x);
            ad+=sz[u]; ans+=w;
        }
    }
    sz[x]+=ad; T.push_back(x);
    for(auto &u : T) u=T1.getfather(u);
    sort(T.begin(),T.end()); 
    T.erase(unique(T.begin(),T.end()),T.end());
}
void solve(int ti,int w,int from,int to){
    makeBlock(from,to);
    processedge(ti,from,to); T.clear(); 
    for(auto &u : Block) link(u,w);
    for(auto &u : Block) inBlock[u]=0,sz[u]=0;
    for(auto &E : L[ti]){
        int xx=T1.getfather(E.first),yy=T1.getfather(E.second);
        G[xx].clear(),G[yy].clear();
    }
    Block.clear();
}

int main()
{
    n=read(); m=read(); p=read();
    for(int i=2;i<=n;i++) fa[i]=read();
    for(int i=1;i<=m;i++){
        D[i].from=read(); D[i].to=read();
        D[i].cost=read(); D[i].id=i;
    }
    sort(D+1,D+m+1);
    for(int i=1;i<=p;i++){
        int ti=read(),x=read(),y=read();
        L[ti].push_back(mk(x,y));
    }
    T1.init(); T2.init(); 
    for(int i=2;i<=n;i++) v[fa[i]].push_back(i); 
    dep[1]=1; dfs(1);
    for(int i=1;i<=m;i++) solve(D[i].id,D[i].cost,D[i].from,D[i].to);
    cout<<ans<<endl;
    return 0;
}