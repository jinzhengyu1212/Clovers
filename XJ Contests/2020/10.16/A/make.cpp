#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
mt19937 my_rand(seed);
const int N=1000005;
int ran(int l,int r)
{
    return (ll)my_rand()*my_rand()%(r-l+1)+l;
}

int a[N],b[N],w[N];
signed main()
{
    srand(time(0));
    int n=100000,q=100000;
    printf("%d %d\n",n,q);
    for (int i=1;i<=n;++i)
    {
        int x=ran(1,1000000000);
        printf("%d ",x);
    }printf("\n");
    for (int i=2;i<=n;++i)
    {
        int x=ran(1,i-1);
        printf("%d %d\n",x,i);
    }
    for (int i=1;i<=q;++i)
    {
        int x=ran(1,n);
        int y=ran(1,1000000000);
        printf("%d %d\n",x,y);
    }
    return 0;
}