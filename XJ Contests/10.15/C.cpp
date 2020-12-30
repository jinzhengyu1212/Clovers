#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
void checkmin(int &x,int y){if(x>y) x=y;}
int T,n;

namespace solver1{
    int dp[N][2][2];
    char s[N];
    void main(){
        if(n==1){
            puts("0");
            return;
        }
        scanf("%s",s+1);
        memset(dp,0x3f,sizeof(dp));
        if(s[1]!=s[2]) dp[2][0][0]=0;
        dp[2][1][0]=1; dp[2][0][1]=1;
        for(int i=3;i<=n;i++){
            int min1=dp[i-1][1][0];
            int min0=min(dp[i-1][0][1],dp[i-1][0][0]);
            if(s[i]==s[i-1]){
                if(s[i]!=s[i-2]){
                    checkmin(dp[i][0][1],min1);
                    checkmin(dp[i][1][0],min0+1);
                }
                else{
                    puts("-1");
                    return;
                }
            }
            else{
                if(s[i]!=s[i-2]){
                    checkmin(dp[i][0][0],min0);
                    checkmin(dp[i][1][0],min0+1);
                    checkmin(dp[i][0][1],min1);
                }
                else{
                    checkmin(dp[i][1][0],dp[i-1][0][0]+1);
                    checkmin(dp[i][0][0],dp[i-1][0][1]);
                }
            }
        }
        int ans=min(dp[n][0][0],dp[n][0][1]);
        checkmin(ans,dp[n][1][0]);
        if(ans>n) puts("-1"); 
        else printf("%d\n",ans);
    }
}

int main(){
    scanf("%d%d",&T,&n);
    if(T==1){
        solver1::main();
        return 0;
    }
    return 0;
}