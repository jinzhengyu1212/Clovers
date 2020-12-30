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
const int MOD=924844033;
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
const int N=2005;
int n,k,sum=0;
int dp[N+N][N],a[N+N],fac[N];

int main()
{
    n=read(); k=read(); fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    for(int rnd=1;rnd<=min(n,2*k);rnd++){
        for(int i=rnd;i<=n;i+=2*k){
            if(i>k){
                a[++sum]=1;
                if(i+k>n) a[sum]=0; 
            }
            if(i+k<=n){
                a[++sum]=1;
                if(i+2*k>n) a[sum]=0;
            }
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=sum;i++){
        dp[i][0]=dp[i-1][0];
        for(int j=1;j<=i;j++){
            dp[i][j]=add(dp[i-1][j],dp[i-a[i-1]-1][j-1]);
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        Add(ans,mul(mul(fac[n-i],dp[sum][i]),(i&1 ? MOD-1 : 1)));
    }
    cout<<ans<<endl;
    return 0;
}