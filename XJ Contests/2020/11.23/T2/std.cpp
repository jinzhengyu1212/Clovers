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
int n,m,mod;
inline int Mul(int a,int b){return (ll)a*b%mod;}
inline void mul(int &a,int b){a=(ll)a*b%mod;}
inline int qpow(int a,int b){int ans=1; while (b) {if (b&1) ans=(ll)ans*a%mod; a=(ll)a*a%mod; b>>=1;} return ans;}
const int N=200005;
int e=0,first[N],nxt[N],point[N],deg[N];
int fac[N],ifac[N],f[N],sz[N];
void add_edge(int x,int y)
{
    //out(x); outln(y);
    ++e;
    nxt[++e]=first[x];
    first[x]=e;
    point[e]=y;
    ++deg[y];
}
int binom(int x,int y){return x<y ? 0 : Mul(fac[x],Mul(ifac[y],ifac[x-y]));}

void init()
{
    read(n); read(m); read(mod);
    e=0; memset(first,-1,sizeof first);
    fac[0]=1; for (int i=1;i<=n;++i) fac[i]=Mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],mod-2); for (int i=n-1;i>=0;--i) ifac[i]=Mul(ifac[i+1],i+1);
    for (int i=1,u,v;i<=m;++i)
    {
        read(u); read(v);
        add_edge(v,u);
    }
    for (int i=1;i<=n;++i) if (!deg[i]) add_edge(0,i);
}

void dfs(int x)
{
    f[x]=1;
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int to=point[i];
        dfs(to);
        sz[x]+=sz[to];
        mul(f[x],f[to]);
        mul(f[x],binom(sz[x],sz[to]));
    }
    sz[x]++;
}

void solve()
{
    dfs(0);
    if (sz[0]!=n+1) printf("0\n");
    else printf("%d\n",f[0]);
    for (int i=0;i<=n;++i) deg[i]=0,sz[i]=0,f[i]=0;
}

int main()
{
    //setIO("photo");
    int t; read(t); while (t--)
    {
        init();
        solve();
    }
    closefile;
    return 0;
}