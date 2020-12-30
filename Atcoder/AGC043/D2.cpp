#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x,f=1; char c=getchar();
    while(c>'9'||c<'0'){c=getchar(); if(c=='-') f=-1;}
    x=c-'0';
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48);
    return x*f;
}
const int N=2005;
const int M=6005;
const int B=6000;
int n,dp[M][M<<1];

int main()
{
    scanf("%d%d",&n,&MOD); n*=3;
    dp[0][B]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=B*2;j++){
            if(j) dp[i][j]=add(dp[i-1][j-1],dp[i][j]);
            if(i>1) dp[i][j]=add(dp[i][j],mul(dp[i-2][j+1],i-1));
            if(i>2) dp[i][j]=add(dp[i][j],mul(dp[i-3][j],mul(i-1,i-2)));
        }
    }
    int ans=0;
    for(int i=B;i<=B*2;i++) ans=add(ans,dp[n][i]);
    cout<<ans<<endl;
    return 0;
}