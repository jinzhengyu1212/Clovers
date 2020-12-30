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
vector<pii> v[N],G[N];
int m,n,k;
namespace solver1{
    int fa[1005][16]; ll dis[1005],dep[1005];
    void dfs(int u,int f){
        for(auto &to : v[u]){
            if(to.first==f) continue;
            dis[to.first]=dis[u]+to.second;
            dep[to.first]=dep[u]+1;
            fa[to.first][0]=u; 
            for(int i=1;i<16;i++) fa[to.first][i]=fa[fa[to.first][i-1]][i-1];
            dfs(to.first,u);
        }
    }
    int LCA(int x,int y){
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=15;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
        if(x==y) return x;
        for(int i=15;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
        return fa[x][0];
    }
    vector<ll> ans;
    void main(){
        dep[1]=1; dfs(1,-1);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                ll tmp=dis[i]+dis[j]-2*dis[LCA(i,j)];
                ans.push_back(tmp);
            }
        }
        sort(ans.begin(),ans.end()); reverse(ans.begin(),ans.end());
        for(int i=0;i<k;i++) printf("%lld\n",ans[i]);
    }        
}

void rebuild(int u,int fa){
    int cnt=0,lst=0;
    for(auto &to : v[u]){
        if(to.first==fa) continue;
        cnt++;
        if(cnt==1){
            G[u].push_back(to);
            G[to.first].push_back(mk(u,to.second));
            lst=u;
        }
        else if(cnt==sz(v[u])-(u!=1)){
            G[lst].push_back(to);
            G[to.first].push_back(mk(lst,to.second));
        }
        else{
            m++;
            G[lst].push_back(mk(m,0));
            G[m].push_back(mk(lst,0));
            G[m].push_back(to); 
            G[to.first].push_back(mk(m,to.second));
            lst=m;
        }
    }
}
void dfs1(int u,int f){
    rebuild(u,f);
    for(auto &to : v[u]){
        if(to.first==f) continue;
        dfs1(to.first,u);
    }   
}
void init(){
    dfs1(1,-1); 
    for(int i=1;i<=m;i++) v[i]=G[i],G[i].clear();
}
pii Edg; int Edgval;
int sz[N],mi,vis[N];
ll dep[N];
void findedge(int u,int f,int S){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to.first==f||vis[to.first]) continue;
        findedge(to.first,u,S); sz[u]+=sz[to.first];
        if(mi>max(sz[to.first],S-sz[to.first])){
            mi=max(sz[to.first],S-sz[to.first]);
            Edg=mk(u,to.first); Edgval=to.second;
        }
    }
}
vector<ll> A,B;
void dfs2(int u,int f,int flag){
    sz[u]=1; 
    if(flag){
        if(u<=n) B.push_back(dep[u]);
    }
    else if(u<=n) A.push_back(dep[u]);
    for(auto &to : v[u]){
        if(to.first==f||vis[to.first]) continue;
        dep[to.first]=dep[u]+to.second;
        dfs2(to.first,u,flag); sz[u]+=sz[to.first];
    }
}
ll Sum=0;
ll best,mid;
void solve1(int u,int Sz){
    if(Sz==1) return; mi=inf;
    findedge(u,-1,Sz); A.clear(); B.clear();
    dep[Edg.first]=0; dep[Edg.second]=0;
    vis[Edg.first]=1; dfs2(Edg.second,-1,1); vis[Edg.first]=0;
    vis[Edg.second]=1; dfs2(Edg.first,-1,0); vis[Edg.second]=0;
    sort(B.begin(),B.end());
    //out(u); out(Edg.first); out(Edg.second); outln(Edgval);
    //cout<<"A:"; for(auto &to : A) cout<<to<<" "; cout<<endl;
    //cout<<"B:"; for(auto &to : B) cout<<to<<" "; cout<<endl;
    for(auto &u : A){
        int pos=lower_bound(B.begin(),B.end(),0ll+mid-u-Edgval)-B.begin();
        Sum+=sz(B)-pos;
        if(Sum>=k) return;
    }
    int tmpA=Edg.first,tmpB=Edg.second;
    vis[tmpA]=1; solve1(tmpB,sz[tmpB]); vis[tmpA]=0;
    if(Sum>=k) return;
    vis[tmpB]=1; solve1(tmpA,sz[tmpA]); vis[tmpB]=0;
}
bool check(){
    Sum=0; memset(vis,0,sizeof(vis));
    solve1(1,m);
    return Sum>=k;
}
void findval(){
    ll l=1,r=2e14;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()) l=mid+1,best=mid;
        else r=mid-1;
    }
}

vector<ll> ANS; 
void solve2(int u,int Sz){
    if(Sz==1) return; mi=inf;
    findedge(u,-1,Sz); A.clear(); B.clear();
    dep[Edg.first]=0; dep[Edg.second]=0;
    vis[Edg.first]=1; dfs2(Edg.second,-1,1); vis[Edg.first]=0;
    vis[Edg.second]=1; dfs2(Edg.first,-1,0); vis[Edg.second]=0;
    sort(B.begin(),B.end());
    // out(u); out(Edg.first); out(Edg.second); outln(Edgval);
    // cout<<"A:"; for(auto &to : A) cout<<to<<" "; cout<<endl;
    // cout<<"B:"; for(auto &to : B) cout<<to<<" "; cout<<endl;
    for(auto &u : A){
        int pos=upper_bound(B.begin(),B.end(),0ll+best-u-Edgval)-B.begin();
        for(int i=pos;i<sz(B);i++) ANS.push_back(u+Edgval+B[i]);
    }
    int tmpA=Edg.first,tmpB=Edg.second;
    vis[tmpA]=1; solve2(tmpB,sz[tmpB]); vis[tmpA]=0;
    vis[tmpB]=1; solve2(tmpA,sz[tmpA]); vis[tmpB]=0;
}

int main()
{
    n=read(); m=n; k=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read(),z=read();
        v[x].push_back(mk(y,z)); v[y].push_back(mk(x,z));
    }
    if(n<=1000){
        solver1::main();
        return 0;
    }
    return 0;
}