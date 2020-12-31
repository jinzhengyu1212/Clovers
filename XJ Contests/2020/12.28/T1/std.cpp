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
#define y1 myyakak
#define y2 hcyakak
const int N=100005;
struct node{
    int from,to;
}a[N];
int n,m; vector<int> v[N];

namespace solver1{
    int bl[2][305],dep[2][305],ans=0;
    void dfs(int u,int f,int T,int flag){
        if(u==T){bl[flag][u]=-1; return;}
        for(auto &to : v[u]){
            if(to==f) continue;
            dep[flag][to]=dep[flag][u]+1; 
            dfs(to,u,T,flag);
            if(bl[flag][to]) bl[flag][u]=to;
        }
    }
    bool check(int x,int y){
        if(x==y) return 1;
        while(x!=-1&&y!=-1){
            int xx=bl[0][x],yy=bl[1][y];
            if(xx==y&&yy==x) return 1;
            if(xx==yy&&xx!=-1) return 1;
            x=xx; y=yy;
        }
        return 0;
    }
    void main(){
        for(int i=1;i<m;i++){
            for(int j=i+1;j<=m;j++){
                memset(bl,0,sizeof(bl));
                dfs(a[i].from,-1,a[i].to,0);
                dfs(a[j].from,-1,a[j].to,1);
                //if(check(a[i].from,a[j].from)) cout<<i<<" "<<j<<endl;
                ans+=check(a[i].from,a[j].from);
            }
        }
        cout<<ans<<endl;
    }
}

namespace solver2{
    int son[N],top[N],fa[N],sz[N],ans=0,L[N],dep[N];
    int dfn[N],out[N],dfn_clock=0;
    void dfs1(int u){
        sz[u]=1;
        for(auto &to : v[u]){
            if(to==fa[u]) continue; 
            fa[to]=u; dep[to]=dep[u]+1;
            dfs1(to); sz[u]+=sz[to];
            if(sz[son[u]]<sz[to]) son[u]=to;
        }
    }
    void dfs2(int u){
        dfn[u]=++dfn_clock;
        if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
        for(auto &to : v[u]){
            if(to==fa[u]||to==son[u]) continue;
            top[to]=to; dfs2(to);
        }
        out[u]=dfn_clock;
    }
    bool isfa(int x,int y){return dfn[x]<=dfn[y]&&out[x]>=out[y];}
    int LCA(int x,int y){
        int tmp=0;
        while(top[x]!=top[y]) dep[top[x]]<dep[top[y]] ? y=fa[top[y]] : x=fa[top[x]];
        return (dep[x]>dep[y] ? y : x);
    }
    void main(){
        dep[1]=1; dfs1(1); top[1]=1; dfs2(1);
        for(int i=1;i<=m;i++){
            L[i]=LCA(a[i].from,a[i].to);
        }
        for(int i=1;i<m;i++){
            int lca1=L[i];
            for(int j=i+1;j<=m;j++){
                int lca2=L[j];
                int ttt=0; if(i==1&&j==3) ttt=1;
                if(a[i].from==a[j].from){
                    ans++;
                    continue;
                }
                int x1=a[i].from,x2=a[i].to,y1=a[j].from,y2=a[j].to;
                if(dep[x1]-dep[lca1]>dep[y1]-dep[lca2]) swap(x1,y1),swap(x2,y2),swap(lca1,lca2);
                int dis=dep[x1]-dep[lca1];
                if(dep[y1]-dis<dep[lca1]) continue;
                if(isfa(lca1,lca2)){
                    if(dis+dep[lca2]-dep[lca1]>dep[y1]-dep[lca2]) continue;
                    if(dis+dep[lca2]-dep[lca1]==dep[y1]-dep[lca2]){
                        ans++; 
                        continue;
                    }
                    if(isfa(lca2,x2)){
                        int tmp=LCA(x2,y1);
                        if(dis+dep[tmp]-dep[lca1]>=dep[y1]-dep[tmp]){
                            ans++;
                        }
                    }
                }
                else if(isfa(lca2,lca1)){
                    if(dis==dep[y1]-dep[lca1]){
                        ans++;
                        continue;
                    }
                    int tmp=LCA(x2,y1);
                    if(dis+dep[tmp]-dep[lca1]>=dep[y1]-dep[tmp]){
                        ans++;
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }   
    m=read();
    for(int i=1;i<=m;i++) a[i].from=read(),a[i].to=read();
    if(n<=300&&m<=300){
        solver1::main();
        return 0;
    }
    if(m<=2000){
        solver2::main();
        return 0;
    }
    return 0;
}