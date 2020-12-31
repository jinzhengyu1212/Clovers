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
int ran(int l,int r){return (ll)my_rand()%(r-l+1)+l;}
int a[200005];
void init()
{
    int n=ran(1,2000);
    int m=ran(1,2000);
    printf("%d %d\n",n,m);
    int L=200000;
    for (int i=1;i<=n;++i)
    {
        a[i]=ran(0,L);
        printf("%d ",a[i]);
    }printf("\n");
    for (int i=1;i<=m;++i)
    {
        int opt=ran(1,2);
        if (opt==3||opt==4)
        {
            int l=ran(1,n); int r=ran(l,n);
            printf("%d %d %d\n",opt,l,r);
        }
        else
        {
            int x=ran(1,n);
            int y=opt==1 ? ran(0,L) : ran(0,_min(a[x],L));
            printf("%d %d %d\n",opt,x,y);
            if (opt==1) a[x]+=y;
            else a[x]-=y;
        }
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