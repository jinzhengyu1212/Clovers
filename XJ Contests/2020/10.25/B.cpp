#include<bits/stdc++.h>
using namespace std;
const int N=55;
const int inf=(int)1e9;
void checkmin(int &x,int y){if(x>y) x=y;}
int n,a[N+10],b[N+10],g[N+10][N+10][N+10];
int dp[N+10][N+10],spe[N+10][N+10];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    for(int from=0;from<=N;from++){
        memset(g[from],0x3f,sizeof(g[from]));
        g[from][0][from]=0;
        for(int i=from;i<=N;i++){
            for(int j=0;j<=N-i;j++){
                for(int k=1;k<=i;k++){
                    checkmin(g[from][i][j],g[from][i-k][k]+(j-k)*(j-k));
                }
            }
        }
    }
    memset(spe,0x3f,sizeof(spe));
    for(int i=1;i<=N;i++) spe[0][i]=0;
    for(int i=1;i<=N;i++){
        for(int j=0;j<=N-i;j++){
            for(int k=1;k<=i;k++){
                checkmin(spe[i][j],spe[i-k][k]+(j-k)*(j-k));
            }
        }
    }

    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=b[1];i++) dp[1][i]=spe[b[1]-i][i];
    for(int i=2;i<=n;i++){
        for(int j=1;j<=b[i];j++){
            for(int pre=1;pre<=b[i-1];pre++){
                for(int up=1;up<=b[i];up++){
                    int delta=up+a[i]-pre-a[i-1];
                    checkmin(dp[i][j],dp[i-1][pre]+g[up][b[i]+up-j][j]+delta*delta);
                }            
            }
            cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
        }
    }
    int ans=inf;
    for(int i=1;i<=b[n];i++){
        checkmin(ans,dp[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}