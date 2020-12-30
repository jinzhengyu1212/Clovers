/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
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
int n,k,t,fac[N],ifac[N],nxt[N],pre[N];
pii a[N]; int val[N];
int C(int n,int m){
    if(n<m||m<0) return 0;
    return mul(fac[n],mul(ifac[m],ifac[n-m]));
}

int s[N];
void init(){
    n=read(); k=read(); t=read();
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=i;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) val[i]=a[i].first;
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=1;i<=n;i++){
        nxt[i]=upper_bound(val+1,val+n+1,val[i]*t)-val-1;
        pre[i]=upper_bound(val+1,val+n+1,val[i]/t)-val;
    }
    for(int i=1;i<=n;i++) s[i]=i;
    for(int i=n;i>=1;i--) if(val[i]==val[i+1]) s[i]=s[i+1];
}

int ans[N];
void solve(){
    for(int i=1;i<=n;i++){
        int nxtnum=nxt[i]-s[i]+1;
        int prenum=s[i]-pre[i]+1;
        Add(ans[a[i].second],C(n-nxtnum,k-nxtnum));
        Add(ans[a[i].second],C(n-prenum,k));
    }
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}

signed main()
{
    init(); solve();
    return 0;
}