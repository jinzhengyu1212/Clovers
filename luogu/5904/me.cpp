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
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
#define int long long 
const int N=100005;
int n,*f[N<<2],*g[N<<2],ans=0,tmp[N<<2],*it=tmp;
vector<int> v[N],V;
int dep[N],son[N];
void dfs1(int u,int fa){
    for(auto to : v[u]){
        if(to==fa) continue;
        dfs1(to,u); dep[u]=(dep[u],dep[to]+1ll);
        if(dep[to]>dep[son[u]]) son[u]=to;
    }
    dep[u]=dep[son[u]]+1;
}

void dfs(int u,int fa){
    if(son[u]) f[son[u]]=f[u]+1, g[son[u]]=g[u]-1, dfs(son[u],u);
    f[u][0]=1; ans+=g[u][0]; 
    for(auto to : v[u]){
        if(to==fa||to==son[u]) continue;
        f[to]=it; it+=dep[to]<<1; g[to]=it; it+=dep[to]<<1;  
        dfs(to,u);
        for(int j=0;j<dep[to];j++){
            if(j) ans+=f[u][j-1]*g[to][j];
            ans+=f[to][j]*g[u][j+1];
        }
        for(int j=0;j<dep[to];j++){
            g[u][j+1]+=f[to][j]*f[u][j+1];
            if(j) g[u][j-1]+=g[to][j];
            f[u][j+1]+=f[to][j];
        }
    }
}

void init(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
}

signed main()
{
    init(); dfs1(1,-1); 
    f[1]=it; g[1]=it+(dep[1]<<1); it+=(dep[1]<<2);
    dfs(1,-1);
    cout<<ans<<endl;
    return 0;
}