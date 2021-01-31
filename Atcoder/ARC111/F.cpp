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
const int N=1005;
int n,m,q;
int dp[N],sum[N];
int ans=0,km,kn,One;

int main()
{
    n=read(); m=read(); q=read();
    km=1ll*m*(m-1)/2%MOD;
    kn=1ll*n*(n+1)/2%MOD;
    sum[0]=1; One=mul(m+m+1,kn);
    for(int i=1;i<q;i++) sum[i]=mul(sum[i-1],One);
    for(int rnd=1;rnd<=n;rnd++){
        int ti=mul(n-rnd+1,rnd),rest=sub(kn,ti);
        for(int i=1;i<q;i++){
            dp[i]=mul(ti,add(sum[i-1],mul(dp[i-1],m)));
            Add(dp[i],mul(dp[i-1],add(mul(rest,2*m),kn)));     
        }
        for(int i=2;i<=q;i++){//query at i 
            int tmp=mul(km,dp[i-1]);
            Mul(tmp,ti);
            Add(ans,mul(tmp,sum[q-i]));
        }
    }
    cout<<ans<<endl;
    return 0;
}