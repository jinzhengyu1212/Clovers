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
const int N=2000005;
int n,m,k,len;
int a[N],top=0;
char s[N],t[N];
void init()
{
    read(n); read(m); read(k);
    scanf("%s",s+1);
    for (int i=1;i+i<=n+1;++i) swap(s[i],s[n+1-i]);
    scanf("%s",t+1);
    for (int i=1;i+i<=m+1;++i) swap(t[i],t[m+1-i]);
    len=_max(n,m);
    for (int i=n+1;i<=len;++i) s[i]='0';
    for (int i=m+1;i<=len;++i) t[i]='0';
    outln(len);
    for (int i=len;i>=1;--i) printf("%c",s[i]); printf("\n");
    for (int i=len;i>=1;--i) printf("%c",t[i]); printf("\n");
}

void solve()
{
    for (int rnd=1;rnd<=10;++rnd)
    {
        top=0;
        outarr(s,1,len); outarr(t,1,len);
        for (int i=1;i<=len;++i)
        {
            if (s[i]=='1'&&t[i]=='1') a[++top]=i;
        }
        outarr(a,1,top);
        for (int i=1;i<=top;++i)
        {
            int pos=a[i];
            while (s[pos]=='1')
            {
                s[pos]='0';
                ++pos;
            }
            if (pos>n) ++n;
            s[pos]='1';
        }
        for (int i=1;i<=top;++i)
        {
            int pos=a[i];
            while (t[pos]=='1')
            {
                t[pos]='0';
                ++pos;
            }
            if (pos>m) ++m;
            t[pos]='1';
        }
        len=_max(n,m);
    }
}

int main()
{
    init();
    solve();
    return 0;
}