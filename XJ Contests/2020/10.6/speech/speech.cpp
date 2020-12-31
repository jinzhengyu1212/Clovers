#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define mk make_pair
const int N=705;

int n,d;
int A[N*N]; int cnt=0;
int mp[N][N],vis[N][N];
pii dfs(int u,int f,int step){
    if(vis[u][f]) return mk(step-vis[u][f],vis[u][f]);
    A[++cnt]=u;
    if(d==step) return mk(0,0);
    vis[u][f]=step;
    dfs(mp[u][f],u,step+1);
}

signed main(){
    scanf("%lld%lld",&n,&d);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) scanf("%lld",&mp[i][j]);
    }
    A[++cnt]=1;
    pii flag=dfs(2,1,2);
    if(!flag.first){
        printf("%lld\n",A[cnt]);
    }
    else{
        d-=cnt;
        int tmp=d%flag.first+flag.second-1;
        if(tmp==flag.second-1) tmp=cnt;
        printf("%lld\n",A[tmp]);
    }
    return 0;
}