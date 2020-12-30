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
const int N=70005;
const int M=150005;

int n,m;
struct Jump{
    int t,L,R,D,U;
};
vector<Jump> J[N]; 
struct node{
    int x,y;
}a[N];
int id[N];
bool cmpx(int x,int y){return a[x].x<a[y].x;}
bool cmpy(int x,int y){return a[x].y<a[y].y;}
int vis[N<<1],dis[N<<1];
struct Node{
    int id,dis;  
    bool operator < (const Node &rhs) const{
        return dis>rhs.dis;
    }
};
priority_queue<Node> Q;
int sx,sy,ex,ey;
int ls[N],rs[N],tag[N];
int cnt2=0;
struct KD_Tree{
    int L[N],R[N],D[N],U[N],typ[N];
    void pushup(int x){
        L[x]=R[x]=a[x].x; U[x]=D[x]=a[x].y;
        if(ls[x]){
            checkmax(R[x],R[ls[x]]); checkmin(L[x],L[ls[x]]);
            checkmax(U[x],U[ls[x]]); checkmin(D[x],D[ls[x]]);
        }
        if(rs[x]){
            checkmax(R[x],R[rs[x]]); checkmin(L[x],L[rs[x]]);
            checkmax(U[x],U[rs[x]]); checkmin(D[x],D[rs[x]]);
        }
    }
    void pushdown(int x){
        if(ls[x]){
            checkmin(tag[ls[x]],tag[x]);
            if(dis[ls[x]]>tag[x]&&!vis[ls[x]]){
                dis[ls[x]]=tag[x];
                Q.push({ls[x],dis[ls[x]]});
            }
        }
        if(rs[x]){
            checkmin(tag[rs[x]],tag[x]);
            if(dis[rs[x]]>tag[x]&&!vis[rs[x]]){
                dis[rs[x]]=tag[x];
                Q.push({rs[x],dis[rs[x]]});
            }
        }
    }
    double sqr(double x){return x*x;}
    int build(int l,int r){
        if(l>r) return 0;
        int mid=(l+r)>>1;
        double av1=0,av2=0;
        for(int i=l;i<=r;i++) av1+=a[id[i]].x,av2+=a[id[i]].y;
        av1/=(r-l+1); av2/=(r-l+1);
        double sum1=0,sum2=0;
        for(int i=l;i<=r;i++) 
            sum1+=sqr(a[id[i]].x-av1),sum2+=sqr(a[id[i]].y-av2);
        if(sum1>sum2) nth_element(id+l,id+mid,id+r+1,cmpx),typ[id[mid]]=0;
        else nth_element(id+l,id+mid,id+r+1,cmpy),typ[id[mid]]=1;
        ls[id[mid]]=build(l,mid-1); rs[id[mid]]=build(mid+1,r);
        pushup(id[mid]); return id[mid];
    }   
    void query(int x,int val){
        if(!x) return;
        if(dis[x]<val) return;
        if(sx<=L[x]&&sy<=D[x]&&ex>=R[x]&&ey>=U[x]){
            if(dis[x]>val&&!vis[x]){
                dis[x]=val;
                Q.push({x,dis[x]});
            }
            checkmin(tag[x],val);
            return;
        }
        pushdown(x);
        if(sx<=a[x].x&&sy<=a[x].y&&ex>=a[x].x&&ey>=a[x].y){
            if(dis[x+n]>val&&!vis[x+n]){
                dis[x+n]=val;
                Q.push({x+n,dis[x+n]});
            }
        }
        if(typ[x]==0){
            if(a[x].x>=sx) query(ls[x],val);
            if(a[x].x<=ex) query(rs[x],val); 
        }
        else{
            if(a[x].y>=sy) query(ls[x],val);
            if(a[x].y<=ey) query(rs[x],val);
        }
    }
}tree;

int root;
void dijkstra(){
    for(int i=1;i<=n+n;i++) dis[i]=inf,vis[i]=0;
    for(int i=1;i<=n;i++) tag[i]=inf;
    dis[n+1]=0; Q.push({n+1,0});
    while(!Q.empty()){
        int u=Q.top().id; Q.pop();
        if(vis[u]) continue; vis[u]=1;
        if(u>n) for(auto &E : J[u-n]){
            sx=E.L,ex=E.R,sy=E.D,ey=E.U;
            tree.query(root,E.t+dis[u]);
        }
        if(u<=n){
            tree.pushdown(u);
            if(dis[u+n]>dis[u]&&!vis[u+n]){
                dis[u+n]=dis[u];
                Q.push({u+n,dis[u+n]});
            }
        }
    }
    for(int i=2;i<=n;i++) printf("%d\n",dis[i+n]);
}


void init(){
    n=read(); m=read(); read(); read();
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    for(int i=1;i<=n;i++) id[i]=i;
    root=tree.build(1,n);
    for(int i=1;i<=m;i++){
        int P=read(),T=read(),L=read(),R=read(),D=read(),U=read();
        J[P].push_back({T,L,R,D,U});
    }
}

int main()
{
    init();
    dijkstra();
    return 0;
}