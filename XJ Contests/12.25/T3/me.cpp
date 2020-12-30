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
const int MOD=1e9+7;
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
const int M=1000001;
const int N=200005;
int n,m,R[N],L[N],vis[N];
vector<int> v[N];
struct node{
    int l,r;
}a[M];
bool cmpl(node x,node y){return x.l<y.l;}
bool cmpr(node x,node y){return x.r<y.r;}
namespace BIT1{
    int mx[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i<=n;i+=lowbit(i)) checkmax(mx[i],val);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) checkmax(ret,mx[i]);
        return ret;
    }
}
namespace BIT2{
    int mi[N];
    void init(){for(int i=1;i<=n;i++) mi[i]=inf;}
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i;i-=lowbit(i)) checkmin(mi[i],val);
    }
    int query(int x){
        int ret=inf;
        for(int i=x;i<=n;i+=lowbit(i)) checkmin(ret,mi[i]);
        return ret;
    }
}
namespace BIT{
    int a[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){
        for(int i=x;i<=n;i+=lowbit(i)) Add(a[i],val);
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) Add(ret,a[i]);
        return ret;
    }
}
void init(){
    n=read(); m=read();
    for(int i=1;i<=m;i++) a[i].l=read(),a[i].r=read(),vis[a[i].r]=1;
    sort(a+1,a+m+1,cmpl);
    for(int i=n,j=m;i>=1;i--){
        R[i]=i-1;
        while(a[j].l==i&&j){
            checkmax(R[i],a[j].r);
            if(R[i]!=n) checkmax(R[i],BIT1::query(a[j].r+1));
            j--;
        }
        BIT1::update(i,R[i]);
    } R[1]=n;
    BIT2::init();
    sort(a+1,a+m+1,cmpr);
    for(int i=1,j=1;i<=n;i++){
        L[i]=i+1;
        while(a[j].r==i&&j<=m){
            checkmin(L[i],a[j].l);
            if(L[i]!=1) checkmin(L[i],BIT2::query(a[j].l-1));
            j++;
        }
        BIT2::update(i,L[i]);
    } L[n]=1;
    //for(int i=1;i<=n;i++) out(i),outln(L[i]);
}
int dp[N],ans=1,sum[N];
void solve(){
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1];
        v[R[i]+1].push_back(i);
        for(auto &to : v[i]){
            BIT::update(to,MOD-((to<=2 ? 0 : sum[to-2])+1));
        }
        BIT::update(i,(i<=2 ? 0 : sum[i-2])+1);
        if(!vis[i]) continue; 
        dp[i]=sub(BIT::query(i),BIT::query(L[i]-1));
        Add(ans,dp[i]); Add(sum[i],dp[i]);
    }
    if(!vis[n]) Add(ans,1);
    cout<<ans<<endl;
}

int main()
{
    init(); solve();
    return 0;
}