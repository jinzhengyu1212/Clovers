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
const int N=150005;
int n,m,vis[N],M,sg[N],tot=0; vector<int> v[N];

bitset<18> rev[N<<5]; int dep[N<<5];
//深度可以整体打标记然后记录每个节点上一次修改看奇偶性，也可以每个节点压进这个节点为根的所有深度的tag，然后bitset优化
struct Segment_Tree{
    int ls[N<<5],rs[N<<5],sum[N<<5];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void pushdown(int x){
        if(!x) return;
        if(rev[x][dep[x]]){
            swap(ls[x],rs[x]);
        }
        if(ls[x]) rev[ls[x]]=rev[ls[x]]^rev[x];
        if(rs[x]) rev[rs[x]]=rev[rs[x]]^rev[x];
        rev[x].reset();
    }
    int Newnode(int x){
        tot++; dep[tot]=dep[x]-1;
        return tot;
    }
    void insert(int x,int l,int r,int pos){
        if(l==r){sum[x]=1; return;}
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos){
            if(!ls[x]) ls[x]=Newnode(x);
            insert(ls[x],l,mid,pos);
        }
        else{
            if(!rs[x]) rs[x]=Newnode(x);
            insert(rs[x],mid+1,r,pos);
        }
        pushup(x);
    }
    int merge(int l,int r,int x,int y,int from){
        if(!x||!y) {pushdown(x+y); return x+y;}
        if(l==r){sum[x]|=sum[y]; return x;}
        int mid=(l+r)>>1;
        pushdown(x); pushdown(y);
        ls[x]=merge(l,mid,ls[x],ls[y],from);
        rs[x]=merge(mid+1,r,rs[x],rs[y],from);
        pushup(x);
        return x;
    }
    int find(int x,int l,int r,int pos){
        if(l==r) return sum[x];
        int mid=(l+r)>>1; pushdown(x);
        if(mid>=pos){
            if(!ls[x]) return 0;
            return find(ls[x],l,mid,pos);
        }
        else{
            if(!rs[x]) return 0;
            return find(rs[x],mid+1,r,pos);
        }
    }
    int query(int x,int l,int r){
        if(l==r) return l;
        int mid=(l+r)>>1; pushdown(x);
        if(sum[ls[x]]==mid-l+1) return query(rs[x],mid+1,r);
        else return query(ls[x],l,mid);
    }
    void update(int x,int val){
        for(int i=0;i<M;i++){
            if(val>>i&1) rev[x][i]=(rev[x].test(i) ? 0 : 1);
        }
    }
}tree;

void dfs1(int u,int f){ 
    vis[u]=1;
    vector<int> t; t.clear();
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs1(to,u); t.push_back(to);
    }
    v[u]=t;
}

void init(){
    for(int i=1;i<=tot;i++) 
        tree.ls[i]=0,tree.rs[i]=0,tree.sum[i]=0;
    n=read(); m=read(); tot=n;
    M=1; while((1<<M)<=n) M++;
    for(int i=1;i<=n;i++) dep[i]=M-1;
    for(int i=1;i<=n;i++) vis[i]=0,v[i].clear();
    for(int i=1;i<=n;i++) rev[i].reset();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs1(i,-1);
}

void dfs2(int u){
    int sum=0; vis[u]=1;
    for(auto &to : v[u]){
        dfs2(to);
        tree.update(to,sum); tree.update(u,sg[to]);
        tree.merge(0,(1<<M)-1,u,to,u); sum^=sg[to];
    }
    if(v[u].empty()) tree.insert(u,0,(1<<M)-1,0);
    sg[u]=tree.query(u,0,(1<<M)-1);
    tree.insert(u,0,(1<<M)-1,sg[u]);
}

void solve(){
    int ans=0;
    for(int i=1;i<=n;i++) vis[i]=0;
    for(int i=1;i<=n;i++) if(!vis[i]){
        dfs2(i),ans^=sg[i];
    }
    puts(ans ? "Alice" : "Bob");
}

int main()
{
    int T=read();
    while(T--){init(); solve();}
    return 0;
}