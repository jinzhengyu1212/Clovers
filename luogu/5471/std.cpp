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
struct node{
    int x,y;
}a[N];
int id[N];
bool cmpx(int x,int y){return a[x].x<a[y].x;}
bool cmpy(int x,int y){return a[x].y<a[y].y;}
vector<pii> v[N<<1];
int vis[N<<1],dis[N<<1];
struct Node{
    int id,dis;  
    bool operator < (const Node &rhs) const{
        return dis>rhs.dis;
    }
};
priority_queue<Node> Q;
void dijkstra(){
    for(int i=1;i<=n+n;i++) dis[i]=inf,vis[i]=0;
    dis[n+1]=0; Q.push({n+1,0});
    while(!Q.empty()){
        int u=Q.top().id; Q.pop();
        if(vis[u]) continue; vis[u]=1;
        for(auto &To : v[u]){
            int to=To.first,w=To.second;
            if(vis[to]) continue;
            if(dis[to]>dis[u]+w){
                dis[to]=dis[u]+w;
                Q.push({to,dis[to]});           
            }
        }
    }
    for(int i=2;i<=n;i++) printf("%d\n",dis[i+n]);
}

int sx,sy,ex,ey;
struct KD_Tree{
    int ls[N],rs[N],L[N],R[N],D[N],U[N],typ[N];
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
    double sqr(double x){return x*x;}
    int build(int l,int r){
        if(l>r) return 0;
        int mid=(l+r)>>1;
        double av1=0,av2=0;
        for(int i=l;i<=r;i++) av1+=a[id[i]].x,av2+=a[id[i]].y;
        av1/=(r-l+1); av2/=(r-l+1);
        double sum1=0,sum2=0;
        for(int i=l;i<=r;i++) 
            sum1+=sqr(a[id[i]].x-av1),sum2+=sqr(a[id[i]].x-av2);
        if(sum1>sum2) nth_element(id+l,id+mid,id+r+1,cmpx),typ[mid]=0;
        else nth_element(id+l,id+mid,id+r+1,cmpy),typ[mid]=1;
        ls[id[mid]]=build(l,mid-1); rs[id[mid]]=build(mid+1,r);
        if(ls[id[mid]]) v[id[mid]].push_back(mk(ls[id[mid]],0));
        if(rs[id[mid]]) v[id[mid]].push_back(mk(rs[id[mid]],0));
        pushup(id[mid]); return id[mid];
    }   
    void query(int x,int from,int val){
        if(!x) return;
        if(sx<=L[x]&&sy<=D[x]&&ex>=R[x]&&ey>=U[x]){
            v[from+n].push_back(mk(x,val));
            return;
        }
        if(sx<=a[x].x&&sy<=a[x].y&&ex>=a[x].x&&ey>=a[x].y)
            v[from+n].push_back(mk(x+n,val));
        if(typ[x]==0){
            if(a[x].x>=sx) query(ls[x],from,val);
            if(a[x].x<=ex) query(rs[x],from,val); 
        }
        else{
            if(a[x].y>=sy) query(ls[x],from,val);
            if(a[x].y<=ey) query(rs[x],from,val);
        }
    }
}tree;

void init(){
    n=read(); m=read(); read(); read();
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    for(int i=1;i<=n;i++) id[i]=i;
    int root=tree.build(1,n);
    for(int i=1;i<=n;i++) v[i].push_back(mk(i+n,0));
    for(int i=1;i<=m;i++){
        int P=read(),T=read(),L=read(),R=read(),D=read(),U=read();
        sx=L,ex=R,sy=D,ey=U;
        tree.query(root,P,T);
    }
    for(int i=1;i<=n+n;i++){
        for(auto &to : v[i]){
            cout<<i<<" "<<to.first<<" "<<to.second<<endl;
        }
    }
}

int main()
{
    init();
    dijkstra();
    return 0;
}