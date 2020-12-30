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
int n,m;
vector<int> A[N],B[N];
struct QUERY{
    int opt,x,y;
}Q[N];

namespace solver1{
    ll c[N];
    void main(){
        for(int i=1;i<=n;i++) A[i].push_back(i),B[i].push_back(i);
        while(m--){
            int opt=read(),x,y;
            if(opt==1){
                x=read(),y=read();
                while(!A[y].empty()) A[x].push_back(A[y].back()),A[y].pop_back();
            }
            else if(opt==2){
                x=read(),y=read();
                while(!B[y].empty()) B[x].push_back(B[y].back()),B[y].pop_back();
            }
            else if(opt==3){
                x=read(),y=read();
                for(int i=0;i<sz(A[x]);i++) c[A[x][i]]+=y;
            }
            else if(opt==4){
                x=read(),y=read();
                for(int i=0;i<sz(B[x]);i++) c[B[x][i]]=y;
            }
            else{
                x=read();
                printf("%lld\n",c[x]);
            }
        }
    }
}

namespace solver2{
    ll c[N];
    struct BIT{
        ll a[N];
        int lowbit(int x){return x&(-x);}
        void update(int x,int val){
            for(int i=x;i<=n;i+=lowbit(i)) a[i]+=val;
        }
        ll query(int x){
            ll ret=0;
            for(int i=x;i;i-=lowbit(i)) ret+=a[i];
            return ret;
        }
    }T;
    namespace DSU{
        int fa[N];
        void init(){for(int i=1;i<=n;i++) fa[i]=i;}
        int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
        void unite(int x,int y){//y->x
            x=getfather(x); y=getfather(y);
            fa[y]=x;
        }
        bool same(int x,int y){return getfather(x)==getfather(y);}
    }
    int dfn[N],out[N],dfn_clock=0,vis[N],id[N];
    vector<int> v[N];
    void dfs(int u,int f){
        vis[u]=1;
        dfn[u]=++dfn_clock;
        for(int i=0;i<sz(v[u]);i++){
            int to=v[u][i];
            dfs(to,u); 
        }
        out[u]=dfn_clock;
    }
    void init(){
        DSU::init();
        for(int i=1;i<=m;i++){
            if(Q[i].opt==1){
                if(DSU::same(Q[i].x,Q[i].y)) continue;
                v[Q[i].x].push_back(Q[i].y);
                DSU::unite(Q[i].x,Q[i].y);
            }
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]) dfs(i,-1);
        }
    }
    void main(){
        init();
        DSU::init();
        for(int i=1;i<=n;i++) id[i]=i;
        for(int i=1;i<=m;i++){
            if(Q[i].opt==1){
                if(DSU::same(Q[i].x,Q[i].y)) swap(id[Q[i].x],id[Q[i].y]);
                else DSU::unite(Q[i].x,Q[i].y);
            }
            else if(Q[i].opt==3){
                int x=id[Q[i].x];
                if(x!=DSU::getfather(x)) continue;
                T.update(dfn[x],Q[i].y);
                T.update(out[x]+1,-Q[i].y);
            }
            else if(Q[i].opt==4){
                int x=id[Q[i].x];
                ll val=T.query(dfn[x]);
                c[i]=Q[i].y-val;
            }
            else{
                ll val=T.query(dfn[Q[i].x]);
                printf("%lld\n",c[i]+val);
            }
        }
    }
}

bool check2(){
    for(int i=1;i<=m;i++) if(Q[i].opt==2) return 1;
    return 0;
}

int main()
{
    n=read(); m=read();
    if(n<=2000&&m<=2000){
        solver1::main();
        return 0;
    }
    for(int i=1;i<=m;i++){
        Q[i].opt=read();
        if(Q[i].opt!=5) Q[i].x=read(),Q[i].y=read();
        else Q[i].x=read();
    }
    if(!check2()){
        solver2::main();
        return 0;
    }
    return 0;
}