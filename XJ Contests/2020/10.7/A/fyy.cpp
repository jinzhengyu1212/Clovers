#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int maxn=95;
const int maxe=maxn*maxn;
struct Edge{
    int from,to,cost,nxt;
    Edge(){}
    Edge(int from,int to,int cost,int nxt):from(from),to(to),cost(cost),nxt(nxt){}
}edges[maxe<<1];
int n,m,d,E_cnt,lst[maxn],tot;
bitset<(1<<11)> dp[2][maxn],cur[maxn];
bitset<(1<<21)> ans;
inline int read(){
    int res=0,f_f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f_f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') res=(res<<3)+(res<<1)+(ch-'0'),ch=getchar();
    return res*f_f;
}
inline void add_edge(int from,int to,int cost){
    edges[++E_cnt]=Edge(from,to,cost,lst[from]);
    lst[from]=E_cnt;
}
inline int get_rev(int x,int y){
    for (int i=1;i<=(y>>1);i++){
        int l=i,r=y-i+1,pl=(x>>l-1)&1,pr=(x>>r-1)&1;
        x^=((pl^pr)<<l-1)^((pl^pr)<<r-1);
    }
    return x;
}
inline void solve(int limit){
    for (int i=1;i<=limit;i++){
        memset(dp[i&1],0,sizeof(dp[i&1]));
        int full=(1<<i-1)-1;
        for (int j=1;j<=n;j++){
            for (int mask=0;mask<=full;mask++){
                if(!dp[i-1&1][j][mask]) continue;
                for (int k=lst[j];~k;k=edges[k].nxt){
                    Edge &e=edges[k];
                    dp[i&1][e.to][mask|(e.cost<<i-1)]=1;
                }
            }
        }
    }
}
int main(){
    memset(lst,-1,sizeof(lst));
    n=read(),m=read(),d=read(),E_cnt=-1;
    for (int i=1;i<=m;i++){
        int from=read(),to=read(),cost=read();
        add_edge(from,to,cost),add_edge(to,from,cost);
    }
    int full=(1<<(d+1>>1))-1,l=d-(d+1>>1);
    dp[0][1][0]=1,solve(d+1>>1);
    for (int i=1;i<=n;i++)
        for (int mask=0;mask<=full;mask++) cur[i][mask]=dp[(d+1>>1)&1][i][mask];
    memset(dp,0,sizeof(dp));
    for (int i=1;i<=n;i++) dp[0][i][0]=1;
    solve(l);
    for (int i=1;i<=n;i++){
        for (int mask=0;mask<=full;mask++){
            if(!cur[i][mask]) continue;
            int now=get_rev(mask,(d+1>>1));
            for (int sta=0;sta<=(1<<l)-1;sta++){
                if(!dp[l&1][i][sta]) continue;
                ans[(now<<l)|sta]=1;
            }
        }
    }
    full=(1<<d)-1;
    for (int i=0;i<=full;i++) tot+=ans[i];
    printf("%d\n",tot);
    return 0;
}
