/*
after dusk passed,
there is a starry sky.
*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
using namespace std;
const int N=2*1e5+100;
int n,k,dp[N],sum[N],de[N],maxde[N],son[N],id[N];
int tot,first[N],nxt[N*2],point[N*2];
struct st
{
    int num,MAX;
};
vector <st> p[N];
inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void add_edge(int x,int y)
{
    tot++;
    nxt[tot]=first[x];
    first[x]=tot;
    point[tot]=y;
}
void dfs(int x,int fa)
{
    maxde[x]=de[x];
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int u=point[i];if (u==fa) continue;
        de[u]=de[x]+1;
        dfs(u,x);
        if (maxde[u]>maxde[son[x]]) son[x]=u;
        maxde[x]=max(maxde[x],maxde[u]);
    }
}
void dfs1(int x,int fa)
{
    if (!son[x])
    {
        p[id[x]].push_back((st){1,1});
        return;
    }
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int u=point[i];if (u==fa) continue;
        dfs1(u,x);
    }
    id[x]=id[son[x]];
    p[id[x]].push_back((st){1,max(p[id[x]].back().MAX,1)});
    int m=(int)p[id[x]].size()-1,now=0;
    if (m-k-1>=0) now=p[id[x]][m-k-1].MAX;
    p[id[x]][m].num+=now,p[id[x]][m].MAX=max(now+1,p[id[x]][m-1].MAX);
    for (int q=first[x];q!=-1;q=nxt[q])
    {
        int u=point[q];if (u==fa||u==son[x]) continue;
        int tmp=p[id[u]].size();
        for (int i=0;i<=maxde[u]+1;i++)
        {
            int to=max(i,k-i+1);
            dp[i]=0;
            if (tmp-to>=0) dp[i]=max(dp[i],p[id[x]][m-i].num+p[id[u]][tmp-to].MAX);
            if (i==0) continue;
            dp[i]=max(dp[i],p[id[u]][tmp-i].num);
            if (m-to>=0) dp[i]=max(dp[i],p[id[u]][tmp-i].num+p[id[x]][m-to].MAX);
        }
        for (int i=maxde[u]+1;i>=0;i--)
        {
            p[id[x]][m-i].num=max(p[id[x]][m-i].num,dp[i]);
            p[id[x]][m-i].MAX=p[id[x]][m-i].num;
            if (m-i) p[id[x]][m-i].MAX=max(p[id[x]][m-i-1].MAX,p[id[x]][m-i].MAX);
        }
    }
}
signed main()
{
//  freopen("1.in","r",stdin);
    tot=-1;
    memset(first,-1,sizeof(first));
    n=read();k=read()-1;
    for (int i=2;i<=n;i++)
    {
        int u=read()+1;
        add_edge(u,i);
        add_edge(i,u);
    }
    dfs(1,1);
    for (int i=1;i<=n;i++) id[i]=i,maxde[i]-=de[i];
    dfs1(1,1);
    int m=p[id[1]].size()-1;
    printf("%d\n",p[id[1]][m].MAX);
}
