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
const int N=500005;
int n,m,vis[N]; pii E[N];
map<pii,int> mp;
vector<int> v[N],G[N];
vector<pii> ans;
int out[N];

void dfs1(int u){
    vis[u]=1;
    for(auto &to : G[u]){
        if(vis[to]) continue;
        mp[mk(u,to)]=1; mp[mk(to,u)]=1;
        dfs1(to); v[u].push_back(to);
    }
}

void dfs2(int u,int f){
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs2(to,u);
    }
    if(f==-1) return;
    if(out[u]&1) ans.push_back(mk(u,f));
    else ans.push_back(mk(f,u)),out[f]++;
}

int main()
{
    n=read(); m=read();
    if(m&1){puts("-1"); return 0;}
    for(int i=1;i<=m;i++){
        E[i].first=read(),E[i].second=read();
        G[E[i].first].push_back(E[i].second);
        G[E[i].second].push_back(E[i].first);
    }
    memset(vis,0,sizeof(vis));
    dfs1(1);
    for(int i=1;i<=m;i++){
        if(!mp.count(E[i])){
            ans.push_back(E[i]);
            out[E[i].first]++;
        }
    }
    dfs2(1,-1);
    for(int i=0;i<m;i++) printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}