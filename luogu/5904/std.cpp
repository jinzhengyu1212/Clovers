#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define MAX 100100
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Line{int v,next;}e[MAX<<1];
int h[MAX],cnt=1,n;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int dep[MAX],hson[MAX],md[MAX];
void dfs1(int u,int ff)
{
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;if(v==ff)continue;
        dfs1(v,u);md[u]=max(md[u],md[v]);
        if(md[v]>md[hson[u]])hson[u]=v;
    }
    md[u]=md[hson[u]]+1;
}
ll *f[MAX],*g[MAX],tmp[MAX<<2],*id=tmp,ans;
void dfs(int u,int ff)
{
    if(hson[u])f[hson[u]]=f[u]+1,g[hson[u]]=g[u]-1,dfs(hson[u],u);
    f[u][0]=1;ans+=g[u][0];
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;if(v==ff||v==hson[u])continue;
        f[v]=id;id+=md[v]<<1;g[v]=id;id+=md[v]<<1;
        dfs(v,u);
        for(int j=0;j<md[v];++j)
        {
            if(j)ans+=f[u][j-1]*g[v][j];
            ans+=g[u][j+1]*f[v][j];
        }
        for(int j=0;j<md[v];++j)
        {
            g[u][j+1]+=f[u][j+1]*f[v][j];
            if(j)g[u][j-1]+=g[v][j];
            f[u][j+1]+=f[v][j];
        }
    }
}
int main()
{
    n=read();
    for(int i=1,u,v;i<n;++i)u=read(),v=read(),Add(u,v),Add(v,u);
    dfs1(1,0);f[1]=id;id+=md[1]<<1;g[1]=id;id+=md[1]<<1;
    dfs(1,0);printf("%lld\n",ans);
    return 0;
}