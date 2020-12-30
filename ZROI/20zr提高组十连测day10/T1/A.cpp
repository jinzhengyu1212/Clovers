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
const int N=100005;
int n,m;
ll a[N],b[N],c[N],d[N],ans=0;
ll x[N],y[N],sum[N];

int main()
{
    n=read(); m=read();
    for(int i=1;i<n;i++) a[i]=read(),ans+=a[i];
    for(int i=1;i<=m;i++) b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read(),ans+=c[i]*(m-1);
    for(int i=1;i<m;i++) d[i]=read(),ans+=d[i]*n;
    ans+=b[1]*(n-1);
    for(int i=1;i<m;i++) y[i]=d[i]-b[i+1];
    for(int i=1;i<n;i++) x[i]=c[i+1]-a[i];
    sort(y+1,y+m);
    for(int i=1;i<m;i++) sum[i]=sum[i-1]+y[i];
    for(int i=1;i<n;i++){
        int pos=upper_bound(y+1,y+m,-x[i])-y;
        ans-=(sum[m-1]-sum[pos-1]+x[i]*(m-pos));
    }
    cout<<ans<<endl;
    return 0;
}