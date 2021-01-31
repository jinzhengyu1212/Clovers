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
const int N=405;
int n,sz[N],k,dep[N],bl[N]; 
vector<int> v[N];
void dfs1(int u,int f){
    if(dep[u]>k) return;
    else if(dep[u]==k) bl[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dep[to]=dep[u]+1;
        dfs1(to,u); bl[u]|=bl[to];
    }
}

int dfn[N],id[N],dfn_clock=0,cnt=0;
void dfs2(int u,int f){
    dfn[u]=++dfn_clock; id[dfn_clock]=u;
    sz[u]=1; cnt++;
    for(auto &to : v[u]){
        if(to==f) continue;
        if(bl[to]) dfs2(to,u),sz[u]+=sz[to];
    }
}

bool dp[N][1<<19];
int main()
{
    n=read(); k=read();
    if(k*k>=n){
        puts("DA");
        return 0;
    }
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs1(1,-1); dfs2(1,-1);
    if(!bl[1]){
        puts("DA");
        return 0;
    }
    int full=(1<<k)-1;
    dp[2][0]=1;
    for(int i=2;i<=cnt;i++){
        int u=id[i];
        for(int S=0;S<=full;S++) if(dp[i][S]){
            if(dep[u]!=k) dp[i+1][S]=1;
            if(S>>(dep[u]-1)&1) continue;
            int to=i+sz[u];
            dp[to][S|(1<<(dep[u]-1))]=1;
        }
    }
    int flag=0;
    for(int S=0;S<=full;S++) flag|=dp[cnt+1][S];
    puts(flag ? "DA" : "NE");
    return 0;
}