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
    int from,to,cost,lca;
}P[N];
vector<int> v[N];
int fa[N][20],n,m,dep[N];

void dfs1(int u,int f){
    for(auto &to : v[u]){
        if(to==f) continue;
        fa[to][0]=u; dep[to]=dep[u]+1;
        for(int i=1;i<20;i++) fa[to][i]=fa[fa[to][i-1]][i-1];
        dfs1(to,u);
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int ans=0;
void init(){
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    } 
    m=read();
    dep[1]=1; dfs1(1,-1);
    for(int i=1;i<=m;i++){
        P[i].from=read(); P[i].to=read();
        P[i].cost=read(); P[i].lca=LCA(P[i].from,P[i].to);
    }
}
vector<Path> T;
bool isfa(int x,int y){return x==LCA(x,y);}
void solve(){
    int full=(1<<m)-1;
    for(int S=1;S<=full;S++){
        T.clear(); int sum=0;
        for(int i=1;i<=m;i++){
            if(S>>(i-1)&1) T.push_back(P[i]),sum+=P[i].cost;
        }
        int flag=1;
        for(int i=0;i<sz(T);i++){
            for(int j=0;j<sz(T);j++) if(i!=j){
                if(isfa(T[i].lca,T[j].from)||isfa(T[i].lca,T[j].to)) 
                    if(dep[T[i].lca]>=dep[T[j].lca]) flag=0;
            }
        }
        if(flag) checkmax(ans,sum);
    }
    cout<<ans<<endl;
}

int main()
{
    init(); solve();
    return 0;
}