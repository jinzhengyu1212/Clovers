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

int n,m,k,top=0,lst[N<<3],ans=1;
pii A[N<<3];
namespace DSU{
    int fa[N<<1],sz[N<<1];
    void init(){for(int i=1;i<=n+n;i++) sz[i]=1,fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : getfather(fa[x]);}
    void merge(int x,int y){
        if(x==y){A[top]=mk(0,0); return;}
        if(sz[x]<sz[y]) swap(x,y);
        A[top]=mk(x,y);
        sz[x]+=sz[y]; fa[y]=x;
    }
    bool unite(int x,int y){
        top++;
        int xx=getfather(x+n),yy=getfather(y+n);
        x=getfather(x); y=getfather(y);
        if(x==y){lst[top]=top; ans=0; return 0;}
        lst[top]=lst[top-1];
        merge(xx,y); top++; merge(x,yy);
        lst[top]=lst[top-1];
        return 1;
    }
    void back(int pre){
        if(lst[pre]==0) ans=1;
        while(top>pre){
            if(lst[top]==top||A[top].first==0){top--; continue;}
            int x=A[top].first,y=A[top].second; top--;
            sz[x]-=sz[y]; fa[y]=y;
        }
    }
}

int ret[N];
struct Segment_Tree{
    vector<pii> v[N<<2];
    void update(int x,int l,int r,int L,int R,pii E){
        if(L>R) return;
        if(L<=l&&r<=R){v[x].push_back(E); return;}
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R,E);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,E);
    }
    void dfs(int u,int l,int r){
        int pre=top;
        for(auto &x : v[u]){
            DSU::unite(x.first,x.second);
        }
        if(l==r){ret[l]=ans; DSU::back(pre); return;}
        int mid=(l+r)>>1;
        dfs(u<<1,l,mid); dfs(u<<1|1,mid+1,r);
        DSU::back(pre);
    }
}tree;

void init(){
    n=read(); m=read(); k=read();
    DSU::init();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),l=read()+1,r=read();
        tree.update(1,1,k,l,r,mk(x,y));  
    }
}

int main()
{
    init();
    tree.dfs(1,1,k);
    for(int i=1;i<=k;i++) (ret[i] ? puts("Yes") : puts("No"));
    return 0;
}