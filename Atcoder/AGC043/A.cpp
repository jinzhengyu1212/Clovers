#include<bits/stdc++.h>
using namespace std;
const int N=105;
void checkmin(int &x,int y){if(x>y) x=y;}
int n,m;
char s[N][N];
int dp[N][N];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    memset(dp,0x3f,sizeof(dp));
    if(s[1][1]=='.') dp[1][1]=0;
    else dp[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i!=n){
                checkmin(dp[i+1][j],dp[i][j]+(s[i+1][j]!=s[i][j]));
            }
            if(j!=m){
                checkmin(dp[i][j+1],dp[i][j]+(s[i][j+1]!=s[i][j]));
            }
        }
    }
    printf("%d\n",(dp[n][m]+(s[n][m]=='#'))/2);
    return 0;
}