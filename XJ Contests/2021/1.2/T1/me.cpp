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
struct Path{
    int from,to,cost;
};
vector<Path> P[N];
vector<int> v[N];
int fa[N],n,m,dep[N],dp[N],sum[N],sum2[N];
int sz[N],top[N],son[N],f[N][20];

void dfs1(int u){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to==fa[u]) continue;
        fa[to]=u; f[to][0]=u; dep[to]=dep[u]+1;
        for(int i=1;i<20;i++) f[to][i]=f[f[to][i-1]][i-1];
        dfs1(to); sz[u]+=sz[to];
        if(sz[to]>sz[son[u]]) son[u]=to;
    }
}
void dfs2(int u){
    if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
    for(auto &to : v[u]){
        if(to==fa[u]||to==son[u]) continue;
        top[to]=to; dfs2(to);
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y]) dep[top[x]]<dep[top[y]] ? y=fa[top[y]] : x=fa[top[x]];
    return (dep[x] < dep[y] ? x : y);
}
int jump(int x,int F){
    for(int i=19;i>=0;i--) if(dep[f[x][i]]>dep[F]) x=f[x][i];
    return x;
}
int calc(int x,int F){
    int flag=0; if(x==3&&F==2) flag=1;
    int ret=sum[x]; 
    if(x==F) return ret;
    while(top[x]!=top[F]){
        int u=top[x];
        ret+=sum2[u]-sum2[x];
        ret+=sum[fa[u]]-dp[u];
        x=fa[u];
    }
    ret+=sum2[F]-sum2[x];
    return ret;
}

void init(){
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    } 
    m=read();
    dep[1]=1; dfs1(1); top[1]=1; dfs2(1);
    for(int i=1;i<=m;i++){
        Path x;
        x.from=read(); x.to=read(); x.cost=read();
        P[LCA(x.from,x.to)].push_back(x);
    }
}

void dfs3(int u,int f){
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs3(to,u); sum[u]+=dp[to];
    }
    dp[u]=sum[u]; sum2[u]=sum[u]-dp[son[u]]+sum2[son[u]];
    for(auto &l : P[u]){
        int x=l.from,y=l.to,w=l.cost;
        int xx=jump(x,u),yy=jump(y,u);
        int tmp1=(x==u ? 0 : calc(x,xx)-dp[xx]);
        int tmp2=(y==u ? 0 : calc(y,yy)-dp[yy]);
        //out(u); out(sum[u]); out(x); out(xx); out(y); out(yy); out(tmp1); outln(tmp2);
        checkmax(dp[u],sum[u]+tmp1+tmp2+w);
    }
    //out(u); out(dp[u]); outln(sum2[u]);
}

int main()
{
    init(); dfs3(1,-1);
    cout<<dp[1]<<endl;
    return 0;
}