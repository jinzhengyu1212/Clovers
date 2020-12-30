#pragma GCC optimize(2)
// #pragma GCC optimize(3)
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
using namespace std;
const int N=92,M=10100;
int n,m,d,ans,vpre[N][11][(1<<10)+10],vsuc[N][11][(1<<10)+10];
int nd;
int tot,first[N],nxt[M*2],point[M*2],len[M*2];
bitset <2000> pre[N],f[(1<<10)+1];
inline void add_edge(int x,int y,int z)
{
    tot++;
    nxt[tot]=first[x];
    first[x]=tot;
    point[tot]=y;
    len[tot]=z;
}
signed main()
{
    // freopen("1.in","r",stdin);
    tot=-1;
    memset(first,-1,sizeof(first));
    scanf("%d%d%d",&n,&m,&d);
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
 
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    vpre[1][0][0]=1;
    for (int j=1;j<=d/2;j++)
    {
        int full=(1<<j)-1;
        for (int i=1;i<=n;i++)
        {
            for (int mask=0;mask<=full;mask++)
            {
                for (int k=first[i];k!=-1;k=nxt[k])
                {
                    int u=point[k];
                    if (len[k]!=(mask&1)) continue;
                    if (vpre[u][j-1][mask>>1])
                    {
                        vpre[i][j][mask]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        int full=(1<<(d/2))-1;
        for (int mask=0;mask<=full;mask++)
        {
            if (vpre[i][d/2][mask]) pre[i][mask]=1;
        }
    }
    for (int i=1;i<=n;i++) vsuc[i][0][0]=1;
    for (int j=1;j<=d-d/2;j++)
    {
        int full=(1<<j)-1;
        for (int i=1;i<=n;i++)
        {
            for (int mask=0;mask<=full;mask++)
            {
                for (int k=first[i];k!=-1;k=nxt[k])
                {
                    int u=point[k];
                    if (len[k]!=(mask&1)) continue;
                    if (vsuc[u][j-1][mask>>1])
                    {
                        vsuc[i][j][mask]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int mask=0;mask<=(1<<(d-d/2))-1;mask++)
        {
            if (vsuc[i][d-d/2][mask]) f[mask]|=pre[i];
        }
    }
    int full=(1<<(d-d/2))-1;
    for (int mask=0;mask<=full;mask++) ans+=(int)f[mask].count();
    printf("%d\n",ans);
}