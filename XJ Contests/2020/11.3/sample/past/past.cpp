#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 10005
using namespace std;
 
int n;

struct Tree{
struct node{
    int y,nxt;
}e[maxn*2];
 
int x,y;
int tot=0,head[maxn];
int dep[maxn],pos[maxn*2];
int a[maxn*2];
int dfn=0;
int f[maxn*2][18];
 
inline void add_edge(int x,int y)
{
    ++tot;
    e[tot].y=y;e[tot].nxt=head[x];head[x]=tot;
}
inline void dfs(int u,int fa)
{
    a[++dfn]=u;
    pos[u]=dfn;
    dep[u]=dep[fa]+1;
    for(register int i=head[u];i;i=e[i].nxt)
    {
        if(e[i].y!=fa)
        {
            dfs(e[i].y,u);
            a[++dfn]=u;
        }
    }
}
inline void st()
{
    memset(f,0x3f,sizeof(f));
    for(register int i=1;i<=dfn;i++)
    {
        f[i][0]=a[i];
    }
    for(register int j=1;j<=16;j++)
    {
        for(register int i=1;i+(1<<j)<=dfn;i++)
        {
            if(dep[f[i][j-1]]<dep[f[i+(1<<(j-1))][j-1]])f[i][j]=f[i][j-1];
            else f[i][j]=f[i+(1<<(j-1))][j-1];
        }
    }
}
void init(){
    memset(dep,0x3f,sizeof(dep));
    dep[1]=0;
    dfs(1,0);
    st();
}
int dist(int x,int y){
    int ans;
    if(pos[x]>pos[y]) swap(x,y);
    int l1=pos[x],l2=pos[y];
    int len=log2(l2-l1+1);
    if(dep[f[l1][len]]<dep[f[l2-(1<<len)+1][len]]) ans=f[l1][len];
    else ans=f[l2-(1<<len)+1][len];
    return dep[x]+dep[y]-2*dep[ans];
}
}T1,T2;

typedef long long ll;
const ll MOD=998244353;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        T1.add_edge(x,y); T1.add_edge(y,x);
    }
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        T2.add_edge(x,y); T2.add_edge(y,x);
    }
    T1.init(); T2.init();
    ll ans=0;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            int dis1=T1.dist(i,j);
            int dis2=T2.dist(i,j);
            ans=(ans+1ll*dis1*dis2%MOD)%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}