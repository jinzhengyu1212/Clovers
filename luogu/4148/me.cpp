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
const int N=200005;
const double Rate=0.713;
int n=0,ans=0,tot=0,root=0;
int sx,sy,ex,ey;
int decode(int x){return x^ans;}
struct node{
    int x,y,val;
}a[N];
int id[N];
bool cmpx(int x,int y){return a[x].x<a[y].x;}
bool cmpy(int x,int y){return a[x].y<a[y].y;}
double sqr(double x){return x*x;} 

struct KD_Tree{
    int ls[N],rs[N],sz[N],L[N],R[N],U[N],D[N],typ[N];
    ll sum[N];
    void pushup(int x){
        sum[x]=a[x].val;
        L[x]=R[x]=a[x].x; U[x]=D[x]=a[x].y;
        sz[0]=0; sz[x]=1+sz[ls[x]]+sz[rs[x]];
        if(ls[x]){
            sum[x]+=sum[ls[x]];
            checkmax(R[x],R[ls[x]]); checkmin(L[x],L[ls[x]]);
            checkmax(U[x],U[ls[x]]); checkmin(D[x],D[ls[x]]);
        }
        if(rs[x]){
            sum[x]+=sum[rs[x]];
            checkmax(R[x],R[rs[x]]); checkmin(L[x],L[rs[x]]);
            checkmax(U[x],U[rs[x]]); checkmin(D[x],D[rs[x]]);
        }
    }
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
    bool bad(int x){return Rate*sz[x]<(double)max(sz[ls[x]],sz[rs[x]]);}
    void dfs(int u){
        if(ls[u]) dfs(ls[u]);
        id[++tot]=u;
        if(rs[u]) dfs(rs[u]);
    }
    void rebuild(int &u){
        tot=0; dfs(u);
        u=build(1,tot);
    }
    void insert(int &x,int now){
        if(!x){
            x=now;
            pushup(x); return;           
        }
        if(typ[x]==0){
            if(a[now].x<a[x].x) insert(ls[x],now);
            else insert(rs[x],now);
        }
        else{
            if(a[now].y<a[x].y) insert(ls[x],now);
            else insert(rs[x],now);
        }
        pushup(x); 
        if(bad(x)) rebuild(x);
    }
    int query(int x){
        if(!x) return 0;
        if(sx<=L[x]&&R[x]<=ex&&sy<=D[x]&&U[x]<=ey) return sum[x];
        int ret=(sx<=a[x].x&&a[x].x<=ex&&sy<=a[x].y&&a[x].y<=ey)*a[x].val;
        if(typ[x]==0){
            if(a[x].x>=sx) ret+=query(ls[x]);
            if(a[x].x<=ex) ret+=query(rs[x]);
        }
        else{
            if(a[x].y>=sy) ret+=query(ls[x]);
            if(a[x].y<=ey) ret+=query(rs[x]);
        }
        return ret;
    }
}tree;

int main()
{
    read(); int opt=0;
    while(scanf("%d",&opt)!=EOF){
        if(opt==3) return 0;
        if(opt==1){
            n++;
            a[n].x=read()^ans; a[n].y=read()^ans; a[n].val=read()^ans;
            tree.insert(root,n);
        }
        else{
            sx=read()^ans; sy=read()^ans;
            ex=read()^ans; ey=read()^ans;
            printf("%d\n",ans=tree.query(root));
        }
    }
    return 0;
}