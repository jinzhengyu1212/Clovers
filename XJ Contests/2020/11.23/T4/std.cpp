#include <cstdio>
#include <algorithm>
#define N 100005
#define ll long long
using namespace std;

struct arr
{
    ll x,y;
}a[N];
ll p[N],sumx[N],sumy[N],n,m;

int so(arr u,arr v)
{
    if (u.x==v.x) return u.y>v.y;
    return u.x>v.x;
}

int find(int o,ll sump)
{
    int l=o,r=n;
    while (l<r)
    {
        int mid=(l+r)/2;
        ll sum=sumx[mid]-sumx[o-1];
        if (sum<=sump) l=mid+1;
            else r=mid;
    }
    if (sumx[l]-sumx[o-1]>sump) l--;
    return l;
}

int main()
{
    //freopen("pack.in","r",stdin);
    //freopen("pack.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%lld%lld",&a[i].x,&a[i].y);
    for (int i=1;i<=m;i++)
        scanf("%lld",&p[i]);
    sort(a+1,a+n+1,so);
    for (int i=1;i<=n;i++)
    {
        sumx[i]=sumx[i-1]+a[i].x;
        sumy[i]=sumy[i-1]+a[i].y;
    }
    for (int i=1;i<=m;i++)
    {
        ll ans=0;
        int s=0;
        while (p[i]>=a[n].x)
        {
            int l=s+1,r=n+1;
            while (l<r)
            {
                int mid=(l+r)/2;
                if (a[mid].x>p[i]) l=mid+1;
                    else r=mid;
            }
            s=find(l,p[i]);
            p[i]-=sumx[s]-sumx[l-1];
            ans+=sumy[s]-sumy[l-1];
            if (s==n) break;
        }
        printf("%lld\n",ans);
    }
    fclose(stdin);
    fclose(stdout);
}