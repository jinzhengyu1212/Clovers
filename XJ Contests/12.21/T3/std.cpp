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
int n,m;
vector<int> v[N];
namespace solver1{
    vector<int> G[N];
    int dfn[N],low[N],bl[N],ans=0,tot=0,T;
    void dfs(int u,int f){
        dfn[u]=++tot; low[u]=dfn[u];
        if(u==T) bl[u]=1;
        for(auto &to : G[u]){
            if(to==f) continue;
            if(dfn[to]) checkmin(low[u],dfn[to]);
            else dfs(to,u),bl[u]|=bl[to],checkmin(low[u],low[to]);
        }
        if(bl[u]&&low[u]==dfn[u]) ans++;
    }
    void main(){
        int Q=read();
        while(Q--){
            for(int i=1;i<=n;i++) G[i]=v[i],dfn[i]=0,bl[i]=0;
            int S=read(); T=read(); int k=read();
            for(int i=1;i<=k;i++){
                int x=read(),y=read();
                G[x].push_back(y);
                G[y].push_back(x);
            }
            ans=0; tot=0;
            dfs(S,-1);
            printf("%d\n",ans-1);
        }
    }
}

int dfn[N],low[N],col[N],kkk=0,bl[N],tot=0;
int fa[N][20],dep[N];
void dfs1(int u,int f){
    dfn[u]=++tot; low[u]=dfn[u];
    vector<int> V; V.clear();
    for(auto &to : v[u]){
        if(to==f) continue;
        if(dfn[to]) checkmin(low[u],dfn[to]);
        else{
            V.push_back(to);
            col[to]=col[u];
            fa[to][0]=u; dep[to]=dep[u]+1;
            for(int i=1;i<20;i++) fa[to][i]=fa[fa[to][i-1]][i-1];
            dfs1(to,u),checkmin(low[u],low[to]);
        }
    }
    v[u]=V;
    if(low[u]==dfn[u]&&f!=-1) bl[u]=1;
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void dfs2(int u){
    for(auto &to : v[u]){
        bl[to]+=bl[u];
        dfs2(to);
    }
}
struct Edge{
    int x,y,to;
};
int dist(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
vector<Edge> G[N];
int ans,vis[N];
void find(int u,int dis,int T){
    vis[col[u]]=1;
    if(col[u]==col[T]){
        ans=dis+dist(u,T);
        return;
    }
    for(auto &E : G[col[u]]){
        if(vis[E.to]) continue;
        int tmp=dist(u,E.x);
        find(E.y,dis+tmp+1,T);
    }
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    if(n<=1000&&m<=1000){
        solver1::main();
        return 0;
    }
    for(int i=1;i<=n;i++) if(!col[i]){
        col[i]=++kkk;
        dep[i]=1; dfs1(i,-1);
        dfs2(i);
    }
    int sumk=0,Q=read();
    while(Q--){
        int S=read(),T=read(),k=read();
        sumk+=k;
        if(sumk==0){
            if(col[S]!=col[T]){
                puts("-1");
                continue;
            }
            printf("%d\n",bl[S]+bl[T]-2*bl[LCA(S,T)]);
        }
        else{
            vector<pii> A;
            for(int i=1;i<=k;i++){
                int x=read(),y=read();
                A.push_back(mk(x,y));
                if(col[x]==col[y]){
                    puts("MYY AKAK!!!");
                    return 0;
                }   
                G[col[x]].push_back({x,y,col[y]});
                G[col[y]].push_back({y,x,col[x]});
            }
            ans=inf;
            find(S,0,T);
            if(ans==inf) puts("-1");
            else printf("%d\n",ans);
            for(auto &x : A){
                G[col[x.first]].clear();
                G[col[x.second]].clear();
                vis[col[x.first]]=0; vis[col[x.second]]=0;
            }
        }
    }
    return 0;
}