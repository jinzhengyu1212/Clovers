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

struct Tree{
    int dfn[N],dfn_clock=0,vis[N],out[N],fa[N];
    vector<int> v[N];
    void dfs(int u){
        dfn[u]=++dfn_clock; vis[u]=1;
        out[u]=dfn[u];
        for(auto &to : v[u]) dfs(to);
    }
}t1,t2;

struct OIerwanhongAKIOI{//A
    vector<int> tim[N<<2];
    vector<ll> val[N<<2];
    void update(int x,int l,int r,int L,int R,int AD,int ti){
        if(L<=l&&r<=R){
            tim[x].push_back(ti);
            val[x].push_back((val[x].empty() ? 0 : val[x].back())+AD);
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R,AD,ti);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,AD,ti);
    }
    ll query(int x,int l,int r,int pos,int ti){
        int tmp=lower_bound(tim[x].begin(),tim[x].end(),ti)-tim[x].begin()-1;
        ll tt=(tmp==-1||tim[x].empty() ? 0 : val[x][tmp]);
        ll ttt=(tim[x].empty() ? 0 : val[x].back());
        if(l==r){return ttt-tt;}
        int mid=(l+r)>>1;
        if(mid>=pos) return ttt-tt+query(x<<1,l,mid,pos,ti);
        else return ttt-tt+query(x<<1|1,mid+1,r,pos,ti);
    }
}tree1;
struct SevenDawnsAKIOI{//B
    int tim[N<<2],val[N<<2];
    pii merge(pii x,pii y){//time val
        return x.first<y.first ? y : x;
    }
    void update(int x,int l,int r,int L,int R,int ti,int Val){
        if(L<=l&&r<=R){
            tim[x]=ti;
            val[x]=Val;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R,ti,Val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,ti,Val);
    }
    pii query(int x,int l,int r,int pos){
        if(l==r) return mk(tim[x],val[x]);
        int mid=(l+r)>>1;
        if(mid>=pos) return merge(mk(tim[x],val[x]),query(x<<1,l,mid,pos));
        else return merge(mk(tim[x],val[x]),query(x<<1|1,mid+1,r,pos));
    }
}tree2;

void solve(){
    for(int i=1;i<=m;i++){
        if(Q[i].opt==1)
            checkmax(t1.out[Q[i].x],t1.out[Q[i].y]);
        else if(Q[i].opt==2)
            checkmax(t2.out[Q[i].x],t2.out[Q[i].y]);
        else if(Q[i].opt==3)
            tree1.update(1,1,n,t1.dfn[Q[i].x],t1.out[Q[i].x],Q[i].y,i);
        else if(Q[i].opt==4)
            tree2.update(1,1,n,t2.dfn[Q[i].x],t2.out[Q[i].x],i,Q[i].y);
        else{
            pii tmp=tree2.query(1,1,n,t2.dfn[Q[i].x]);
            ll ret=tree1.query(1,1,n,t1.dfn[Q[i].x],tmp.first);
            printf("%lld\n",ret+tmp.second);
        }
    }
}

int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        Q[i].opt=read();
        if(Q[i].opt!=5) Q[i].x=read(),Q[i].y=read();
        else Q[i].x=read();
    }
    for(int i=1;i<=m;i++){
        if(Q[i].opt==1) t1.v[Q[i].x].push_back(Q[i].y),t1.fa[Q[i].y]=Q[i].x;
        else if(Q[i].opt==2) t2.v[Q[i].x].push_back(Q[i].y),t2.fa[Q[i].y]=Q[i].x;
    }
    for(int i=1;i<=n;i++){
        if(t1.fa[i]==0) t1.dfs(i);
        if(t2.fa[i]==0) t2.dfs(i);
    }
    solve();
    return 0;
}