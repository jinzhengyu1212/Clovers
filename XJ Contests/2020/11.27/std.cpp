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
const int N=1000005;
ll gcd(ll a,ll b){return b ? gcd(b,a%b) : a;}
int n;
ll a[N];
ll b[N];
void init()
{
    read(n);
    for (int i=1;i<=n;++i)
    {
        read(a[i]);
    }
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i)
    {
        b[i]+=(i-1);
        b[i]-=(n-i);
        b[i]+=2LL*(i-1)*(i-1);
        b[i]-=2LL*(n-i)*(n-i-1);
    }
}

void solve()
{
    if (n==1)
    {
        printf("%lld 1\n",a[1]);
        return;
    }
    ll B=(ll)n*(n-1),A=0,tot=0;
    for (int i=1;i<=n;++i)
    {
        tot+=b[i]*a[i]/B;
        A+=(ll)b[i]*a[i]%B;
    }
    ll g=gcd(A,B);
    A/=g,B/=g;
    A+=B*tot;
    if (A<0&&B<0) A=-A,B=-B;
    printf("%lld %lld\n",A,B);
}

int main()
{
    //setIO("");
    init();
    solve();
    closefile;
    return 0;
}