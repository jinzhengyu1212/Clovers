
#include <bits/stdc++.h>
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
unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
mt19937 my_rand(seed);
template <class T> T ran(T l,T r){return my_rand()%(r-l+1)+l;}
int a[10000];
void init()
{
    int n=ran(2,10),m=ran(2,100);
    printf("%d %d\n",n,m);
    for (int i=1;i<=n;++i)
    {
        int x=ran(1,1000000);
        printf("%d ",x);
    } cout<<endl;
    for (int i=2;i<=n;++i)
    {
        int l=ran(1,10000),fa=ran(1,i-1);
        printf("%d %d %d\n",fa,i,l);
    }
    while (m--)
    {
        int s=ran(1,n); int t=ran(1,n);
        printf("%d %d\n",s,t);
    }
}

void solve()
{
}

int main()
{
    //setIO("");
    init();
    solve();
    closefile;
    return 0;
}