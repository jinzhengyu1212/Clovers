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
const int N=200005;
struct Edge{
    int from,to;
}E[N];
vector<int> v[N],G[N];//B A
int n,s1,s2;
int bl[N];
int dep1[N],dep2[N],fa[N];
void dfs1(int u,int f){
    for(auto &to : G[u]) if(to!=f) dep1[to]=dep1[u]+1,dfs1(to,u);
}
void dfs2(int u,int f){
    for(auto &to : v[u]) if(to!=f) dep2[to]=dep2[u]+1,fa[to]=u,dfs2(to,u);
}
void dfs3(int u,int f){
    bl[u]=1;
    for(auto &to : G[u]){
        if(to==f) continue;
        if(dep1[to]<dep2[to]) dfs3(to,u);
    }
}

bool check(int x,int y){
    if(dep2[x]<dep2[y]) swap(x,y);
    if(fa[fa[x]]==y||fa[x]==fa[y]||fa[x]==y) return 0;
    else return 1;
}

int main()
{
    n=read(); s1=read(); s2=read();
    if(s1==s2){puts("0"); return 0;}
    for(int i=1;i<n;i++){
        E[i].from=read(),E[i].to=read();
        G[E[i].from].push_back(E[i].to);
        G[E[i].to].push_back(E[i].from);
    }
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs1(s1,-1); dfs2(s2,-1); dfs3(s1,-1);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!bl[i]) continue;
        for(auto &to : G[i]){
            if(check(i,to)){puts("-1"); return 0;}           
        }
        checkmax(ans,dep2[i]*2);
    }
    cout<<ans<<endl;
    return 0;
}