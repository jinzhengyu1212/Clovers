#include<bits/stdc++.h>
using namespace std;
const int M=(1<<22);
const int N=91;
int n,m,d,vis[M];
vector<int> v[N];
bitset<M> dp[N],pre[N],tmp1,tmp2;
struct Edge{
    int from,to,cost;
}E[N*N];
int main(){
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&E[i].from,&E[i].to,&E[i].cost);
    }
    pre[1].set(0);
    for(int rnd=1;rnd<=d;rnd++){
        for(int i=1;i<=n;i++){
            dp[i].reset();
        }
        //for(int i=1;i<=n;i++) print(pre[i]); cout<<endl;
        for(int i=1;i<=m;i++){
            int x=E[i].from,y=E[i].to,c=E[i].cost;
            tmp1=pre[x]; tmp2=pre[y];
            if(c) tmp1<<=(1<<(rnd-1)),tmp2<<=(1<<(rnd-1));
            dp[x]|=tmp2; dp[y]|=tmp1;
        }
        for(int i=1;i<=n;i++) pre[i]=dp[i];
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=(1<<d)-1;j++){
            if(dp[i].test(j)) 
                if(!vis[j]) vis[j]=1,ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}