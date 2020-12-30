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
const int N=300005;
#define int long long
int n,tot=0,m,val[N]; ll ans;
struct Line{
    int sx,ex,y,flag;
    bool operator < (const Line &rhs) const{
        return y<rhs.y;
    }
}a[N];

struct Segment_Tree{
    int cover[N<<2],len[N<<2];
    void pushup(int x,int L,int R){
        if(cover[x]) len[x]=val[R+1]-val[L];
        else len[x]=len[x<<1]+len[x<<1|1];
    }
    void update(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            cover[x]+=val;
            pushup(x,l,r);
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=L) update(x<<1,l,mid,L,R,val);
        if(mid<R) update(x<<1|1,mid+1,r,L,R,val);
        pushup(x,l,r);
    }
}tree;

void init(){
    n=read();
    for(int i=1;i<=n;i++){
        int sx=read(),sy=read(),ex=read(),ey=read();
        a[++tot]={sx,ex,sy,1}; val[tot]=sx;
        a[++tot]={sx,ex,ey,-1}; val[tot]=ex;
    }
    sort(val+1,val+tot+1);
    m=unique(val+1,val+tot+1)-val-1;
    for(int i=1;i<=tot;i++){
        a[i].sx=lower_bound(val+1,val+m+1,a[i].sx)-val;
        a[i].ex=lower_bound(val+1,val+m+1,a[i].ex)-val;
    }
    sort(a+1,a+tot+1);
}

void solve(){
    ans=0;
    for(int i=1;i<=tot;i++){
        ans+=tree.len[1]*(a[i].y-a[i-1].y);
        tree.update(1,1,m,a[i].sx,a[i].ex-1,a[i].flag);
    }
    cout<<ans<<endl;
}

signed main()
{
    init(); solve();
    return 0;
}