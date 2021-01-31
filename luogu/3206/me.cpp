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
const int N=50005;
int n,m,q;
struct Modify{int id,val;}Q[N];
struct Edge{
    int x,y,val,id;
}E[N];
bool cmp(int x,int y){return E[x].val<E[y].val;}
int top=0;
namespace DSU{
    int fa[N],sz[N];
    pii stk[N<<5];
    void init(){for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;}
    int getfather(int x){return x==fa[x] ? x : getfather(fa[x]);}
    void unite(int x,int y){
        x=getfather(x); y=getfather(y);
        if(x==y) return;
        if(sz[x]<sz[y]) swap(x,y);
        fa[y]=x; sz[x]+=sz[y]; stk[++top]=mk(x,y);
    }
    bool same(int x,int y){return getfather(x)==getfather(y);}
    void back(int pre){
        while(top!=pre){
            int x=stk[top].first,y=stk[top].second;
            top--;
            fa[y]=y; sz[x]-=sz[y];
        }
    }
}
vector<int> Mo[N];
void init(){
    n=read(); m=read(); q=read();
    for(int i=1;i<=m;i++) E[i].id=i,E[i].x=read(),E[i].y=read(),E[i].val=read();
    for(int i=1;i<=q;i++) Q[i].id=read(),Q[i].val=read();
}
void print(){
    cout<<"single:";
    for(int i=1;i<=n;i++) if(i==DSU::getfather(i)) cout<<i<<" ";
    cout<<endl;
}

int vis[N],bl[N]; ll ans[N];
void cdq(int l,int r,vector<int> v,ll sum){
    int pre=top;
    if(l==r){
        E[Q[l].id].val=Q[l].val;
        sort(v.begin(),v.end(),cmp);
        for(auto &i : v){
            if(!DSU::same(E[i].x,E[i].y)){
                sum+=E[i].val;
                DSU::unite(E[i].x,E[i].y);
            }
        }
        ans[l]=sum; DSU::back(pre);
        return;      
    }
    vector<int> ret,del,used; 
    ret.clear(),del.clear(),used.clear();
    for(int i=l;i<=r;i++) bl[Q[i].id]=1,E[Q[i].id].val=inf;
    sort(v.begin(),v.end(),cmp);
    for(auto &i : v){
        if(bl[i]) break;
        if(DSU::same(E[i].x,E[i].y)){
            del.push_back(i);
            vis[i]=1;
        }
        else DSU::unite(E[i].x,E[i].y);
    }
    DSU::back(pre);
    for(int i=l;i<=r;i++) E[Q[i].id].val=-inf;
    sort(v.begin(),v.end(),cmp);
    for(auto &i : v){
        if(!DSU::same(E[i].x,E[i].y)){
            DSU::unite(E[i].x,E[i].y);
            if(!bl[i]) used.push_back(i),vis[i]=1,sum+=E[i].val;
        }
    }
    DSU::back(pre);
    for(int i=l;i<=r;i++) bl[Q[i].id]=0;
    for(auto &i : v) if(!vis[i]) ret.push_back(i);
    int mid=(l+r)>>1;
    for(int i=mid+1;i<=r;i++){
        E[Q[i].id].val=Mo[Q[i].id].back();
    }
    for(auto &i : used){
        DSU::unite(E[i].x,E[i].y);
    }
    int pre2=top;
    cdq(l,mid,ret,sum); DSU::back(pre2);
    for(int i=l;i<=mid;i++) {
        E[Q[i].id].val=Q[i].val;
        Mo[Q[i].id].push_back(E[Q[i].id].val);
    }
    cdq(mid+1,r,ret,sum); DSU::back(pre);
    for(int i=l;i<=mid;i++){
        Mo[Q[i].id].pop_back();
        E[Q[i].id].val=Mo[Q[i].id].back();
    }
    for(auto &i : used) vis[i]=0,sum-=E[i].val;
    for(auto &i : del) vis[i]=0;
    used.clear(); del.clear(); ret.clear();
}

int main()
{
    init(); DSU::init();
    vector<int> tmp;
    for(int i=1;i<=m;i++) tmp.push_back(i);
    for(int i=1;i<=m;i++) Mo[i].push_back(E[i].val);
    cdq(1,q,tmp,0);
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    return 0;
}