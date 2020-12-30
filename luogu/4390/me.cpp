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
#define y1 myyakak
#define y0 hcyakak
const int V=2000005;
const int N=200005;
int w;
struct BIT{
    ll a[V];
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i<=w;i+=lowbit(i)) a[i]+=val;
    }
    ll query(int x){
        ll ret=0; assert(x>=0);
        for(int i=x;i;i-=lowbit(i)) ret+=a[i];
        return ret;
    }
}tree;
struct ADD{
    int ti,x,y,val;
    bool operator < (const ADD &rhs) const{
        return x<rhs.x;
    }
}A[N],a[N];
struct QUERY{
    int ti,x0,y0,x1,y1;
}B[N];
struct Q1{
    int x,y0,y1,id,flag;
    bool operator < (const Q1 &rhs) const{
        return x<rhs.x;
    }
}b[N];
int cnta=0,cntb=0,ta[N],tb[N];
ll ans[N];

void update(int la,int ra,int lb,int rb){
    int na=0,nb=0;
    for(int i=la;i<=ra;i++) a[++na]=A[i];
    for(int i=lb;i<=rb;i++){
        b[++nb]={B[i].x0-1,B[i].y0,B[i].y1,i,-1};
        b[++nb]={B[i].x1,B[i].y0,B[i].y1,i,1};
    }
    sort(a+1,a+na+1); sort(b+1,b+nb+1);
    int i=1,j=1;
    while(i<=na&&j<=nb){
        while(a[i].x<=b[j].x&&i<=na){
            tree.update(a[i].y,a[i].val);
            ++i;
        }
        while(b[j].x<a[i].x&&j<=nb){
            ans[b[j].id]+=b[j].flag*(tree.query(b[j].y1)-tree.query(b[j].y0-1));
            j++;
        }
    }
    while(j<=nb){
        ans[b[j].id]+=b[j].flag*(tree.query(b[j].y1)-tree.query(b[j].y0-1));
        j++;
    }
    for(i=1;i<=na;i++) tree.update(a[i].y,-a[i].val);
}

void cdq(int l,int r){
    int la=lower_bound(ta+1,ta+cnta+1,l)-ta,lb=lower_bound(tb+1,tb+cntb+1,l)-tb;
    int ra=upper_bound(ta+1,ta+cnta+1,r)-ta-1,rb=upper_bound(tb+1,tb+cntb+1,r)-tb-1;
    if(ra<la||rb<lb) return;
    int mid=(l+r)>>1;
    int ma=upper_bound(ta+1,ta+cnta+1,mid)-ta-1,mb=upper_bound(tb+1,tb+cntb+1,mid)-tb;
    if(la<=ma&&mb<=rb) update(la,ma,mb,rb);
    cdq(l,mid); cdq(mid+1,r);
}

int main()
{
    read(); w=read();
    int opt,ttt=0;
    while((opt=read())!=3){
        ttt++;
        if(opt==1) A[++cnta]={ttt,read(),read(),read()},ta[cnta]=ttt;
        else B[++cntb]={ttt,read(),read(),read(),read()},tb[cntb]=ttt;
    }
    cdq(1,ttt);
    for(int i=1;i<=cntb;i++) printf("%lld\n",ans[i]);
    return 0;
}