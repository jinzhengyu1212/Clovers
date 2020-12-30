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
const int N=100005;
const int M=10005;
int T,n,m,sg[M],a[N];
vector<int> v[N];
int ans[N],dp[N];
int dep[N],fa[N],gf[N];
struct Split{
    vector<int> v[N];
    int fa[N],dfn[N],top[N],id[N],sz[N],son[N];
    void dfs1(int u,int f){
        sz[u]=1; 
        for(auto &to : v[u]){
            if(to==f) continue;
            fa[to]=u; dfs1(to,u);
            if(sz[son[u]]<sz[to]) son[u]=to;
        }
    }
    int cnt=0;
    void dfs2(int u){
        dfn[u]=++cnt; id[cnt]=u;
        if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
        for(auto &to : v[u]){
            if(to==fa[u]||son[u]==to) continue;
            d
        }
    }
}tree1,tree2;

void build(){
    for(int i=1;i<=n;i++){
        if()
    }
}

void dfs(int u){
    dp[u]=sg[a[u]];
    for(auto &to : v[u]){
        if(to==fa[u]) continue;
        dep[to]=dep[u]+1; fa[to]=u; gf[to]=fa[u];
        dfs(to); ans[u]^=dp[to];
    }
    if(gf[u]){
        dp[gf[u]]^=dp[u];
    }
}

struct Query{
    int typ,x,add;
};
Query Q[N];
int vis[M];

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    T=read();
    for(int i=1;i<=T;i++){
        int opt=read();
        if(opt==1){
            int x=read();
            Q[i].typ=1; Q[i].x=x;
        }
        else if(opt==2){
            int x=read(),y=read();
            Q[i].typ=2; Q[i].x=x; Q[i].add=y;
        }
        else{
            int u=read(),to=read(),y=read();
            Q[i].typ=2; Q[i].x=to; Q[i].add=y;
            v[u].push_back(to); 
            checkmax(n,to);
        }
    }
    sg[0]=0;
    for(int i=1;i<=10000;i++){
        memset(vis,0,sizeof(vis));
        for(int j=i-1;j>=max(0,i-m);j--) vis[sg[j]]=1;
        for(int j=0;j<=i;j++){
            if(!vis[i]){
                sg[i]=i;
                break;
            }
        }
    }
    dfs(1);
}

void jump(int x,int val){
    while(x){
        ans[x]^=val;
        x=gf[x];
    }
}

void solve(){
    for(int i=1;i<=T;i++){
        int u=Q[i].x;
        if(Q[i].typ==1){
            if(ans[u]) puts("Yes");
            else puts("No"); 
        }
        else{
            jump(fa[u],sg[a[u]]);
            a[u]+=Q[i].add;
            jump(fa[u],sg[a[u]]);
        }
    }
}

int main()
{
    init();
    solve();
    return 0;
}