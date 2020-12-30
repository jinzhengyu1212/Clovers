/*
after dusk passed,
there is a starry sky.
*/
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
#define int long long
using namespace std;
const int N=1e5+100;
int n,l,a[N],b[N],ans;
map <int,vector<int> > mp;
inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void getup(int l,int r)
{
    for (int i=l;i<=r;)
    {
        int j=i;
        while(j<=r&&mp[b[j]-j][0]==mp[b[i]-i][0]) j++;
        ans+=mp[b[i]-i][0]-i;
        i=j;
    }
}
inline void getdown(int l,int r)
{
    for (int i=r;i>=l;)
    {
        int j=i;
        while(j>=l&&mp[b[j]-j].back()==mp[b[i]-i].back()) j--;
        ans+=i-mp[b[i]-i].back();
        i=j;
    }
}
signed main()
{
    // freopen("1.txt","r",stdin);
    n=read();l=read();
    for (int i=1;i<=n;i++) a[i]=read();
    for (int i=1;i<=n;i++) b[i]=read();
    a[0]=0;a[n+1]=l+1;
    for (int i=0;i<=n+1;i++) mp[a[i]-i].push_back(i);
    bool bl=1;
    for (int i=1;i<=n;i++) if (mp[b[i]-i].empty()) bl=0;
    if (!bl)
    {
        printf("-1\n");
        return 0;
    }
    for (int i=1;i<=n;)
    {
        int j=i;
        while(j<=n&&(b[j]<=a[j])==(b[i]<=a[i])) j++;
        if (b[i]<=a[i]) getdown(i,j-1);
        else getup(i,j-1);
        i=j;
    }
    printf("%lld\n",ans);
}