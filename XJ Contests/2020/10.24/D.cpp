#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,MOD;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int sqr(int x){return mul(x,x);}

namespace solver1{
    int ans[105],dp[105][105][105];
    void main(){
        for(int ttt=1;ttt<=n;ttt++){
            memset(dp,0,sizeof(dp));
            dp[1][1][(ttt==1)]=1;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=i;j++){
                    for(int k=0;k<=i;k++){
                        if(j+1==ttt){
                            dp[i+1][j+1][1]=add(dp[i+1][j+1][1],dp[i][j][k]);
                        }
                        else dp[i+1][j+1][k]=add(dp[i+1][j+1][k],dp[i][j][k]);
                        if(j>=ttt) dp[i+1][j][k+1]=add(dp[i+1][j][k+1],dp[i][j][k]);
                        dp[i+1][j][k]=add(dp[i+1][j][k],mul(dp[i][j][k],j-(j>=ttt)));
                    }
                }
            }
            for(int j=ttt;j<=n;j++){
                for(int k=1;k<=n;k++){
                    ans[ttt]=add(ans[ttt],mul(dp[n][j][k],sqr(k)));
                }
            }
        }
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        puts("");
    }
}

int pre[N][N],suff[N][N],ans[N];
void solve(){
    pre[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++) 
            pre[i][j]=add(pre[i-1][j-1],mul(pre[i-1][j],j));
    }
    for(int i=1;i<=n;i++) suff[1][i]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n;j++){
            suff[i][j]=add(suff[i-1][j+1],mul(suff[i-1][j],j));
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int now=suff[n-j+1][i];
            if(j<n) now=add(now,mul(3*(n-j),suff[n-j][i]));
            if(j<n-1) now=add(now,mul(mul(n-j,n-j-1),suff[n-j-1][i]));
            ans[i]=add(ans[i],mul(now,pre[j-1][i-1]));
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
}

int main(){
    scanf("%d%d",&n,&MOD);
    //if(n<=100) solver1::main();
    solve();
    return 0;
}