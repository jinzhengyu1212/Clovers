/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const ll INF=(ll)5e18;
const ll MOD=1e18;
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=505;
char s[N];
int a[N],n,dp[N][N];

int solve(int m){
    memset(dp,0,sizeof(dp));
    dp[0][0]=1; 
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(i,m);j++){
            if(j&&a[i]==a[j]){
                dp[i][j]=(dp[i][j]+dp[i-1][j-1])%MOD;
            }
            dp[i][j]=(dp[i][j]+dp[i-1][j])%MOD;
        }
    }
    return dp[n][m];
}

signed main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++) a[i]=(s[i]=='B');
    int ans=1;
    for(int i=1;i<=n;i++) ans=(ans+solve(i))%MOD;
    printf("%018lld\n",ans);
    return 0;
}