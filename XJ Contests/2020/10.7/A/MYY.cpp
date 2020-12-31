//#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cassert>
#include <cmath>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define sz(x) (int)x.size()
#define m_p make_pair
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;
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
const int N=91;
int n,m,d;
bitset<1048576> ans;
bitset<1024> f[91][91][11],S[91];
int e=0,first[N],nxt[N*N*2],point[N*N*2],value[N*N*2];
void add_edge(int x,int y,int z)
{
    nxt[++e]=first[x];
    first[x]=e;
    point[e]=y;
    value[e]=z;
}
 
void init()
{
    read(n); read(m); read(d);
    memset(first,-1,sizeof first);
    for (int i=1;i<=m;++i)
    {
        int u,v,c;
        read(u); read(v); read(c);
        add_edge(u,v,c);
        add_edge(v,u,c);
    }
}
 
void solve()
{
    int d1=(d+1)/2,d2=d-d1;
    for (int r=1;r<=n;++r)
    {
        for (int i=first[r];i!=-1;i=nxt[i])
        {
            int to=point[i];
            if (value[i]) f[r][to][1][1]=1;
            else f[r][to][1][0]=1;
        }
        for (int i=1;i<d1;++i)
        {
            for (int j=1;j<=n;++j)
            {
                for (int p=first[j];p!=-1;p=nxt[p])
                {
                    int to=point[p];
                    if (value[p]) f[r][to][i+1]|=(f[r][j][i]<<(1<<i));
                    else f[r][to][i+1]|=f[r][j][i];
                }
            }
        }
        for (int i=1;i<=n;++i)
        {
            S[r]|=f[r][i][d2];
        }
    }
    //for (int i=1;i<=n;++i) cout<<f[1][i][d1]<<endl;cout<<endl;
    //for (int i=1;i<=n;++i) cout<<S[i]<<endl;
    for (int i=1;i<=n;++i)
    {
        for (int U=0;U<(1<<d1);++U)
        {
            for (int T=0;T<(1<<d2);++T)
            {
                if (f[1][i][d1][U]&&S[i][T])
                {
                    //out(i); out(U); outln(T);
                    ans[(U<<d2)|T]=1;
                }
            }
        }
    }
    printf("%d\n",(int)ans.count());
}
 
int main()
{
    init();
    solve();
    return 0;
}