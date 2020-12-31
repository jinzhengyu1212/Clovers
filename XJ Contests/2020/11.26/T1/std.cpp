	
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template <class T> void read(T &x)
{
    x=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if (flag) x=-x;
}
template <class T> T _max(T a,T b){return a>b ? a : b;}
template <class T> T _min(T a,T b){return a<b ? a : b;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=100005;
int n,k;
int e=0,first[N],nxt[N<<1],point[N<<1];
int f[N][2],fa[N],vis[N],mark[N];
void add_edge(int x,int y)
{
    nxt[++e]=first[x];
    first[x]=e;
    point[e]=y;
}

void init()
{
    read(n); read(k);
    for (int i=1;i<=n;++i) f[i][0]=f[i][1]=0,first[i]=-1;
    for (int i=2;i<=n;++i)
    {
        read(fa[i]);
        add_edge(fa[i],i);
    }
}

void solve()
{
    int ans=n-1;
    for (int S=0;S<(1<<(n-1));++S)
    {
        int cnt=0;
        for (int i=1;i<=n;++i) vis[i]=0;
        for (int i=0;i<n-1;++i)
        {
            if (S>>i&1) ++cnt,vis[i+2]=vis[fa[i+2]]=1;
        }
        int tot=0;
        for (int i=1;i<=n;++i)
            if (vis[i]) ++tot;
        if (tot>=k) checkmin(ans,cnt);
    }
    printf("%d\n",ans);
}

int main()
{
    //setIO("");
    int t; read(t); while (t--)
    {
        init();
        solve();
    }
    closefile;
    return 0;
}