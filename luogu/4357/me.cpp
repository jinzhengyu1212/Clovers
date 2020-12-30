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
#define int long long
const int N=100005;
struct node{
    int x,y;
}a[N];
int n,k;
bool cmpx(node A,node B){return A.x<B.x;}
bool cmpy(node A,node B){return A.y<B.y;}

priority_queue<int,vector<int>,greater<int> > Q;
struct KD_Tree{
    int ls[N],rs[N],L[N],R[N],D[N],U[N];
    int sqr(int x){return x*x;}
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
    int build(int l,int r){
        if(l>r) return 0;
        int mid=(l+r)>>1;
        double av1=0,av2=0;
        for(int i=l;i<=r;i++) av1+=a[i].x,av2+=a[i].y;
        av1/=(r-l+1); av2/=(r-l+1);
        double sum1=0,sum2=0;
        for(int i=l;i<=r;i++) 
            sum1+=sqr(av1-a[i].x),sum2+=sqr(av2-a[i].y);
        if(sum1<sum2) nth_element(a+l,a+mid,a+r+1,cmpx);
        else nth_element(a+l,a+mid,a+r+1,cmpy);
        ls[mid]=build(l,mid-1); rs[mid]=build(mid+1,r);
        pushup(mid); return mid;
    }
    int esti(int id,int to){
        if(to==0) return 0;
        return max(sqr(a[id].x-L[to]),sqr(a[id].x-R[to]))+
               max(sqr(a[id].y-D[to]),sqr(a[id].y-U[to]));
    }
    int dist(int X,int Y){
        return sqr(a[X].x-a[Y].x)+sqr(a[X].y-a[Y].y);
    }
    void query(int l,int r,int from){
        if(l>r) return;
        int mid=(l+r)>>1,dis=dist(from,mid);
        if(dis>Q.top()) Q.pop(),Q.push(dis);
        int disx=esti(from,ls[mid]),disy=esti(from,rs[mid]);
        if(disx>Q.top()&&disy>Q.top()){
            if(disx>disy){
                query(l,mid-1,from);
                if(disy>Q.top()) query(mid+1,r,from);
            }
            else{
                query(mid+1,r,from);
                if(disx>Q.top()) query(l,mid-1,from);
            }
        }       
        else{
            if(disx>Q.top()) query(l,mid-1,from);
            if(disy>Q.top()) query(mid+1,r,from);
        }
    }
}tree;

signed main()
{
    n=read(); k=read()*2;
    for(int i=1;i<=k;i++) Q.push(0);
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    tree.build(1,n);
    for(int i=1;i<=n;i++) tree.query(1,n,i);
    cout<<Q.top()<<endl;
    return 0;
}