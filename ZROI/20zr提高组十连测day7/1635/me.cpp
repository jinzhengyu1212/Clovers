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
const int N=2005;
int n,a[N],t[N],dp[N][N],fac[N],ifac[N];
int C(int n,int m){
    return mul(fac[n],mul(ifac[m],ifac[n-m]));
}

int main()
{
    n=read();
    fac[0]=1; for(int i=1;i<=2000;i++) fac[i]=mul(fac[i-1],i);
    ifac[2000]=qpow(fac[2000],MOD-2);
    for(int i=1999;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    for(int i=1;i<=n;i++) a[i]=read(),t[a[i]]++;
    dp[2001][0]=1; int now=0;
    for(int i=2000;i>=1;i--){
        now+=t[i];
        for(int j=0;j<=now;j++){
            dp[i][j]=dp[i+1][j-t[i]];
            int faci=1;
            for(int cnt=1;cnt*i+j<=now;cnt++){
                Mul(faci,ifac[i]);
                int tmp1=mul(fac[i*cnt],mul(faci,ifac[cnt]));
                int tmp2=C(j+cnt*i,i*cnt);
                Add(dp[i][j],mul(dp[i+1][j+cnt*i-t[i]],mul(tmp1,tmp2)));
            }
        }
    }
    cout<<dp[1][0]<<endl;
    return 0;
}