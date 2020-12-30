#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
 
ll dp[1020],n,m,cnt[1020];
ll qpow(ll x,ll y)
{
    ll ret=1;
    while(y)
    {
        if(y%2==1) ret=ret*x%MOD;
        x=x*x%MOD;
        y/=2;
    }
    return ret;
}
 
int main()
{
    scanf("%lld%lld",&n,&m);
    int full=(1<<n)-1;
    memset(dp,-1,sizeof(dp));
    for(int mask=0;mask<=full;mask++)
    {
        int tmp=0;
        for(int i=1;i<=n;i++) if(mask&(1<<(i-1))) tmp++;
        if(tmp>=m) dp[mask]=0;
    }
    for(int mask1=full;mask1>=0;mask1--)
    {
        //cout<<1<<endl;
        for(int i=0;i<=full;i++) cnt[i]=0;
        if(dp[mask1]!=-1) continue;
        for(int l=1;l<=n;l++)
        {
            for(int r=l;r<=n;r++)
            {
                int mask2=0;
                for(int i=l;i<=r;i++) mask2|=(1<<(i-1));
                cnt[mask1|mask2]++;
            }
        }
        ll S=n*(n+1)/2;
        ll sum=0;
        for(int i=mask1+1;i<=full;i++)
            sum=(sum+cnt[i]*dp[i])%MOD;
        //cout<<mask1<<" "<<sum<<" "<<cnt[mask1]<<endl;
        dp[mask1]=(sum+S)*qpow(S-cnt[mask1],MOD-2)%MOD;
    }
    cout<<dp[0]<<endl;
    return 0;
}