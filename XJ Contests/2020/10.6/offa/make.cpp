#include <bits/stdc++.h>
using namespace std;
const int N=5*1e6+100;
int n,m,k,t[N],q,a[N],b[N],p[N];
int ran(int l,int r)
{
    return 1ll*rand()*rand()%(r-l+1)+l;
}
signed main()
{
    // freopen("data.in","w",stdout);
    srand(time(0));
    n=8;
    for (int i=1;i<=n;i++) a[i]=ran(1,n/2);
    for (int i=1;i<=n;i++) p[i]=ran(-100,100);
    int last=0;
    for (int i=ran(1,n/2);i<=n;i++)
    {
        if (a[i]>last) b[++m]=a[i],last=a[i];
        if (m==4) break;
    }
    printf("%d\n",n);
    for (int i=1;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
    for (int i=1;i<=n;i++) printf("%d ",p[i]);
    printf("\n");
    printf("%d\n",m);
    for (int i=1;i<=m;i++) printf("%d ",b[i]);
    printf("\n");
}