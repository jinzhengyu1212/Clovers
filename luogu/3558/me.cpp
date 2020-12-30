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
int min3(int x,int y,int z){return min(min(x,y),z);}
const int N=1000005;
int ans=0,dp[N][3],n,a[N];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    memset(dp,0x3f,sizeof(dp));
    dp[1][a[1]+1]=0;
    for(int i=2;i<=n;i++){
        if(a[i]==-1){
            dp[i][0]=dp[i-1][0];
            dp[i][2]=dp[i-1][2]+2;
        }
        if(a[i]==0){
            dp[i][1]=min(dp[i-1][0],dp[i-1][1]);
            dp[i][0]=dp[i-1][0]+1;
            dp[i][2]=dp[i-1][2]+1;
        }
        if(a[i]==1){
            dp[i][2]=min3(dp[i-1][0],dp[i-1][1],dp[i-1][2]);
            dp[i][0]=dp[i-1][0]+2;
            dp[i][1]=dp[i-1][0]+1;
        }
    }
    int ans=min3(dp[n][0],dp[n][1],dp[n][2]);
    if(ans<=n*5) printf("%d\n",ans);
    else puts("BRAK");
    return 0;
}