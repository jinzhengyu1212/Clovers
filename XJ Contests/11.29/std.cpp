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
const int mod=998244353,N=200005;
inline int Add(int a,int b){a+=b; return a>=mod ? a-mod : a;}
inline int Sub(int a,int b){a-=b; return a<0 ? a+mod : a;}
inline int Mul(int a,int b){return (ll)a*b%mod;}
inline void add(int &a,int b){a+=b; (a>=mod) && (a-=mod);}
inline void sub(int &a,int b){a-=b; (a<0) && (a+=mod);}
inline void mul(int &a,int b){a=(ll)a*b%mod;}
inline int qpow(int a,int b){int ans=1; while (b) {if (b&1) ans=(ll)ans*a%mod; a=(ll)a*a%mod; b>>=1;} return ans;}
int n;
int e=0,first[N],nxt[N<<1],point[N<<1];
int r,deg=0;
int dep[N];
int a[505][505],Max=0,ans[505],f[505][505];
void add_edge(int x,int y)
{
    nxt[++e]=first[x];
    first[x]=e;
    point[e]=y;
}

void dfs(int x,int f)
{
    dep[x]=dep[f]+1;
    ++a[deg][dep[x]];
    checkmax(Max,dep[x]);
    for (int i=first[x];i!=-1;i=nxt[i])
    {
        int to=point[i];
        if (to==f) continue;
        dfs(to,x);
    }
}

void init()
{
    read(n);
    memset(first,-1,sizeof first);
    for (int i=1,u,v;i<n;++i)
    {
        read(u); read(v);
        add_edge(u,v);
        add_edge(v,u);
    }
}

void solve()
{
    for (r=1;r<=n;++r)
    {
        deg=0;
        for (int i=first[r];i!=-1;i=nxt[i]) ++deg;
        for (int i=1;i<=deg;++i) for (int j=1;j<=n;++j) a[i][j]=0;
        dep[r]=0;
        deg=0;
        for (int i=first[r];i!=-1;i=nxt[i])
        {
            int to=point[i];
            ++deg;
            dfs(to,r);
        }
        for (int d=1;d<=Max;++d)
        {
            for (int i=0;i<=deg;++i) f[i][0]=1;
            for (int i=1;i<=deg;++i) for (int j=1;j<=deg;++j) f[i][j]=0;
            for (int i=1;i<=deg;++i)
            {
                for (int j=1;j<=deg;++j)
                {
                    f[i][j]=Add(f[i-1][j],Mul(f[i-1][j-1],a[i][d]));
                }
            }
            for (int i=1;i<=deg;++i) add(ans[i],f[deg][i]);
        }
    }
    for (int i=3;i<n;++i) printf("%d\n",ans[i]);
}

int main()
{
    //setIO("e");
    init();
    solve();
    closefile;
    return 0;
}