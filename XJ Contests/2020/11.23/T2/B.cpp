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
int MOD=998244353;
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
int n,T,m; vector<int> v[N];
int sz[N],fac[N],ifac[N],in[N];
int C(int n,int m){
    return mul(fac[n],mul(ifac[n-m],ifac[m]));
}

queue<int> q;
void init(){
    n=read(); m=read(); MOD=read();
    for(int i=1;i<=n;i++) v[i].clear(),in[i]=0;
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y); in[y]++;
    }
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
}

int now,ans=0;
int vis[N];
void dfs1(int u){
    sz[u]=1; vis[u]=1;
    for(int i=0;i<sz(v[u]);i++){
        int to=v[u][i]; if(vis[to]) continue; 
        dfs1(to); sz[u]+=sz[to];
    }
}

int dfs2(int u){
    sz[u]--; 
    int ret=1; vis[u]=1;
    if(sz[u]==0) return 1;
    for(int i=0;i<sz(v[u]);i++){
        int to=v[u][i]; if(vis[to]) continue;
        int tmp=sz[to];
        Mul(ret,mul(C(sz[u],tmp),dfs2(to)));
        sz[u]-=tmp;
    }
    return ret;
}

void solve(){
    for(int i=1;i<=n;i++) if(!in[i]) v[0].push_back(i);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=0;i<sz(v[u]);i++){
            int to=v[u][i]; 
            if(!--in[to]) q.push(to);
        }
    }
    for(int i=1;i<=n;i++) if(in[i]){
        puts("0");
        return;
    }
    for(int i=0;i<=n;i++) vis[i]=0;
    dfs1(0);
    for(int i=0;i<=n;i++) vis[i]=0;
    printf("%d\n",dfs2(0));
}

int main()
{
    T=read();
    while(T--){
        init();
        fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
        ifac[n]=qpow(fac[n],MOD-2);
        for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
        solve();
    }
    return 0;
}