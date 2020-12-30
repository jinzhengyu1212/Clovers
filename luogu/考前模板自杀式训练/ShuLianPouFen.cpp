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
int MOD=998244353;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x%MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? (x%MOD+MOD)%MOD : x;}
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
int n,m,Rt;
vector<int> v[N];

int fa[N],sz[N],son[N],top[N],dfn[N],out[N],cnt=0,id[N],a[N],dep[N];
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
    dfn[u]=++cnt; id[cnt]=u;
    if(son[u]) top[son[u]]=top[u],dfs2(son[u]);
    for(auto &to : v[u]){
        if(to==fa[u]||to==son[u]) continue;
        top[to]=to; dfs2(to);
    }
    out[u]=cnt;
}

struct Segment_Tree{
    int sum[N<<2],tag[N<<2];
    void pushup(int x){sum[x]=add(sum[x<<1],sum[x<<1|1]);}
    void pushdown(int x,int l,int mid,int r){
        if(!tag[x]) return;
        Add(tag[x<<1],tag[x]); Add(tag[x<<1|1],tag[x]);
        Add(sum[x<<1],mul(tag[x],mid-l+1));
        Add(sum[x<<1|1],mul(tag[x],r-mid));
        tag[x]=0;
    }
    void build(int x,int l,int r){
        if(l==r){sum[x]=a[id[l]]; return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid); build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void update(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            Add(sum[x],mul(r-l+1,val));
            Add(tag[x],val);
            return;
        }
        int mid=(l+r)>>1;
        pushdown(x,l,mid,r);
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x);
    }
    int query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[x];
        int mid=(l+r)>>1;
        pushdown(x,l,mid,r);
        int ret=0;
        if(mid>=L) Add(ret,query(x<<1,l,mid,L,R));
        if(mid<R) Add(ret,query(x<<1|1,mid+1,r,L,R));
        return ret;
    }
}tree;

void init(){
    n=read(); m=read(); Rt=read(); MOD=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs1(Rt);
    top[Rt]=Rt; dfs2(Rt);
    tree.build(1,1,n);
}

int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
        else y=fa[top[y]];
    }
    return dep[x]>dep[y] ? y : x;
}

void change(int x,int F,int val){
    while(top[x]!=top[F]){
        int to=top[x],u=fa[to];
        tree.update(1,1,n,dfn[to],dfn[x],val);   
        x=u;
    }
    tree.update(1,1,n,dfn[F],dfn[x],val);
}

int query(int x,int F){
    int ret=0;
    while(top[x]!=top[F]){
        int to=top[x],u=fa[to];
        Add(ret,tree.query(1,1,n,dfn[to],dfn[x]));
        x=u;
    } 
    Add(ret,tree.query(1,1,n,dfn[F],dfn[x]));
    return ret;
}

void update_path(int x,int y,int val){
    int lca=LCA(x,y);
    change(x,lca,val);
    change(y,lca,val);
    tree.update(1,1,n,dfn[lca],dfn[lca],(-val%MOD+MOD)%MOD);
}

int query_path(int x,int y){
    int lca=LCA(x,y),ret=0;
    Add(ret,query(x,lca));
    Add(ret,query(y,lca));
    return sub(ret,tree.query(1,1,n,dfn[lca],dfn[lca]));
}

void solve(){
    //out(dfn[2]); outln(out[2]);
    while(m--){
        int opt=read(),x,y,z;
        if(opt==1){
            x=read(),y=read(),z=read();
            update_path(x,y,z);
        }
        else if(opt==2){
            x=read(),y=read();
            printf("%d\n",query_path(x,y));
        }
        else if(opt==3){
            x=read(),z=read();
            tree.update(1,1,n,dfn[x],out[x],z);
        }
        else if(opt==4){
            x=read();
            printf("%d\n",tree.query(1,1,n,dfn[x],out[x]));
        }
    }
}

int main()
{
    init(); solve();
    return 0;
}