#include<bits/stdc++.h>
using namespace std;
const int N=82;

int n,a[5];
namespace solver1{
    void main(){
        if(a[2]==0&&n==2) n--;
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
    bool operator < (const PRIOR &rhs)const{
        return z<rhs.z;
    }
}pre[N][N][N];
vector<PRIOR> A;
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
        if(!flag) A.push_back(PRIOR(a1,a2,a3));
        return dp[a1][a2][a3]=flag;
    }
    void main(){
        memset(dp,-1,sizeof(dp));
        dfs(80,80,80);
        sort(A.begin(),A.end());
        for(int i=0;i<(int)A.size();i++) cout<<A[i].x<<" "<<A[i].y<<" "<<A[i].z<<endl;
    }
}

void solve(){
    solver2::main();
}

int main(){
    int T=1; //scanf("%d",&T);
    while(T--){
        solve();
    }
}