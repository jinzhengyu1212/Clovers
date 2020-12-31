#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500005,inf=2e18;
int a[N],s[N],mp[N];
signed main()
{
    int T;
    scanf("%lld",&T);
    while(T--)
    {
        int n,q,top=0;
        scanf("%lld%lld",&n,&q);
        for(int i=1;i<=n;i++) scanf("%lld",a+i);
        a[n+1]=n;
        for(int i=1;i<=n+1;i++) a[n+1+i]=a[i];
        for(int i=n*2+2;i;i--)
        {
            mp[i]=0;
            if(a[i]==n-1) s[++top]=i;
            if(a[i]==n+1)
            {
                if(top) mp[i]=mp[s[top]]=s[top]-i,top--;
                else mp[i]=inf;
            }
        }
        for(int i=1;i<=n+1;i++) if(!mp[i]) mp[i]=mp[i+n+1];
        while(q--)
        {
            int x;
            scanf("%lld",&x);
            x++;
            int now=(x-1)/n;
            int t=(x-1)%n+1;
            if(a[t]==n-1&&(mp[t]>now||mp[t]==0)) printf("%lld ",n-1);
            else
            {
                int last=((t-now-1)%(n+1)+n+1)%(n+1)+1;
                if(mp[last]<=now||a[last]!=n+1) printf("%lld ",n);
                else printf("%lld ",n+1);
            }
        }
        printf("\n");
    }
    return 0;
}