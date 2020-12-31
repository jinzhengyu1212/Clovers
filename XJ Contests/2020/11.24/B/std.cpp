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
const int N=1005;
int n,m;
int g[N][N];
void init()
{
    read(n); read(m);
    for (int i=1,u,v;i<=m;++i)
    {
        read(u); read(v);
        g[u][v]=1;
    }
}

void solve()
{
    ll ans=0;
    for (int i=1;i<=n;++i)
    {
        for (int j=i+1;j<=n;++j)
        {
            for (int k=i+1;k<=n;++k)
            {
                if (j==k) continue;
                for (int l=i+1;l<=n;++l)
                {
                    if (j==l||k==l) continue;
                    if (g[i][j]&&g[j][k]&&g[k][l]&&g[l][i]) ++ans;
                }
            }
        }
    }
    printf("%lld\n",ans);
}

int main()
{
    //setIO("country");
    init();
    solve();
    closefile;
    return 0;
}