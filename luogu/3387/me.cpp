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
const int N=50005;
const int M=200005;
vector<int> v[N],G[N];
int n,m;
int scc[N],tot=0,val[N];
int dfn[N],low[N],dfn_clock=0;
int dp[N],in[N];
stack<int> stk;
void tarjan(int u){
    dfn[u]=++dfn_clock;
    low[u]=dfn[u];
    stk.push(u);
    for(auto &to : v[u]){
        if(!dfn[to]){
            tarjan(to);
            checkmin(low[u],low[to]);
        }
        else if(!scc[to]){
            checkmin(low[u],dfn[to]);
        }
    }
    //out(u),out(low[u]),outln(dfn[u]);
    if(low[u]==dfn[u]){
        scc[u]=++tot; dp[tot]+=val[u];
        while(stk.top()!=u)
            scc[stk.top()]=tot,dp[tot]+=val[stk.top()],stk.pop();
        stk.pop();
    }
}

pii E[M];
void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        E[i]=mk(x,y);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=m;i++){
        int x=scc[E[i].first],y=scc[E[i].second];
        if(x!=y) G[x].push_back(y),in[y]++;;
        
    }
}

void solve(){
    queue<int> q;
    for(int i=1;i<=tot;i++) if(!in[i]) q.push(i);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto &to : G[u]){
            if(!--in[to]) q.push(to),dp[to]+=dp[u];
        }
    }
    int ans=0;
    for(int i=1;i<=tot;i++) checkmax(ans,dp[i]);
    cout<<ans<<endl;
}

int main()
{
    init(); solve();
    return 0;
}