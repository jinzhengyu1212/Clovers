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
const int N=105;
pii E[N*N];
int n,m,mp[N][N],mp2[N][N],a[N];
void print(){
    for(int i=1;i<=m;i++){
        int u=E[i].first,v=E[i].second;
        assert(mp2[u][v]+mp2[v][u]==1);
        if(mp2[u][v]) puts("->");
        else puts("<-");
    }
}

int dfn_clock=0,dfn[N],low[N];
int cnt=0,scc[N];

stack<int> stk;
void dfs(int u,int f){
    dfn[u]=++dfn_clock; low[u]=dfn[u];
    stk.push(u);
    for(int to=1;to<=n;to++) if(a[u]==a[to]&&mp[u][to]&&to!=f){
        if(!mp2[to][u]) mp2[u][to]=1;
        if(dfn[to]) checkmin(low[u],dfn[to]);
        else dfs(to,u),checkmin(low[u],low[to]);
    }
    if(low[u]==dfn[u]){
        cnt++;
        while(stk.top()!=u){
            int now=stk.top(); stk.pop();
            scc[now]=cnt;
        }
        scc[u]=cnt; stk.pop();
    }
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        E[i].first=read(); E[i].second=read();
        mp[E[i].first][E[i].second]=1;
        mp[E[i].second][E[i].first]=1;
    }
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,-1);
    //for(int i=1;i<=n;i++) cout<<i<<" "<<scc[i]<<endl;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)if(scc[i]!=scc[j]&&mp[i][j]){
            if(a[i]>a[j]) mp2[i][j]=1;
            else mp2[j][i]=1;
        }
    }
    print();
    return 0;
}