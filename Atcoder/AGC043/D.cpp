#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int MOD,n;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}

int dp[N*3][N*6];
int main(){
    scanf("%d%d",&n,&MOD); n*=3;
    dp[0][n]=1;
    //以第三个转移为例，确定块长为3，那么最大的那个一定在块顶，讨论另外两个位置的情况
    //只考虑那两个位置的种数，即(i-1)*(i-2)，剩下的一定是一个从小到大的排列，那么直接乘上dp状态即可
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n+n;j++){
            if(j) dp[i][j]=add(dp[i][j],dp[i-1][j-1]);
            if(i>=2) dp[i][j]=add(dp[i][j],mul(dp[i-2][j+1],i-1));
            if(i>=3) dp[i][j]=add(dp[i][j],mul(dp[i-3][j],mul(i-2,i-1)));
        }
    }
    int ans=0;
    for(int j=n;j<=n+n;j++){
        ans=add(ans,dp[n][j]);
    }
    cout<<ans<<endl;
    return 0;
}