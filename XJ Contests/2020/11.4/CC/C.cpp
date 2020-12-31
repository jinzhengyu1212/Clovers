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
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
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
int n,m; pii E[N<<1];
vector<int> v[N];

int tot=0;
namespace DSU{
    int fa[N],sz[N];
    pii opt[N<<3];
    void init(){for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1; tot=0;}
    int getfather(int x){
        if(x==fa[x]) return x;
        return getfather(fa[x]);
    }
    bool unite(int x,int y){
        x=getfather(x); y=getfather(y);
        if(x==y) return 0;
        if(sz[x]<sz[y]) swap(x,y);
        fa[y]=x; sz[x]+=sz[y];
        opt[++tot]=mk(x,y);
        return 1;
    }
    void back(int pre){
        while(tot!=pre){
            int x=opt[tot].first,y=opt[tot].second; tot--;
            sz[x]-=sz[y]; fa[y]=y;
        }
    }
}

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y; x=read(); y=read();
        v[x].push_back(y);
        v[y].push_back(x);
        E[i]=mk(x,y);
    }
}
int col[N];
vector<int> G[N];
int flag,vis[N];
void dfs(int u,int f){
    int U=0; vis[u]=1;
    for(int i=0;i<sz(G[u]);i++){
        int to=G[u][i]; 
        if(to==f){
            if(U==1) flag=0;
            U=1;
            continue;
        }
        if(vis[to]) flag=0;
        else dfs(to,u);
    }
}
bool check(){
    for(int i=1;i<=n;i++) G[i].clear(),vis[i]=0;
    for(int i=1;i<=m;i++){
        int x=E[i].first,y=E[i].second;
        if(col[x]==col[y]) G[x].push_back(y),G[y].push_back(x);
    }
    flag=1;
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs(i,-1);
    }
    return flag;
}
namespace solver1{
    void main(){
        int full=(1<<n)-1;
        for(int mask=0;mask<=full;mask++){
            for(int i=1;i<=n;i++){
                if(mask>>(i-1)&1) col[i]=1;
                else col[i]=2;
            }
            if(check()){
                for(int i=1;i<=n;i++) printf("%d ",col[i]);
                puts("");
                return;
            }
        }
        puts("-1");
    }
}

int a[N],in[N];
bool process(){
    DSU::init();
    for(int i=1;i<=n;i++) col[i]=1,in[i]=0;
    for(int i=1;i<=n;i++){
        int pre=tot,u=a[i];
        for(int j=0;j<(int)v[u].size();j++){
            int to=v[u][j];
            if(!in[to]) continue;
            if(!DSU::unite(u,to)){
                col[u]=2;
                DSU::back(pre);
                break;
            }
        }
        if(col[u]==1) in[u]=1;
    }
    return check();
}

void solve(){
    if(n<=10){
        solver1::main();
        return;
    }
    for(int i=1;i<=n;i++) a[i]=i;
    int TI=min(100,2000000/n);
    while(TI--){
        random_shuffle(a+1,a+n+1);
        if(process()){
            for(int i=1;i<=n;i++) printf("%d ",col[i]);
            return;
        }
    }
    puts("-1");
}

int main()
{
    srand(19260817);
    init(); solve();
    return 0;
}