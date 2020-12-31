#include<bits/stdc++.h>
using namespace std;
const int N=82;

int n,a[5];
namespace solver1{
    void main(){
        if(n==1){
            if(a[1]==1) puts("Lose");
            else printf("1\n");
        }
        else{
            if(a[2]==a[1]-1) puts("Lose");
            else{
                int x=a[1],y=a[2];
                if(x==y) y--;
                else x=y+1;
                printf("%d %d\n",x,y);
            }
        }
    }
}

struct PRIOR{
    int x,y,z;
    PRIOR(){}
    PRIOR(int x,int y,int z):x(x),y(y),z(z){}
}pre[N][N][N];
namespace solver2{
    int dp[N][N][N];
    
    int dfs(int a1,int a2,int a3){
        if(a1==1&&a2==0&&a3==0) return dp[1][0][0]=0;
        if(dp[a1][a2][a3]!=-1) return dp[a1][a2][a3];
        int flag=0;
        for(int i=a1-1;i>=1;i--){
            int x=i,y=min(i,a2),z=min(i,a3);
            if(!dfs(x,y,z)) pre[a1][a2][a3]=PRIOR(x,y,z),flag=1;
        }
        for(int i=a2-1;i>=0;i--){
            int x=a1,y=i,z=min(i,a3);
            if(!dfs(x,y,z)) pre[a1][a2][a3]=PRIOR(x,y,z),flag=1;
        }
        for(int i=a3-1;i>=0;i--){
            int x=a1,y=a2,z=i;
            if(!dfs(x,y,z)) pre[a1][a2][a3]=PRIOR(x,y,z),flag=1;
        }
        return dp[a1][a2][a3]=flag;
    }
    void main(){
        memset(dp,-1,sizeof(dp));
        if(dfs(a[1],a[2],a[3])){
            PRIOR tmp=pre[a[1]][a[2]][a[3]];
            printf("%d %d %d\n",tmp.x,tmp.y,tmp.z);
        }
        else puts("Lose");
    }
}

namespace solver3{
    void main(){
        if(a[3]==1){
            if((a[1]==2&&a[2]==2)||(a[1]==3&&a[2]==1)) puts("Lose");
            else{
                if(a[1]==1) printf("1 0 0\n");
                if(a[2]>=2) printf("2 2 1\n");
                else printf("3 1 1\n");
            }
        }
        else if(a[3]==2){
            if(a[1]-a[2]==2) puts("Lose");
            else{
                if(a[1]>a[2]+2) printf("%d %d 2\n",a[2]+2,a[2]);
                else printf("%d %d 2\n",a[1],a[1]-2);
            }
        }
        else if(a[3]==3){
            if(a[2]==3) puts("6 3 3");
            else if(a[2]==4) puts("7 4 3");
            else puts("5 5 3");
        }
    }
}

void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    if(n<=2) solver1::main();
    else if(a[1]<=81) solver2::main();
    else if(a[3]<=3) solver3::main();
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        solve();
    }
}