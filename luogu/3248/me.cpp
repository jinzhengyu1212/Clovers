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
const int N=230005;
int n,m,Q;
int dep[N],sz[N]; vector<int> v[N];
vector<pii> G[N];
int dfn[N],id[N],dfn_clock=0,out[N];
int ffa[N][23];
void dfs1(int u,int f){
    dfn[u]=++dfn_clock; id[dfn_clock]=u;
    sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dep[to]=dep[u]+1; ffa[to][0]=u;
        for(int i=1;i<23;i++) ffa[to][i]=ffa[ffa[to][i-1]][i-1];
        dfs1(to,u); sz[u]+=sz[to];
    }
    out[u]=dfn_clock;
}

int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=22;i>=0;i--) if(dep[ffa[x][i]]>=dep[y]) x=ffa[x][i];
    if(x==y) return x;
    for(int i=22;i>=0;i--) if(ffa[x][i]!=ffa[y][i]) x=ffa[x][i],y=ffa[y][i];
    return ffa[x][0];
}
int dist(int x,int y){
    return dep[x]+dep[y]-2*dep[LCA(x,y)];
}

int tot;
struct Chairman_Tree{
    int ls[N<<5],rs[N<<5],sum[N<<5];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void build(int x,int l,int r){
        sum[x]=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        ls[x]=++tot,rs[x]=++tot; 
        build(ls[x],l,mid); build(rs[x],mid+1,r);
    }
    void insert(int x,int y,int l,int r,int pos){
        if(l==r){sum[x]=sum[y]+1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,rs[x]=rs[y],insert(ls[x],ls[y],l,mid,pos);
        else rs[x]=++tot,ls[x]=ls[y],insert(rs[x],rs[y],mid+1,r,pos);
        pushup(x);
    }
    int query(int x,int y,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,tmp=sum[ls[y]]-sum[ls[x]];
        if(k>tmp) return query(rs[x],rs[y],mid+1,r,k-tmp);
        else return query(ls[x],ls[y],l,mid,k);
    }
}tree;

void init(){
    n=read(); tot=n; m=read(); Q=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y),v[y].push_back(x);
    }
    dep[1]=1; dfs1(1,-1);
    tree.build(0,1,n);
    for(int i=1;i<=n;i++) tree.insert(i,i-1,1,n,id[i]);
}

int Rt[N],opt[N];//tmpid
int cnt=1; ll sum[N];
int Fa[N];
void connect(ll B,int id){
    int pos=lower_bound(sum+1,sum+id+1,B)-sum;
    int delta=B-sum[pos-1];
    B=tree.query(dfn[Rt[pos]]-1,out[Rt[pos]],1,n,delta);
    int dis=dep[B]-dep[Rt[pos]]+1; Fa[opt[id]]=B;
    G[opt[pos]].push_back(mk(opt[id],dis));
}

void prepare(){
    sum[1]=n; Rt[1]=1; opt[1]=1;
    for(int i=2;i<=m+1;i++){
        int A=read(); ll B; scanf("%lld",&B);
        Rt[i]=A; opt[i]=++cnt;
        sum[i]=sum[i-1]+sz[A];
        connect(B,i);
    }
}

ll dep2[N]; int fa[N][23],Dep[N];
void dfs2(int u,int f){
    for(auto &to : G[u]){
        if(to.first==f) continue;
        dep2[to.first]=dep2[u]+to.second; 
        Dep[to.first]=Dep[u]+1;
        fa[to.first][0]=u;
        for(int i=1;i<23;i++) fa[to.first][i]=fa[fa[to.first][i-1]][i-1];
        dfs2(to.first,u);
    }
}

int bx,by,rx,ry;
void decode(ll &x,int flag){
    int pos=lower_bound(sum+1,sum+m+1,x)-sum;
    int delta=x-sum[pos-1];
    x=tree.query(dfn[Rt[pos]]-1,out[Rt[pos]],1,n,delta);
    if(flag==1) bx=opt[pos],rx=Rt[pos]; else by=opt[pos],ry=Rt[pos];
}

void process(ll &ans,ll &x,ll &y){
    if(bx==by) return; 
    if(Dep[bx]<Dep[by]) swap(x,y),swap(bx,by),swap(rx,ry);
    ans+=dep[x]-dep[rx],x=rx;
    for(int i=22;i>=0;i--) if(Dep[fa[bx][i]]>Dep[by]) 
        ans+=dep2[bx]-dep2[fa[bx][i]],
        bx=fa[bx][i],rx=Rt[bx];
    if(Dep[bx]>Dep[by]) ans++,x=Fa[bx],bx=fa[bx][0],rx=Rt[bx];
    if(bx==by) return;
    ans+=dep[y]-dep[ry],y=ry;
    ans+=dep[x]-dep[rx],x=rx;
    for(int i=22;i>=0;i--) if(fa[bx][i]!=fa[by][i]) 
        ans+=dep2[bx]-dep2[fa[bx][i]],
        ans+=dep2[by]-dep2[fa[by][i]],
        bx=fa[bx][i],by=fa[by][i];
    ans+=2; x=Fa[bx],y=Fa[by];
}

void solve(){
    Dep[1]=1; dfs2(1,-1);
    while(Q--){
        ll x,y; scanf("%lld%lld",&x,&y);
        ll ans=0;
        decode(x,1); decode(y,2);
        process(ans,x,y);
        ans+=dist(x,y);
        printf("%lld\n",ans);
    }
}

signed main()
{
    init();
    prepare();
    solve();
    return 0;
}