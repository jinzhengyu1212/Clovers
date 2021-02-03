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
const int N=2005;
int dep[N],n,sz[N]; char s[N];
vector<int> v[N];

void dfs1(int u,int f){
    sz[u]=(s[u]=='1');
    for(auto &to : v[u]){
        if(to==f) continue;
        dep[to]=dep[u]+1; dfs1(to,u); sz[u]+=sz[to];
    }
}
int f[N],g[N];
void dfs2(int u,int F){
    f[u]=g[u]=0;
    for(auto &to : v[u]){
        if(to==F) continue;
        dfs2(to,u);
        if(f[u]>g[to]+sz[to]) f[u]-=(g[to]+sz[to]);
        else if(g[u]<f[to]+sz[to]) f[u]=f[to]+sz[to]-g[u];
        else f[u]=(g[u]+g[to]+sz[to])%2;
        g[u]+=g[to]+sz[to];
    }
}

int ans=inf;
int main()
{
    n=read(); scanf("%s",s+1);
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    for(int rt=1;rt<=n;rt++){
        dep[rt]=0; dfs1(rt,-1);
        dfs2(rt,-1);
        if(f[rt]==0) checkmin(ans,g[rt]/2);
    }
    if(ans==inf) puts("-1");
    else printf("%d\n",ans);
    return 0;
}