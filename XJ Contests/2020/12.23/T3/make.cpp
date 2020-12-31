/*
after dusk passed,
there is a starry sky.
*/
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
using namespace std;
const int N=2*1e5+100;
int n,m,l,a[N],b[N];
inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int ran(int l,int r)
{
    return 1ll*rand()*rand()%(r-l+1)+l;
}
inline void print(int y[],int n)
{
    for (int i=1;i<=n;i++) printf("%d",y[i]);
    printf("\n");
}
bool check(int x)
{
    if (x>=n) return b[x-n];
    else return a[x];
}
signed main()
{
    srand(time(0));
    n=5;l=5;
    printf("%d %d\n",n,l);
    for (int i=1;i<=n;i++) printf("%d %d\n",ran(1,10),ran(1,10));
    for (int i=1;i<=n;i++) a[i]=i;
    random_shuffle(a+1,a+1+n);
    m=ran(1,n);printf("%d\n",m);
    for (int i=1;i<=m;i++) printf("%d ",a[i]);
    printf("\n");
}