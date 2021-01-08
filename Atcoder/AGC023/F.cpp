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
struct node{
    ll sum,sz; int id;
    bool operator < (const node &rhs) const{
        if(sum*rhs.sz==rhs.sum*sz) return id<rhs.id;
        return sum*rhs.sz>rhs.sum*sz;
    }
};
set<node> st;
int n,m=0,dp[N],t[N],fa[N]; 
ll a[N],sz[N];
vector<int> v[N];

void dfs(int u,int from){
    int id=(t[u]==1 ? ++m : from);
    for(auto &to : v[u]){
        dfs(to,id); dp[u]+=dp[to];
    }
    if(t[u]==1){
        fa[id]=from; a[id]=dp[u];
        dp[u]=0;
    }
    else dp[u]++;
}

void init(){
    n=read();
    for(int i=2;i<=n;i++){
        int fa=read();
        v[fa].push_back(i);
    }
    for(int i=1;i<=n;i++) t[i]=read();
    dfs(1,0);
}
namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=m;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){fa[getfather(x)]=getfather(y);}
}

int b[N],nxt[N],top=0,vis[N],Copy[N],lst[N];
void solve(){
    for(int i=1;i<=m;i++) st.insert({1ll*a[i],1ll,i});
    for(int i=1;i<=m;i++) sz[i]=1,Copy[i]=a[i],lst[i]=i;
    DSU::init();
    while(!st.empty()){
        int u=st.begin()->id;
        st.erase(st.begin());
        if(!fa[u]||vis[fa[u]]){
            int x=u;
            while(x) vis[x]=1,b[++top]=x,x=nxt[x];
        }
        else{
            int F=DSU::getfather(fa[u]);
            st.erase({a[F],sz[F],F});
            nxt[lst[F]]=u; lst[F]=lst[u];
            a[F]+=a[u]; sz[F]+=sz[u];
            st.insert({a[F],sz[F],F});
        }
        DSU::unite(u,fa[u]);
    }
    ll ans=0;
    for(int i=1;i<=m;i++) ans+=1ll*i*Copy[b[i]];
    cout<<ans<<endl;
}

int main()
{
    init(); solve();
    return 0;
}