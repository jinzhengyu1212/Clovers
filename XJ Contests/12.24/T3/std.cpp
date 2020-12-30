
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
double A=clock();
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) {cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;}
#define user_time cerr<<fixed<<setprecision(6)<<(clock()-A)*1.0/CLOCKS_PER_SEC<<endl
#define m_p make_pair
#define sz(x) (int)x.size()
template <class T> void read(T &x)
{
    x=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if (flag) x=-x;
}
template <class T> T _max(T a,T b){return b>a ? b : a;}
template <class T> T _min(T a,T b){return b<a ? b : a;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=100005,LOG=18,inf=0x3f3f3f3f;
int n,m;
int e=0,first[N],nxt[N<<1],point[N<<1],value[N<<1];
int a[N],s[N],t[N];
int Min,Root,total,siz[N];
int cover[N],vis[N],Next[N];
pii arr[N];int top=0;
ll ans[N],sum[N],dis[N];
int fa[LOG+1][N],g[LOG+1][N];
vector<int> u[N],d[N],Q[N];
void add_edge(int x,int y,int z)
{
    nxt[++e]=first[x];
    first[x]=e;
    point[e]=y;
    value[e]=z;
}

void init()
{
    read(n); read(m);
    for (int i=1;i<=n;++i) read(a[i]);
    memset(first,-1,sizeof first);
    for (int i=1,u,v,w;i<n;++i)
    {
        read(u); read(v); read(w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    for (int i=1;i<=m;++i) read(s[i]),read(t[i]);
}

void get_siz(int x,int f)
{
    siz[x]=1;
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (to==f||vis[to]) continue;
        get_siz(to,x);
        siz[x]+=siz[to];
    }
}

void get_root(int x,int f)
{
    int Max=total-siz[x];
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (to==f||vis[to]) continue;
        get_root(to,x);
        checkmax(Max,siz[to]);
    }
    if (checkmin(Min,Max)) Root=x;
}

void Cover(int x,int f,int r)
{
    cover[x]=r;
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (vis[to]||to==f) continue;
        Cover(to,x,r);
    }
}

void get_control(int x)
{
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (vis[to]) continue;
        Cover(to,x,to);
    }
}

void pre_dfs(int x,int f)
{
    fa[0][x]=f; g[0][x]=a[x];
    for (int i=1;i<=LOG;++i)
    {
        fa[i][x]=fa[i-1][fa[i-1][x]];
        g[i][x]=_min(g[i-1][x],g[i-1][fa[i-1][x]]);
    }
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (to==f||vis[to]) continue;
        dis[to]=dis[x]+value[i];
        pre_dfs(to,x);
    }
}

int getSmall(int x)
{
    int val=a[x];
    for (int i=LOG;i>=0;--i)
        if (g[i][x]>=val) x=fa[i][x];
    return x;
}

void dfs_up(int x,int f)
{
    int tmp=getSmall(x);
    if (!tmp) Next[x]=x,sum[x]=a[x]*dis[x];
    else Next[x]=Next[tmp],sum[x]=sum[tmp]+a[x]*(dis[x]-dis[tmp]);
    for (int i=0;i<sz(u[x]);++i) ans[u[x][i]]+=sum[x];
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int to=point[i];
        if (to==f||vis[to]) continue;
        dfs_up(to,x);
    }
}

void dfs_down(int x,int f,int now_min)
{
    arr[++top]=m_p(now_min,x);
    for (int i=0;i<sz(d[x]);++i)
    {
        int idx=d[x][i],w=a[Next[s[idx]]];
        ll num=0;
        if (now_min>=w) num=w*dis[x];
        else
        {
            int lst=upper_bound(arr+1,arr+top+1,m_p(w,0),greater<pii>())->second;
            num=w*dis[lst]+sum[x]-sum[lst];
        }
        ans[idx]+=num;
    }
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (vis[to]||to==f) continue;
        sum[to]=sum[x]+value[i]*now_min;
        dfs_down(to,x,_min(now_min,a[to]));
    }
    --top;
}

void doit(int x)
{
    dis[x]=0;
    pre_dfs(x,0);
    sum[x]=0;
    dfs_up(x,0);
    sum[x]=0;
    dfs_down(x,0,a[x]);
}

void dfs(int x)
{
    vis[x]=1; cover[x]=x;
    get_control(x); 
    vector<int> now=Q[x];
    for (int i=0;i<sz(now);++i)
    {
        int idx=now[i];
        //out(x); out(i); outln(idx);
        if (cover[s[idx]]^cover[t[idx]])
        {
            u[s[idx]].push_back(idx);
            d[t[idx]].push_back(idx);
        }
        else Q[cover[s[idx]]].push_back(idx);
    }
    doit(x);
    for (int i=0;i<sz(now);++i)
    {
        int idx=now[i];
        if (cover[s[idx]]^cover[t[idx]])
        {
            u[s[idx]].clear();
            d[t[idx]].clear();
        }
    }
    Q[x].clear();
    for (int i=first[x];~i;i=nxt[i])
    {
        int to=point[i];
        if (vis[to]) continue;
        Min=n; Root=0; get_siz(to,x); total=siz[to]; get_root(to,x);
        if (to!=Root) Q[Root]=Q[to],Q[to].clear();
        dfs(Root);
    }
}

void solve()
{
    Min=n; Root=0; get_siz(1,0); total=siz[1]; get_root(1,0);
    for (int i=1;i<=m;++i) Q[Root].push_back(i);
    dfs(Root);
    for (int i=1;i<=m;++i) printf("%lld\n",ans[i]);
}

int main()
{
    init();
    solve();
    return 0;
}