	
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define m_p make_pair
#define sz(x) (int)x.size()
#define line cerr<<"--------------------\n";
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define gc() getchar()
//char buf[1<<23],*p1=buf,*p2=buf;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <class T> void read(T &x)
{
    x=0; char c=gc(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=gc();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=gc();
    if (flag) x=-x;
}
template <class T> inline T _max(T a,T b){return a>b ? a : b;}
template <class T> inline T _min(T a,T b){return a<b ? a : b;}
template <class T> inline bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> inline bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=105,M=100005;
const ll inf=10000000000000;
int mabs(int x){return x>0 ? x : -x;}
int n,m,S,T;
int a[N],b[N];
int e=1,first[N],nxt[M<<1],point[M<<1],cost[M<<1],val[M<<1];
int lst_point[N],lst_e[N],inque[N];
ll dis[N];
void add_edge(int x,int y,int cap,int co)
{
    nxt[++e]=first[x]; first[x]=e; point[e]=y;
    val[e]=cap; cost[e]=co;
}

void addE(int x,int y,int cap,int _cost)
{
    add_edge(x,y,cap,_cost);
    add_edge(y,x,0,-_cost);
}

void init()
{
    read(n); read(m);
    for (int i=1;i<=n;++i) read(a[i]);
    for (int i=1;i<=m;++i) read(b[i]);
    memset(first,-1,sizeof first);
    S=1; T=n+m+2;
    for (int i=1;i<=n;++i)
    {
        addE(S,i+1,1,0);
    }
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=m;++j)
        {
            addE(i+1,n+j+1,1,mabs(a[i]-b[j]));
        }
    }
    for (int i=1;i<=m;++i)
    {
        addE(n+i+1,T,1,0);
    }
}

bool spfa(int S,int T)
{
    queue <int> q;
    for (int i=1;i<=n+m+2;++i)
    {
        inque[i]=lst_point[i]=lst_e[i]=0;
        dis[i]=inf;
    }
    q.push(S); inque[S]=1; dis[S]=0;
    while (!q.empty())
    {
        int now=q.front(); q.pop();
        inque[now]=0;
        for (int i=first[now];i!=-1;i=nxt[i])
        {
            int to=point[i];
            if (val[i]&&dis[now]+cost[i]<dis[to])
            {
                dis[to]=dis[now]+cost[i];
                lst_point[to]=now;
                lst_e[to]=i;
                if (!inque[to])
                {
                    inque[to]=1;
                    q.push(to);
                }
            }
        }
    }
    if (dis[T]==inf) return 0;
    else return 1;
}

ll MCMF()
{
    ll Cost=0;
    while (spfa(S,T))
    {
        int x=T; int delta=2000000000;
        while (x!=S)
        {
            checkmin(delta,val[lst_e[x]]);
            x=lst_point[x];
        }
        x=T;
        while (x!=S)
        {
            val[lst_e[x]]-=delta;
            val[lst_e[x]^1]+=delta;
            x=lst_point[x];
        }
        Cost+=(ll)delta*dis[T];
    }
    return Cost;
}

void solve()
{
    printf("%lld\n",MCMF());
}

int main()
{
    init();
    solve();
    return 0;
}